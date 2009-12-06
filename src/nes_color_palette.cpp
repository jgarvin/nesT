/*
 * Contains an implementation of a single 4-color palette used for for a sprite.  These palletes are
 * really just indices into a master palette, which is implemented elsewhere.  See here for more
 * info: http://wiki.nesdev.com/w/index.php/PPU_palettes
 */

#include <toast/assert.hpp>
#include <cstring>
#include <algorithm>
#include "nes_color_palette.hpp"

/* indices must point to at least 4 values.  We just keep the pointer to master, not the contents.
 */
nes_color_palette::nes_color_palette(nes_master_palette *master, const std::vector<uint8_t> *indices)
{
	TOAST_ASSERT_NOT_NULL(master);
	m_master = master;
	
	m_pal.resize(PALETTE_SIZE);

	if(indices)
	{
		TOAST_ASSERT(indices->size() >= PALETTE_SIZE);
		std::copy(indices->begin(), indices->begin() + PALETTE_SIZE, m_pal.begin());
	}
	else
		m_pal = std::vector<uint8_t>(PALETTE_SIZE);
}

nes_color_palette::~nes_color_palette()
{
}

/* Uses the data in the input to create a colored image in the output.  Returns True when completed.
 * The input data must be numbers 0-3 to correspond to the indices into this palette.  Both arrays
 * must have the same dimension sizes for this to work correctly.
 */
bool nes_color_palette::apply_colors(boost::multi_array<uint8_t, 2> *input_data, 
									 boost::multi_array<uint32_t, 2> *output_image)
{
	// get iterators for our rows (y-coordindate)
	auto in_itry  = input_data->begin();
	auto out_itry = output_image->begin();

	for(; in_itry < input_data->end() && out_itry < output_image->end(); ++in_itry, ++out_itry)
	{
		// get iterators for the columns in the the row (x-coordinate)
		auto in_itrx = in_itry->begin();
		auto out_itrx = out_itry->begin();

		for(; in_itrx < in_itry->end() && out_itrx < out_itry->end(); ++in_itrx, ++out_itrx)
			*out_itrx = color(*in_itrx);
	}
	return true;
}


/* Change one of the colors in this palette to refer to a different color in the object's master
 * palette.  For example, calling set_color(1, 0x0A) sets color 1 in the palette to refer to 0x0A in
 * the master, which is green in the default master.  Index must be less than 3 and color less than
 * the master palette size (64).
 */
void nes_color_palette::set_color_ref(uint8_t index, uint8_t ref)
{
	TOAST_ASSERT(index < PALETTE_SIZE);
	TOAST_ASSERT(ref < m_master->size());
	m_pal[index] = ref;
}

/* Get the reference into the master palette where this index points to.  Index must be less than
 * the palette size (4).
 */
uint8_t nes_color_palette::color_ref(uint8_t index) const
{
	TOAST_ASSERT(index < PALETTE_SIZE);
	return m_pal[index];
}

/* Set the master color palette.  This is the large palette from which this palette can choose its
 * colors from.  It's up to the caller to figure out what to do with the old palette.  This will
 * fail if you pass in a NULL pointer.
 */
void nes_color_palette::set_master_palette(nes_master_palette *master)
{
	TOAST_ASSERT_NOT_NULL(master);
	m_master = master;
}

/* Get a pointer to the master palette.  Modifying its contents will affect this palette.
 */
nes_master_palette * nes_color_palette::master_palette() const
{
	return m_master;
}

/* Get the 32-bit color value in the master color palette that is referenced by the given index.
 * Note that the NES supports color modifications (such as monochrome mode) and so the color
 * returned is the color after those mods are applied.
 */
uint32_t nes_color_palette::color(uint8_t index) const
{
	return m_master->color(color_ref(index));
}

/* Just like the above method, but this returns the actual unmodified color from the palette.  Use
 * this one if you want to use it to change the colors in the master palette.
 */
uint32_t nes_color_palette::actual_color(uint8_t index) const
{
	return m_master->actual_color(color_ref(index));
}
