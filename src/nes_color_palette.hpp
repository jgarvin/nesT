/*
 * Contains an implementation of a single 4-color palette used for for a sprite.  These palettes are
 * really just indices into a master palette, which is implemented elsewhere.  Also, note that color
 * 0 is always the background color.  See here for more info:
 * http://wiki.nesdev.com/w/index.php/PPU_palettes
 */

#ifndef INCLUDED_NEST_NES_COLOR_PALETTE_HPP
#define INCLUDED_NEST_NES_COLOR_PALETTE_HPP

#include <cstdint>
#include <boost/multi_array.hpp>

#include "sprite.hpp"
#include "nes_master_palette.hpp"


class nes_color_palette
{
public:
	nes_color_palette(nes_master_palette *master, const uint8_t *indices = NULL);
	~nes_color_palette();

	bool apply_colors(boost::multi_array<uint8_t, 2> *input_data, 
					  boost::multi_array<uint32_t, 2> *output_image);

	void set_color_ref(uint8_t index, uint8_t ref);
	uint8_t color_ref(uint8_t index) const;
	void set_master_palette(nes_master_palette *master);
	nes_master_palette * master_palette() const;

private:
	uint32_t color(uint8_t index) const;
	uint32_t actual_color(uint8_t index) const;

	static const uint8_t PALETTE_SIZE = 4;
	
	uint8_t m_pal[PALETTE_SIZE];
	nes_master_palette *m_master;
};

#endif // INCLUDED_NEST_NES_COLOR_PALETTE_HPP
