#ifndef UI_TRACK_HEIGHT
#define UI_TRACK_HEIGHT

namespace ui {

enum Height {
	HeightSmallest,
	HeightSmall,
	HeightNormal,
	HeightLarge,
	HeightLargest
};

int get_height_in_pixels(Height);

void set_default_height(Height);

Height get_default_height();

std::string get_height_name(Height);
}

#endif
