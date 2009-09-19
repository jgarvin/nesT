#include <sstream>

#include "sprite.hpp"

sprite::sprite(const char* raw_data)
	: color_layout_(boost::extents[8][8])
{
	const char* channelA = raw_data;
	const char* channelB = raw_data + COLOR_CHANNEL_SIZE;

	for(int i = 0; i < HEIGHT; ++i) {
		for(int j = 0; j < WIDTH; ++j)
		{
			char mask = 1 << i;
			char valA = mask & channelA[j] ? 1 : 0;
			char valB = mask & channelB[j] ? 2 : 0; // B channel gets more weight

			color_layout_[i][j] = valA + valB;
		}
	}
}

std::string sprite::to_string() const
{
	std::ostringstream o;
	
	for(int i = 0; i < HEIGHT; ++i) {
		for(int j = 0; j < WIDTH; ++j) {
			o << static_cast<int>(color_layout_[i][j]);
		}
		if(i != HEIGHT - 1)
			o << std::endl;
	}

	return o.str();
}
