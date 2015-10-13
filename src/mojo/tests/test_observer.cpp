#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_observer
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include "mojo/core/misc/functor_dispatcher.hpp"
#include "mojo/core/time/time.hpp"

#include <atomic>
#include <iostream>
#include <cstdint>
#include <list>
#include <set>
#include <thread>
#include <mutex>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

class Object;

class ObjectReferenceOwner {
public:
	virtual ~ObjectReferenceOwner() {}

	virtual void drop_references(const std::shared_ptr<Object>&) = 0;
};

/**
 * An instance of a class deriving from Object must be held in a
 * std::shared_ptr as Object derives from std::enable_shared_from_this<Object>
 *
 * The lifetime of a class deriving from Object can be controlled in two ways.
 *
 * The shared_ptr is created by client code and the lifetime of the object is
 * controlled by the number of shared_ptr instances. When the last shared_ptr
 * instance is destructed the Object derived destructor is called as per usual
 * shared_ptr usage.
 *
 * Or the shared_ptr is created via ObjectManager::create<Type>() factory
 * interface in which case the ObjectManager holds an extra strong reference.
 * The Object manager will periodically check if it is the only reference
 * holder to the Object instance and if so drop its reference so the destructor
 * is called. The other situation is when an Object instance is forcefully
 * destroyed with object->destroy() which indicates to strong reference holders
 * to drop their references. The manager will receive the drop_references
 * callback and will know that it should soon be the only reference holder to
 * the Object instance and if the reference count doesn't drop to 1 within a
 * certain period of time there may be a strong reference that isn't going out
 * of scope when it should.
 *
 * An ObjectManager is used to be able to control when and in which thread an
 * Object instance is deleted.
 *
 * The Object destructor should only be called when there are no other
 * reference holders. As long as references to Object instances are held in
 * shared_ptr and any raw pointer usage is only while holding a strong
 * reference then there should be no dangling references...
 *
 * We also want to be able to forcefully destroy an Object instance, which
 * means all reference holders will have to drop their references. In order to
 * facilitate that, the reference holders must register a callback when they
 * acquire the reference that can be executed to signal to drop any references
 * to the object.
 *
 * As there may be references held in many threads it is impractical to handle
 * disposing of references in a synchronous manner as it means waiting for each
 * thread that may have a reference to the object to drop the reference.
 *
 * If the dropping of references is performed in a asynchronous manner then the
 * reference holder queues for the reference to be dropped in whatever threads
 * it knows may hold a reference to the Object instance.
 *
 * In the case of a single threaded GUI where an Object instance is created in
 * a non-GUI thread and a callback is executed to tell the GUI about the new
 * Object the GUI code must immediately register a callback to handle forceful
 * destruction and then queue the new Object to be handled by the GUI thread.
 * This ensures that if a forceful destruction of the instance occurs before
 * the GUI has processed the new Object it can still queue the reference to be
 * dropped and it won't miss the forceful destruction signal.
 *
 * Using the ObjectManager class should be optional for Object derived classes
 * and the Object class should not hold a reference to the ObjectManager class
 *
 * This implies that Object creation should occur through a central factory
 * interface where Object instances are created and then registered with the
 * ObjectManager instance.
 *
 * Using the ObjectManager class is a form of garbage collection that we can
 * use to control when the destruction of class instances occur. For instance
 * we may want to handle object destruction in a low priority thread and or
 * only run the thread for a maximum period of time etc.
 *
 * If the destroy method is called on an Object instance the ObjectManager will
 * queue that instance for final destruction. The ObjectManager can easily
 * detect if any references are being held when they shouldn't if the reference
 * count is still > 1 after a sufficient period of time has elapsed for all
 * threads to have run and removed their reference.
 */
class Object : public enable_shared_from_this<Object> {
public:

	/**
	 * The destructor for an Object must not be called until destroy is called
	 * to notify the observers to drop references.
	 */
	virtual ~Object();

	// property interface

	/**
	 * Request that hold references to this class drop their references. This
	 * may not leave the caller with the only valid reference if the object is
	 * also being managed by an ObjectManager.
	 */
	void destroy()
	{
		std::cout << "Object::destroy" << std::endl;

		std::unique_lock<std::mutex> lock(m_reference_owner_mutex);

		for (auto const reference_owner : m_reference_owners) {
			const shared_ptr<Object> obj_ptr = shared_from_this();
			reference_owner->drop_references(obj_ptr);
		}
		// clear reference_owner list?
	}

