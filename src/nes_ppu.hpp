#ifndef INCLUDED_NEST_NES_PPU_HPP
#define INCLUDED_NEST_NES_PPU_HPP

#include <cstdint>

//#include "nes_ppu_status.hpp"

class nes_ppu {
private:
	// Registers
	
	char access_vram_byte(uint16_t i) const; // 64KB addressable
	char video_ram[16384];

	union
	{
		char raw_data[256];
		struct
		{
			uint32_t y_pos:8;      // top of sprite; the NES adds 1 to this
			uint32_t tile_num:8;   // for 8x16 sprites, LSb which bank to use
			uint32_t palette:2;
			uint32_t unused:3;
			uint32_t priority:1;   // 0: in front of BG; 1: behind BG
			uint32_t flip_hor:1;
			uint32_t flip_ver:1;
			uint32_t x_pos:8;
		} attribute[64];
	} sprite_ram;


	std::uint16_t program_counter_;
	std::uint8_t stack_pointer_;
	std::uint8_t accumulator_;
	std::uint8_t index_x_;
	std::uint8_t index_y_; // can't affect stack pointer
//	nes_ppu_status status_;
};

#endif
