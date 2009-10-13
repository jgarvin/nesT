#include "nes_ppu.hpp"

char nes_ppu::access_byte(uint16_t i) const
{
	return video_ram[i % 16384]; // On NES wraps around
}