	void add_reference_owner(ObjectReferenceOwner* reference_owner)
	{
		std::unique_lock<std::mutex> lock(m_reference_owner_mutex);

		m_reference_owners.insert(reference_owner);

		/**
		 * assertion or perhaps just a warning here if the reference_owner count and
		 * the shared_ptr count are not equal, If an Observer wants to hold
		 * more than a single strong reference then it needs to be a logged
		 * warning?
		 */
	}

	/**
	 * The ObjectReferenceOwner must still hold at least one strong reference to
	 * this instance when calling remove_reference_owner. It is assumed that the
	 * first thing they do after calling remove_reference is actually dropping
	 * all the strong references they do hold.
	 */
	void remove_reference_owner(ObjectReferenceOwner* reference_owner)
	{
		std::unique_lock<std::mutex> lock(m_reference_owner_mutex);

		/**
		 * assertion or perhaps just a warning here if the reference_owner count and
		 * the shared_ptr count are not equal, If an Observer wants to
		 * hold more than a single strong reference then it needs to be a
		 * logged warning?
		 */

		m_reference_owners.erase(reference_owner);
	}

private:
	std::set<ObjectReferenceOwner*> m_reference_owners;
	std::mutex m_reference_owner_mutex;
};

Object::~Object()
{
	/**
	 * If there are any observers still in the observer list then it is an
	 * error.
	 *
	 * No need to lock as there can be no other reference holders apart from
	 * the current thread.
	 */
//	assert (m_object_observers.empty());
}

class ObjectGC : public ObjectReferenceOwner {
public: // ctors
	virtual ~ObjectGC() { }

public: // interface
	virtual void manage (const shared_ptr<Object>&) = 0;

	//void collect () = 0;

	void drop_references (const shared_ptr<Object>&) = 0;

};

class DefaultObjectGC : public ObjectGC
{
public:
	DefaultObjectGC()
	    : m_thread(std::ref(*this))
	{
		std::cout << "DefaultObjectGC::ctor" << std::endl;
	}

	~DefaultObjectGC()
	{
		std::cout << "DefaultObjectGC::dtor" << std::endl;
		m_thread.join();
	}

	void manage(const shared_ptr<Object>& object)
	{
		std::cout << "DefaultObjectGC::manage" << std::endl;
		/**
		 * Add the reference immediately in the event that object is destroyed.
		 * It is assumed that the caller ensures that no calls to
		 * object->destroy() can occur concurrently or before this function
		 * returns.
		 */
		object->add_reference_owner(this);

		/**
		 * Now that we have added a reference to the object the insertion could
		 * just be queued to occur in the manager thread but that is just a
		 * detail.
		 */
		std::unique_lock<std::mutex> lock(m_managed_objects_mutex);

		// TODO check it was inserted successfully
		m_managed_objects.insert(object);
	}

	void drop_references (const shared_ptr<Object>& object)
	{
		std::cout << "DefaultObjectGC::drop_references" << std::endl;

		/**
		 * The object instance could be queued here to be dropped in the GC thread
		 */
		std::unique_lock<std::mutex> lock(m_managed_objects_mutex);
		// TODO check it was erased successfully
		m_managed_objects.erase(object);
	}

	void operator()()
	{
		std::cout << "DefaultObjectGC running cleanup" << std::endl;

		std::unique_lock<std::mutex> lock(m_managed_objects_mutex);
		for (auto object : m_managed_objects) {
			if (object.unique()) {
				std::cout << "Object ref count 1, dropping reference" << std::endl;
				m_managed_objects.erase(object);
			}
		}

		mojo::sleep(1);
	}

private:
	std::thread m_thread;

	std::mutex m_managed_objects_mutex;
	std::set<shared_ptr<Object>> m_managed_objects;
};

class ObjectManager {
public:
	static void initialize();

	static void deinitialize();

	static void set_gc(std::unique_ptr<ObjectGC> gc)
	{
		// set a custom GC
		// transfer managed objects?
	}

	static ObjectGC& get_gc();

	template <class T>
	static shared_ptr<T> create()
	{
		shared_ptr<T> ptr = make_shared<T>();
		get_gc().manage(ptr);
		return ptr;
	}

private:
	class Impl;
	static unique_ptr<Impl> s_impl;
};

