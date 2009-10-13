#include "mirror_mode.hpp"

std::ostream& operator<<(std::ostream& s, mirror_mode const& mode)
{
	s << mode.to_string();

	return s;
}



