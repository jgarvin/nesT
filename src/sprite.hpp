#ifndef INCLUDED_NEST_SPRITE_HPP
#define INCLUDED_NEST_SPRITE_HPP

#include <cstdint>
#include <string>

#include <boost/array.hpp>
#include <boost/multi_array.hpp>

// Represents an 8x8 pixel bitmap stored in the CHR region
class sprite
{
public:
	sprite(const char* raw_data);

	std::string to_string() const;

	// we can remove this later.  I just needed this for testing
	boost::multi_array<uint8_t, 2> * data() {return &color_layout_;}

private:
	static const int WIDTH = 8;
	static const int HEIGHT = 8;
	static const int COLOR_CHANNEL_SIZE = 8;

	boost::multi_array<uint8_t, 2> color_layout_;
};

#endif