struct ObjectManager::Impl {
	std::unique_ptr<ObjectGC> m_gc;
};

void ObjectManager::initialize()
{
	s_impl = unique_ptr<Impl>(new Impl);
	s_impl->m_gc = unique_ptr<ObjectGC>(new DefaultObjectGC);
}

void ObjectManager::deinitialize()
{
	s_impl.reset();
}

ObjectGC& ObjectManager::get_gc()
{
	return *(s_impl->m_gc.get());
}

std::unique_ptr<ObjectManager::Impl> ObjectManager::s_impl;

class Route;

class RouteObserver {
public:
	virtual void mute_enabled_changed(const shared_ptr<Route>&,
	                                  bool mute_enabled) = 0;
	virtual void solo_enabled_changed(const shared_ptr<Route>&,
	                                  bool solo_enabled) = 0;
};

class Route : public Object {
public: // ctors
	Route()
	    : m_mute_enabled(false)
	    , m_solo_enabled(false)
	{
	}

public: // interface
	void set_mute_enabled(bool mute_enabled)
	{
		std::cout << "Route::set_mute_enabled" << std::endl;
		if (m_mute_enabled == mute_enabled) {
			return;
		}
		m_mute_enabled = mute_enabled;

		std::unique_lock<std::mutex> lock(m_route_observers_mutex);

		const shared_ptr<Route> route = static_pointer_cast<Route>(shared_from_this());

		for (auto const observer : m_route_observers) {
			observer->mute_enabled_changed(route, m_mute_enabled);
		}
	}

	bool get_mute_enabled() const { return m_mute_enabled; }

	void set_solo_enabled(bool solo_enabled)
	{
		std::cout << "Route::set_solo_enabled" << std::endl;
		if (m_solo_enabled == solo_enabled) {
			return;
		}
		m_solo_enabled = solo_enabled;

		// perhaps the lock should only be taken to copy the observer list
		// so that the lock isn't held during emission but then again if the
		// list is copied and no lock is taken then another thread may remove
		// an observer from the observer list and be deleted. We then have a
		// dangling reference in the copied list. One way to rectify this would
		// be to hold weak_ptr references to the Observers and try to convert to
		// shared_ptr before calling but that also complicates things for the
		// clients as they can't add/remove observers in ctor/dtor etc and
		// probably other complications.
		std::unique_lock<std::mutex> lock(m_route_observers_mutex);

		const shared_ptr<Route> route = static_pointer_cast<Route>(shared_from_this());

		for (auto const observer : m_route_observers) {
			observer->solo_enabled_changed(route, m_solo_enabled);
		}
	}

	bool get_solo_enabled() const { return m_solo_enabled; }

	virtual void add_route_observer(RouteObserver* route_observer)
	{
		std::unique_lock<std::mutex> lock(m_route_observers_mutex);
		m_route_observers.insert(route_observer);
	}

	virtual void remove_route_observer(RouteObserver* route_observer)
	{
		std::unique_lock<std::mutex> lock(m_route_observers_mutex);
		m_route_observers.erase(route_observer);
	}

private: // data
	std::set<RouteObserver*> m_route_observers;
	std::mutex m_route_observers_mutex;

	bool m_mute_enabled;
	bool m_solo_enabled;
};

class Track;

class TrackObserver {
public:
	virtual void record_enabled_changed(const shared_ptr<Track>&,
	                                    bool record_enabled) = 0;
};

class Track : public Route {
public:

	Track()
	: m_record_enabled(false)
	{

	}

	void set_record_enabled(bool record_enabled)
	{
		std::cout << "Route::set_record_enabled" << std::endl;
		if (m_record_enabled == record_enabled) {
			return;
		}
		m_record_enabled = record_enabled;

		std::unique_lock<std::mutex> lock(m_track_observers_mutex);
		const shared_ptr<Track> track = static_pointer_cast<Track>(shared_from_this());

		for (auto const observer : m_track_observers) {
			observer->record_enabled_changed(track, m_record_enabled);
		}
	}

	bool get_record_enabled() const { return m_record_enabled; }

	void add_track_observer(TrackObserver* track_observer)
	{
		std::unique_lock<std::mutex> lock(m_track_observers_mutex);
		m_track_observers.insert(track_observer);
	}

