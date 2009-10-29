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
 * or else you'll get garbage in the palette.
 */
void nes_master_palette::set_master(const uint32_t *colors)
{
	if(colors)
		memcpy((void *)m_palette, (void *)colors, MASTER_SIZE);
}

/* Copy the values in this palette to the buffer.  The buffer must be able to hold at least 64
 * 32-bit values.
 */
void nes_master_palette::copy_master(uint32_t *buffer) const
{
	if(buffer)
		memcpy((void *)buffer, (void *)m_palette, MASTER_SIZE);
}

/* Copy the default palette into the buffer.  The buffer must be able to hold at least 64 32-bit
 * values.
 */
void nes_master_palette::copy_default(uint32_t *buffer) const
{
	if(buffer)
		memcpy((void *)buffer, (void *)DEFAULT_MASTER, MASTER_SIZE);
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

const uint32_t nes_master_palette::DEFAULT_MASTER[MASTER_SIZE] =
{
	0x00808080, 0x00003DA6, 0x000012B0, 0x00440096,
	0x00A1005E, 0x00C70028, 0x00BA0600, 0x008C1700,
	0x005C2F00, 0x00104500, 0x00054A00, 0x0000472E,
	0x00004166, 0x00000000, 0x00050505, 0x00050505,
	0x00C7C7C7, 0x000077FF, 0x002155FF, 0x008237FA,
	0x00EB2FB5, 0x00FF2950, 0x00FF2200, 0x00D63200,
	0x00C46200, 0x00358000, 0x00058F00, 0x00008A55,
	0x000099CC, 0x00212121, 0x00090909, 0x00090909,
	0x00FFFFFF, 0x000FD7FF, 0x0069A2FF, 0x00D480FF,
	0x00FF45F3, 0x00FF618B, 0x00FF8833, 0x00FF9C12,
	0x00FABC20, 0x009FE30E, 0x002BF035, 0x000CF0A4,
	0x0005FBFF, 0x005E5E5E, 0x000D0D0D, 0x000D0D0D,
	0x00FFFFFF, 0x00A6FCFF, 0x00B3ECFF, 0x00DAABEB,
	0x00FFA8F9, 0x00FFABB3, 0x00FFD2B0, 0x00FFEFA6,
	0x00FFF79C, 0x00D7E895, 0x00A6EDAF, 0x00A2F2DA,
	0x0099FFFC, 0x00DDDDDD, 0x00111111, 0x00111111
};
