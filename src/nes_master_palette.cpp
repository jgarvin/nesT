/*
 * This is an implementation of the 64-color master palette that defines all of the colors the NES
 * has to work with.  The NES has only one of these palettes, but we could theoretically give each
 * sprite its own master palette if we wanted to implement some funky effects.
 *
 * The default colors used in this class are taken from the NES Tech FAQ found here:  
 * http://www.disgruntleddesigner.com/chrisc/NESTechFAQ.html
 *
 */

#include <cstring>
#include <toast/assert.hpp>
#include "nes_master_palette.hpp"

/* colors must point to at least 64 32-bit values.  This will use the default palette if the input
 * is NULL (default).
 */
nes_master_palette::nes_master_palette(const uint32_t *colors)
{
	if(colors)
		memcpy((void *)m_palette, (void *)colors, MASTER_SIZE);
	else
		memcpy((void *)m_palette, (void *)DEFAULT_MASTER, MASTER_SIZE);

	m_emphasis = 0;
	m_grayscale = false;
}

nes_master_palette::~nes_master_palette()
{
}

/* Set the actual color at the given index to the given color.  This sets the unmodified color.
 */
void nes_master_palette::set_color(uint8_t index, uint32_t color)
{
	if(index < MASTER_SIZE)
		m_palette[index] = color;
}

/* Get the currently-set color at the given index.  The NES can modify the colors by emphasizing
 * some or setting a grayscale mode.  This will return the color after these modifications have been
 * applied.
 */
uint32_t nes_master_palette::color(uint8_t index) const
{
	union
	{
		uint32_t value;
		uint8_t  component[4];  // A, R, G, B
	} result;

	result.value = 0xFFFFFFFF;

	if(index < MASTER_SIZE)
	{
		if(m_grayscale)
			result.value = actual_color(index & 0x30);
		else
			result.value = actual_color(index);

		// Emphasis works by actually _deemphasizing_ the other colors, so if emphasis is enabled we
	    // have to darken the components that are not emphasized.
		if(m_emphasis)
		{
			uint8_t emp = m_emphasis;
			
			// oddly enough, we need to darken everything if all bits are set...
			if(emp & (EMPHASIS_RED | EMPHASIS_GREEN | EMPHASIS_BLUE))
				emp = 0;

			if(!(emp & EMPHASIS_RED))
				result.component[1] = result.component[1] / 4;
			if(!(emp & EMPHASIS_GREEN))
				result.component[2] = result.component[2] / 4;
			if(!(emp & EMPHASIS_BLUE))
				result.component[3] = result.component[3] / 4;
		}
	}
	return result.value;
}

/* Like the above method, but returns the unmodified palette color.  Use this if you want to modify
 * the color and place it back into the palette.
 */
uint32_t nes_master_palette::actual_color(uint8_t index) const
{
	return (index < MASTER_SIZE ? m_palette[index] : 0xFFFFFFFF);
}

/* Copy the values at the given pointer to this palette.  The pointed-to palette must have 64 colors
 * or else you'll get garbage in the palette.  Throws an exception if you pass in a NULL pointer.
 */
void nes_master_palette::set_master(const uint32_t *colors)
{
	TOAST_ASSERT_NOT_NULL(colors);
	memcpy((void *)m_palette, (void *)colors, MASTER_SIZE);
}

/* Copy the values in this palette to the buffer.  The buffer must be able to hold at least 64
 * 32-bit values.
 */
void nes_master_palette::copy_master(uint32_t *buffer) const
{
	TOAST_ASSERT_NOT_NULL(buffer);
	memcpy((void *)buffer, (void *)m_palette, MASTER_SIZE);
}

/* Copy the default palette into the buffer.  The buffer must be able to hold at least 64 32-bit
 * values.
 */
void nes_master_palette::copy_default(uint32_t *buffer) const
{
	TOAST_ASSERT_NOT_NULL(buffer);
	memcpy((void *)buffer, (void *)DEFAULT_MASTER, MASTER_SIZE);
}

/* Reset the master palette back to using the default colors.
 */
void nes_master_palette::reset_to_default()
{
	memcpy((void *)m_palette, (void *)DEFAULT_MASTER, MASTER_SIZE);
}

/* Set the emphasis bits for the corresponding components.  Note that "emphasizing" one component
 * really just deemphasizes the others.  You can mix emphases as well to darken a single component.
 * Setting all bits darkens all colors.
 */
void nes_master_palette::set_emphasis(bool r, bool g, bool b)
{
	m_emphasis = 0;

	if(r)
		m_emphasis |= EMPHASIS_RED;
	if(g)
		m_emphasis |= EMPHASIS_GREEN;
	if(b)
		m_emphasis |= EMPHASIS_BLUE;
}

/* Set grayscale mode on the NES.  Really, all this does is do a bitwise AND on all colors with
 * 0x30.  This means that all colors will look like the one in index 0x00, 0x10, 0x20, or 0x30.  So
 * you'd get some interesting effects if your palette didn't set those to be shades of gray...
 */
void nes_master_palette::set_grayscale(bool enabled)
{
	m_grayscale = enabled;
}

/* Get the emphasis bits returned as the 3 least significant bits of this result, like this:
 *    7-3    2      1     0
 * [unused][blue][green][red]
 */
uint8_t nes_master_palette::emphasis() const
{
	return m_emphasis;
}

/* Get whether or not grayscale mode is enabled.
 */
bool nes_master_palette::grayscale() const
{
	return m_grayscale;
}

/* Get the size of the master palette.  It is always 64 for the NES.
 */
uint8_t nes_master_palette::size() const
{
	return MASTER_SIZE;
}

// Note to self:  an alpha value of 0xFF is opaque...
const uint32_t nes_master_palette::DEFAULT_MASTER[MASTER_SIZE] =
{
	0xFF808080, 0xFF003DA6, 0xFF0012B0, 0xFF440096,
	0xFFA1005E, 0xFFC70028, 0xFFBA0600, 0xFF8C1700,
	0xFF5C2F00, 0xFF104500, 0xFF054A00, 0xFF00472E,
	0xFF004166, 0xFF000000, 0xFF050505, 0xFF050505,
	0xFFC7C7C7, 0xFF0077FF, 0xFF2155FF, 0xFF8237FA,
	0xFFEB2FB5, 0xFFFF2950, 0xFFFF2200, 0xFFD63200,
	0xFFC46200, 0xFF358000, 0xFF058F00, 0xFF008A55,
	0xFF0099CC, 0xFF212121, 0xFF090909, 0xFF090909,
	0xFFFFFFFF, 0xFF0FD7FF, 0xFF69A2FF, 0xFFD480FF,
	0xFFFF45F3, 0xFFFF618B, 0xFFFF8833, 0xFFFF9C12,
	0xFFFABC20, 0xFF9FE30E, 0xFF2BF035, 0xFF0CF0A4,
	0xFF05FBFF, 0xFF5E5E5E, 0xFF0D0D0D, 0xFF0D0D0D,
	0xFFFFFFFF, 0xFFA6FCFF, 0xFFB3ECFF, 0xFFDAABEB,
	0xFFFFA8F9, 0xFFFFABB3, 0xFFFFD2B0, 0xFFFFEFA6,
	0xFFFFF79C, 0xFFD7E895, 0xFFA6EDAF, 0xFFA2F2DA,
	0xFF99FFFC, 0xFFDDDDDD, 0xFF111111, 0xFF111111
};