	void remove_track_observer(TrackObserver* track_observer)
	{
		std::unique_lock<std::mutex> lock(m_track_observers_mutex);
		m_track_observers.erase(track_observer);
	}

private:
	std::set<TrackObserver*> m_track_observers;
	std::mutex m_track_observers_mutex;

	bool m_record_enabled;
};

class Project;

class ProjectObserver {
public:
	virtual void route_added(const shared_ptr<Route>& track) = 0;
	virtual void route_removed(const shared_ptr<Route>& track) = 0;
};

class Project : public Object, public ObjectReferenceOwner {
public:

	bool add_route (const shared_ptr<Route>& route)
	{
		route->add_reference_owner(this);
		{
			std::unique_lock<std::mutex> lock(m_route_mutex);
			m_routes.insert(route);
		}

		std::unique_lock<std::mutex> lock(m_project_observers_mutex);

		for (auto const observer : m_project_observers) {
			observer->route_added(route);
		}
	}

	bool remove_route (const shared_ptr<Route>& route)
	{
		route->remove_reference_owner(this);
		{
			std::unique_lock<std::mutex> lock(m_route_mutex);
			m_routes.erase(route);
		}

		std::unique_lock<std::mutex> lock(m_project_observers_mutex);

		for (auto const observer : m_project_observers) {
			observer->route_removed(route);
		}
	}

	/**
	 * When removing a route from the project we also want all reference
	 * holders to drop there references to the route?
	 */
	void remove_all_routes()
	{
		std::unique_lock<std::mutex> observer_lock(m_project_observers_mutex);
		std::unique_lock<std::mutex> routes_lock(m_route_mutex);

		for (auto route : m_routes) {
			route->remove_reference_owner(this);

			for (auto const observer : m_project_observers) {
				observer->route_removed(route);
			}
		}
		m_routes.clear();
	}

	void destroy_all_routes()
	{
		std::set<shared_ptr<Route>> routes_copy;
		{
			std::unique_lock<std::mutex> routes_lock(m_route_mutex);

			/**
			 * Take a copy so the iterators aren't invalidated when drop_references
			 * is called by destroy.
			 */
			routes_copy = m_routes;
		}

		for (auto route : routes_copy) {
			route->destroy();
		}

		// The route list should now be empty unless another thread has added
		// another route in the meantime, which should probably be prevented.
		//assert(m_routes.empty());
	}

	void drop_references(const std::shared_ptr<Object>& object)
	{
		const std::shared_ptr<Route> route = static_pointer_cast<Route>(object);
		{
			std::unique_lock<std::mutex> lock(m_route_mutex);
			m_routes.erase(route);
		}

		std::unique_lock<std::mutex> lock(m_project_observers_mutex);

		for (auto const observer : m_project_observers) {
			observer->route_removed(route);
		}
	}

	void add_project_observer(ProjectObserver* observer)
	{
		std::unique_lock<std::mutex> lock(m_project_observers_mutex);
		m_project_observers.insert(observer);
	}

	void remove_project_observer(ProjectObserver* observer)
	{
		std::unique_lock<std::mutex> lock(m_project_observers_mutex);
		m_project_observers.erase(observer);
	}

private:
	std::set<ProjectObserver*> m_project_observers;
	std::mutex m_project_observers_mutex;

	std::set<shared_ptr<Route>> m_routes;
	std::mutex m_route_mutex;
};

class Widget {
public:
};

class RouteWidget : public Widget, public RouteObserver {
public:
	RouteWidget(const shared_ptr<Route>& route)
	    : m_route(route)
	{
		m_route->add_route_observer(this);
	}

	~RouteWidget()
	{
		m_route->remove_route_observer(this);
	}

public: // RouteObserver interface
	virtual void mute_enabled_changed(const shared_ptr<Route>& route, bool mute_enabled)
	{
		std::cout << "RouteWidget::mute_enabled_changed" << std::endl;
		assert(route == m_route);
	}

	virtual void solo_enabled_changed(const shared_ptr<Route>& route, bool solo_enabled)
	{
		std::cout << "RouteWidget::solo_enabled_changed" << std::endl;
		assert(route == m_route);
	}

public:
	const shared_ptr<Route>& get_route() { return m_route; }

protected:
	shared_ptr<Route> m_route;
};

