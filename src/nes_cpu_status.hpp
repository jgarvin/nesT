#ifndef INCLUDED_NEST_NES_CPU_STATUS_HPP
#define INCLUDED_NEST_NES_CPU_STATUS_HPP

#include <cstdint>

class nes_cpu_status {
public:
	bool carry() const;
	bool zero() const;
	bool interrupt_disable() const;
	bool decimal_mode() const;
	bool break_command() const;
	bool overflow() const;
	bool negative() const;

private:
	std::uint8_t raw_register_;
};

#endif
