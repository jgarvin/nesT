/*
 * Contains an implementation of a single 4-color palette used for for a sprite.  These palletes are
 * really just indices into a master palette, which is implemented elsewhere.  See here for more
 * info: http://wiki.nesdev.com/w/index.php/PPU_palettes
 */

#include <toast/assert.hpp>
#include <cstring>
#include "nes_color_palette.hpp"

/* indices must point to at least 4 values.  We just keep the pointer to master, not the contents.
 */
nes_color_palette::nes_color_palette(nes_master_palette *master, const uint8_t *indices)
{
	TOAST_ASSERT_NOT_NULL(master);
	m_master = master;
	
	if(indices != NULL)
		memcpy((void *)m_pal, (const void *)indices, PALETTE_SIZE);
	else
		memset((void *)m_pal, 0, PALETTE_SIZE);
}

nes_color_palette::~nes_color_palette()
{
}

/* Uses the data in the input to create a colored image in the output.  Returns True when
 * completed.  The input data must be numbers 0-3 to correspond to the indices into this palette.
 * If not, then this function will return False to indicate an error in the resultant image.  Both
 * arrays must have the same dimension sizes for this to work correctly.
 */
bool nes_color_palette::apply_colors(boost::multi_array<uint8_t, 2> *input_data, 
									 boost::multi_array<uint32_t, 2> *output_image)
{
	// get iterators for our rows (x-coordindate)
	boost::multi_array<uint8_t, 2>::iterator  in_itrx  = input_data->begin();
	boost::multi_array<uint32_t, 2>::iterator out_itrx = output_image->begin();

	uint32_t the_color = 0;
	bool result = true;

	for(; in_itrx != input_data->end() && out_itrx != output_image->end(); ++in_itrx, ++out_itrx)
	{
		// get iterators for the columns in the the row (y-coordinate)
		boost::multi_array<uint8_t, 1>::iterator in_itry = (*in_itrx).begin();
		boost::multi_array<uint32_t, 1>::iterator out_itry = (*out_itrx).begin();

		for(; in_itry != (*in_itrx).end() && out_itry != (*out_itrx).end(); ++in_itry, ++out_itry)
		{
			the_color = color(*in_itry);
			
			if(0xFFFFFFFF == the_color)    // index did not reference valid color
				result = false;
			
			*out_itry = the_color;
		}
	}
	return result;
}


/* Change one of the colors in this palette to refer to a different color in the object's master
 * palette.  For example, calling set_color(1, 0x0A) sets color 1 in the palette to refer to 0x0A in
 * the master, which is green in the default master.  Has no effect if index is greater than 3 or if
 * color is greater than the master palette size-1 (63 by default).
 */
void nes_color_palette::set_color_ref(uint8_t index, uint8_t ref)
{
	if(index < PALETTE_SIZE && ref < m_master->size())
		m_pal[index] = ref;
}

/* Get the reference into the master palette where this index points to.  Returns 0xFF (which is
 * invalid) if the index is out of bounds.
 */
uint8_t nes_color_palette::color_ref(uint8_t index) const
{
	return (index < PALETTE_SIZE ? m_pal[index] : 0xFF);
}

/* Set the master color palette.  This is the large palette from which this palette can choose its
 * colors from.  It's up to the caller to figure out what to do with the old palette.  This will
 * throw an exception if you pass in a NULL pointer.
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
