#ifndef INCLUDED_NEST_MIRROR_MODE_HPP
#define INCLUDED_NEST_MIRROR_MODE_HPP

class mirror_mode
{
public:
	virtual ~mirror_mode() {}
};

class horizontal_mirror_mode : public mirror_mode {};

class vertical_mirror_mode : public mirror_mode {};

#endif

