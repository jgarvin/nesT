#ifndef INCLUDED_NEST_NES_PPU_HPP
#define INCLUDED_NEST_NES_PPU_HPP

#include <cstdint>

//#include "nes_ppu_status.hpp"

class nes_ppu {
private:
	// Registers
	
	char access_vram_byte(uint16_t i) const; // 64KB addressable
	char video_ram[16384];

	char sprite_ram[256];

	std::uint16_t program_counter_;
	std::uint8_t stack_pointer_;
	std::uint8_t accumulator_;
	std::uint8_t index_x_;
	std::uint8_t index_y_; // can't affect stack pointer
//	nes_ppu_status status_;
};

#endif