class TrackWidget : public RouteWidget, public TrackObserver {
public:
	TrackWidget(const shared_ptr<Track>& track)
	    : RouteWidget(track)
	    , m_track(track)
	{
		m_track->add_track_observer(this);
	}

	~TrackWidget()
	{
		m_track->remove_track_observer(this);
	}

public: // RouteObserver interface
	virtual void mute_enabled_changed(const std::shared_ptr<Route>& route, bool mute_enabled)
	{
		std::cout << "TrackWidget::mute_enabled_changed" << std::endl;
	}

	virtual void solo_enabled_changed(const std::shared_ptr<Route>& route, bool solo_enabled)
	{
		std::cout << "TrackWidget::solo_enabled_changed" << std::endl;
	}

public: // TrackObserver interface
	virtual void record_enabled_changed(const std::shared_ptr<Track>& track, bool record_enabled)
	{
		std::cout << "TrackWidget::record_enabled_changed" << std::endl;
	}

private:
	// not necessary to store this but saves casting?
	shared_ptr<Track> m_track;
};

class UI;

class ProjectUI : public Widget,
                  public ProjectObserver,
                  public ObjectReferenceOwner {
public:
	ProjectUI(const shared_ptr<Project>& project, int id)
	    : m_thread(std::ref(*this))
	    , m_project(project)
	    , m_id(id)
	{
		std::cout << "ProjectUI ctor" << std::endl;
		// wait for dispatcher to start
		m_dispatcher.iteration(true);
		m_project->add_project_observer(this);
	}

	~ProjectUI()
	{
		m_project->remove_project_observer(this);
		m_dispatcher.quit();
		std::cout << "ProjectUI quit main loop" << std::endl;
		m_thread.join();
	}

	void route_added(const shared_ptr<Route>& route)
	{
		//std::cout << "ProjectUI route_added" << std::endl;
		shared_ptr<Route> route_ptr(route);

		/**
		 * I'm not sure that the ProjectUI needs be a reference owner for
		 * the Route as the Project class is also a reference owner and will
		 * execute the route_removed callback when the Route is either removed
		 * from the Project or is destroyed.
		 */
		//route->add_reference_owner (this);

		// bind a strong reference into the queue as
		call_async(std::bind(&ProjectUI::route_added_ui_thread, this, route_ptr));
	}

	/**
	 * This function will be called by the Project class when a route is either
	 * removed from the project or a route is forcefully destroyed.
	 */
	void route_removed(const shared_ptr<Route>& route)
	{
		//std::cout << "ProjectUI route_removed" << std::endl;
		shared_ptr<Route> route_ptr(route);

		/**
		 * This will cause a deadlock as the route's reference owner lock will
		 * be held in Route::destroy and trying to remove the reference from
		 * the observers list. So queue it to be done in the UI thread.
		 */
		 //route->remove_reference_owner(this);

		// we already hold a strong reference so a std::cref(route) could
		// be used here?
		call_async(std::bind(&ProjectUI::route_removed_ui_thread, this, route_ptr));
	}

	void drop_references(const shared_ptr<Object>& project)
	{
		std::cout << "ProjectUI drop references" << std::endl;

		// project is going away...what to do here

		// or one of the routes is going away
	}

public:
	typedef boost::function<void()> function_type;

	void operator()()
	{
		std::cout << "ProjectUI running dispatcher main loop" << std::endl;
		m_dispatcher.run();
	}

private:

	void call_sync(const function_type& func) { m_dispatcher.call_sync(func); }

	void call_async(const function_type& func) { m_dispatcher.call_async(func); }

	void iteration(bool block) { m_dispatcher.iteration(block); }

private:

	void route_added_ui_thread (shared_ptr<Route> route)
	{
		std::cout << "ProjectUI route_added_ui_thread" << std::endl;

		shared_ptr<Track> track = dynamic_pointer_cast<Track>(route);

		if (track) {
			std::cout << "ProjectUI Adding TrackWidget" << std::endl;
			shared_ptr<TrackWidget> track_widget = make_shared<TrackWidget>(track);
			m_route_widgets.push_back(track_widget);
		} else {
			std::cout << "ProjectUI Adding RouteWidget" << std::endl;
			shared_ptr<RouteWidget> route_widget = make_shared<RouteWidget>(route);
			m_route_widgets.push_back(route_widget);
		}
	}

	void route_removed_ui_thread (shared_ptr<Route> route)
	{
		std::cout << "ProjectUI route_removed_ui_thread" << std::endl;

		for (const auto route_widget : m_route_widgets) {
			if (route_widget->get_route() == route) {
				m_route_widgets.remove(route_widget);
				break;
			}
		}

		/**
		 * The project doesn't hold a reference to the Route but it is the
		 * reference owner so it is responsible for dropping all references to
		 * the route when the Object's destroy callback is executed.
		 *
		 * The RouteWidget instance holds the reference to the Route so destroy
		 * the RouteWidget that holds a reference to the route.
		 *
		 * The RouteWidget could be the reference owner(I think) but that would
		 * require an extra callback from the RouteWidget to the ProjectUI, but
		 * perhaps is cleaner.
		 */
		route->remove_reference_owner(this);
	}

private:
	FunctorDispatcher m_dispatcher;

	std::thread m_thread;

	std::list<std::shared_ptr<RouteWidget>> m_route_widgets;

	shared_ptr<Project> m_project;

	const int m_id;
};

