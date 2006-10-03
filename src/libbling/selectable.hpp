
#ifndef BLING_SELECTABLE_INCLUDED
#define BLING_SELECTABLE_INCLUDED

namespace bling {

class Selectable 
{
public:
  
    Selectable() : m_selected(false) {}
    
    virtual ~Selectable() {}
    
	virtual void set_selected (bool yn) {
		if(yn != m_selected) {
			m_selected = yn;
		}
	}
    
    virtual bool selected() const { return m_selected; }
    
protected:

    bool m_selected;

};

} // namespace bling

#endif // BLING_SELECTABLE_INCLUDED
