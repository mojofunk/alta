
class AtomicUpdateBase
{
public:

	virtual ~AtomicUpdateBase();
	
	// perform the update
	virtual void operator();

	virtual void notify_update_complete () = 0;

};

class atomic_update
{
public:

	// perform the update
	virtual void operator();

private:

	class_type* m_object;

	atomic_ptr<property_type> 
	
};
