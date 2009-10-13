#ifndef INCLUDED_NEST_MIRROR_MODE_HPP
#define INCLUDED_NEST_MIRROR_MODE_HPP

#include <sstream>

class mirror_mode;
std::ostream& operator<<(std::ostream& s, mirror_mode const& mode);

class mirror_mode
{
public:
	virtual ~mirror_mode() {}

protected:
	virtual std::string to_string() const = 0;
	friend std::ostream& operator<<(std::ostream& s, mirror_mode const& mode);
};

class horizontal_mirror_mode : public mirror_mode
{
protected:
	std::string to_string() const { return std::string("Horizontal"); }
};

class vertical_mirror_mode : public mirror_mode
{
protected:
	std::string to_string() const { return std::string("Vertical"); }
};

#endif

