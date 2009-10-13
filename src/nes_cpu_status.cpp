#include "nes_cpu_status.hpp"

bool nes_cpu_status::carry() const
{
	return raw_register_ & 1;
}

bool nes_cpu_status::zero() const
{
	return raw_register_ & 2;
}

bool nes_cpu_status::interrupt_disable() const
{
	return raw_register_ & 4;
}

bool nes_cpu_status::decimal_mode() const
{
	return raw_register_ & 8;
}

bool nes_cpu_status::break_command() const
{
	return raw_register_ & 16;
}

bool nes_cpu_status::overflow() const
{
	return raw_register_ & 32;
}

bool nes_cpu_status::negative() const
{
	return raw_register_ & 64;
}
