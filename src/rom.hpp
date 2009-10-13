#ifndef INCLUDED_NEST_ROM_HPP
#define INCLUDED_NEST_ROM_HPP

#include <fstream>
#include <string>
#include <vector>

#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>

#include "sprite.hpp"
#include "mirror_mode.hpp"

class rom
{
public:
	rom(std::ifstream& file);

	std::string title() const;
	std::string to_string() const;

	// Up to the calller to delete the sprites
	std::vector<sprite*> construct_sprites(); 

private:
	std::vector<char*> prg_banks();
	std::vector<char*> chr_banks();

	int num_prg_banks() const;
	int num_chr_banks() const;
	int prg_bank_offset(int i) const;
	int chr_bank_offset(int i) const;

	boost::shared_ptr<mirror_mode> stored_mirror_mode() const;
	
	std::vector<char> raw_nes_data_;

	static const int BANK_START_OFFSET = 16;
	static const int PRG_BANK_SIZE = 16384;
	static const int CHR_BANK_SIZE = 8192;

	static const boost::array<char, 4> NORMAL_HEADER;
};

#endif