BOOST_AUTO_TEST_CASE(test_route_observer)
{
	std::shared_ptr<Route> route = make_shared<Route>();
	std::unique_ptr<RouteWidget> route_widget(new RouteWidget(route));

	route->set_solo_enabled(true);
	route->set_mute_enabled(true);

	route->destroy();
}

BOOST_AUTO_TEST_CASE(test_track_observer)
{
	std::shared_ptr<Track> track = make_shared<Track>();
	std::unique_ptr<TrackWidget> track_widget(new TrackWidget(track));

	track->set_solo_enabled(true);
	track->set_mute_enabled(true);
	track->set_record_enabled(true);

	track->destroy();
}

BOOST_AUTO_TEST_CASE(test_object_manager_create)
{
	ObjectManager::initialize();

	std::shared_ptr<Track> track = ObjectManager::create<Track>();
	std::unique_ptr<TrackWidget> track_widget(new TrackWidget(track));

	track->set_solo_enabled(true);
	track->set_mute_enabled(true);
	track->set_record_enabled(true);

	track->destroy();

	ObjectManager::deinitialize();
}

BOOST_AUTO_TEST_CASE(test_project_ui)
{
	ObjectManager::initialize();

	//std::shared_ptr<Project> project = ObjectManager::create<Project>();
	std::shared_ptr<Project> project = make_shared<Project>();

	std::list<ProjectUI*> project_ui_list;

	for (int i = 0; i < 10; ++i) {
		ProjectUI* new_project_ui = new ProjectUI(project, i);
		project_ui_list.push_back(new_project_ui);
	}

	std::cout << "Adding tracks to project" << std::endl;

	for (int i = 0; i < 1000; ++i) {
		std::shared_ptr<Route> route = ObjectManager::create<Route>();
		std::shared_ptr<Track> track = ObjectManager::create<Track>();

		project->add_route(track);
		project->add_route(route);
	}

	// Test destroying the routes

	project->remove_all_routes();

	mojo::sleep(3);

	std::cout << "Adding tracks to project again" << std::endl;

	for (int i = 0; i < 1000; ++i) {
		std::shared_ptr<Route> route = ObjectManager::create<Route>();
		std::shared_ptr<Track> track = ObjectManager::create<Track>();

		project->add_route(track);
		project->add_route(route);
	}

	// Test destroying the routes

	project->destroy_all_routes();

	mojo::sleep(3);

	for (auto project_ui : project_ui_list) {
		delete project_ui;
	}

	ObjectManager::deinitialize();
}

BOOST_AUTO_TEST_CASE(test_add_remove_observers)
{
}

/**
 * Test connecting to an Object derived class, then destroying/deleting
 * the instance in another thread.
 */
BOOST_AUTO_TEST_CASE(test_drop_references_threaded)
{
	// several worker threads will create and destroy tracks while observer
	// threads add and remove references to created tracks.
}

/**
 * Test connecting and disconnecting a signal/event of an Object derived
 * instance from another thread.
 */
BOOST_AUTO_TEST_CASE(test_add_remove_observers_threaded)
{
}

BOOST_AUTO_TEST_CASE(test_circular_references)
{

}

