
#include <libgleam/periodic_signal.hpp>

namespace gleam {

PeriodicSignal::PeriodicSignal (unsigned int interval,
        Glib::RefPtr<Glib::MainContext> main_context,
        int priority)
    :
        m_timeout_interval(interval),
        m_main_context(main_context),
        m_priority(priority)
{

}

sigc::signal<void>&
PeriodicSignal::signal()
{
    /*
     * If there are currently no connections then activate
     * the timeout.
     */
    if(m_signal.size() == 0)
    {
        const Glib::RefPtr<Glib::TimeoutSource> timeout_source = Glib::TimeoutSource::create(1000);
        m_timeout_connection = timeout_source->connect(sigc::mem_fun(this, &PeriodicSignal::timeout_handler));

        // The MainContext takes a reference to the timeout source
        // so the source that was created stays around after the RefPtr
        // goes out of scope.
        timeout_source->attach(m_main_context);
    }

    return m_signal;
}

bool
PeriodicSignal::timeout_handler()
{
    if(m_signal.size() == 0)
    {
        m_timeout_connection.disconnect();
        
        return false;
    }

    m_signal();

    // There are still callbacks connected
    // to the signal so stay connected to the 
    // timeout callback.
    return true;
}

} // namespace gleam
