#ifndef INCLUDED_NEST_NES_CPU_HPP
#define INCLUDED_NEST_NES_CPU_HPP

#include "nes_cpu_status.hpp"

class nes_cpu {
private:
	long cycle_count_;
	
	// Registers
	uint16_t program_counter_;
	uint8_t stack_pointer_;
	uint8_t accumulator_;
	uint8_t index_x_;
	uint8_t index_y_; // can't affect stack pointer
	nes_cpu_status status_;
};

#endif
