/*
 * This is an implementation of the 64-color master palette that defines all of the colors the NES
 * has to work with.  The NES has only one of these palettes, but we could theoretically give each
 * sprite its own master palette if we wanted to implement some funky effects.
 *
 * The default colors used in this class are taken from the NES Tech FAQ found here:  
 * http://www.disgruntleddesigner.com/chrisc/NESTechFAQ.html
 */

#ifndef INCLUDED_NEST_NES_MASTER_PALETTE_HPP
#define INCLUDED_NEST_NES_MASTER_PALETTE_HPP

#include <cstdint>
#include <vector>

class nes_master_palette
{
public:
	nes_master_palette(const std::vector<uint32_t> *colors = NULL);
	~nes_master_palette();

	// colors are in 0xAARRGGBB format
	void set_color(uint8_t index, uint32_t color);
	uint32_t color(uint8_t index) const;
	uint32_t actual_color(uint8_t index) const;
	
	void set_master(const std::vector<uint32_t> *colors);
	void copy_master(std::vector<uint32_t> *dest) const;
	void copy_default(std::vector<uint32_t> *dest) const;
	void reset_to_default();
	
	void set_emphasis(bool r, bool g, bool b);
	void set_grayscale(bool enabled);
	uint8_t emphasis() const;
	bool grayscale() const;

	uint8_t size() const;

private:
	static const uint8_t MASTER_SIZE = 64;
	std::vector<uint32_t> m_palette;
	
	static const uint8_t EMPHASIS_RED   = 0x01;
	static const uint8_t EMPHASIS_GREEN = 0x02;
	static const uint8_t EMPHASIS_BLUE  = 0x04;
	
	uint8_t m_emphasis;
	bool m_grayscale;

	static const std::vector<uint32_t> DEFAULT_MASTER;
};

#endif // INCLUDED_NEST_NES_MASTER_PALETTE_HPP
