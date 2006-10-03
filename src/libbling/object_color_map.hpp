#ifndef BLING_OBJECT_COLOR_MAP_INCLUDED
#define BLING_OBJECT_COLOR_MAP_INCLUDED

#include <map>
#include <cmath>
#include <cstdlib> // random()

#include <gdkmm/color.h>
#include <sigc++/sigc++.h>

namespace bling {

/**
   This class can be used so that if there is
   several visual representations of a certain
   object in a GUI then the color representation
   for those objects will be consistant.
*/
template<class T>
class ObjectColorMap : public sigc::trackable
{
public:

	/**
	   @return The color associated with a 
	   particular object.

	   If the object doesn't have a color 
	   associated with it then a unique color 
	   for that type of object will be generated.
	*/
	Gdk::Color get_color(const T& object)
	{
		typename std::map<T*,Gdk::Color>::const_iterator it = m_color_map.find(&object);
		
		if(it != m_color_map.end()) return (*it).second;

		// object not in colormap so generate a 
		// unique color and add mapping.

		Gdk::Color newcolor = get_unique_color();

		m_color_map.insert(make_pair(&object, newcolor));

		return newcolor;	
	}

	/**
	   Find a color that is sufficiently different to the other
	   objects in color map.
	*/
	Gdk::Color get_unique_color()
	{
		Gdk::Color newcolor;
		bool found_unique_color = false;
		const int max_saturation = 48000; // 65535 would open up the whole color wheel
		double delta = 25.0;
		bool colors_to_close = false;

		while(delta > 10.0) {
			
			newcolor.set_red (random() % max_saturation);
			newcolor.set_blue (random() % max_saturation);
			newcolor.set_green (random() % max_saturation);
	
			for (typename std::map<T*, Gdk::Color>::iterator i = m_color_map.begin();
			     i != m_color_map.end() && !colors_to_close; ++i) {
				
				float rdelta, bdelta, gdelta;
				
				rdelta = newcolor.get_red() - (*i).second.get_red();
				bdelta = newcolor.get_blue() - (*i).second.get_blue();
				gdelta = newcolor.get_green() - (*i).second.get_green();
				
				if (sqrt (rdelta*rdelta + bdelta*bdelta + gdelta*gdelta) < delta) {
					colors_to_close = true;
				}
			}
			
			if(!colors_to_close) return newcolor;

			// allow for colors to be closer
			--delta;
		}

		/* If we still haven't found a different enough color,
		   we may still want to check that the new color is 
		   unique. XXX todo.
		*/
		return newcolor;
	}

	bool object_in_colormap(const T& object) const
	{
		typename std::map<T*, Gdk::Color>::const_iterator i = m_color_map.find(&object);

		if(i != m_color_map.end()) return true;
		return false;
	}

	/**
	   Set the color for an object in the colormap,
	   or add the mapping if it doesn't exist.
	*/
	void set_color(const T& object, const Gdk::Color& newcolor)
	{
		typename std::map<T*, Gdk::Color>::const_iterator i = m_color_map.find(&object);
		
		if(i != m_color_map.end()) {
			
			// object in map, so set its associated color.
		
			(*i).second = newcolor;
			m_color_changed(sigc::ref(*(*i).first), newcolor);
		}

		// check for uniqueness of color?
		m_color_map.insert(make_pair(&object, newcolor));	
	}
	
	
	/**
	   signal is emitted when the color of an object
	   is changed.
	*/
	sigc::signal<void, T&, Gdk::Color>& color_changed() const
	{ return m_color_changed; }

private:

	/// the color map
	std::map<T*, Gdk::Color> m_color_map;

	sigc::signal<void, T&, Gdk::Color> m_color_changed; 

};

} // namespace bling

#endif // BLING_OBJECT_COLOR_MAP_INCLUDED
