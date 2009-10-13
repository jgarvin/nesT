#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include <QApplication>

#include <boost/program_options.hpp>

#include <SDL/SDL.h>

#include "main_window.hpp"
#include "rom.hpp"

namespace po = boost::program_options;

bool SDLSetup()
{
	bool result = true;

	// we'll init the subsystems when we need them
	if(SDL_Init(0) == -1)
	{
		std::cout << "SDL init error: " << SDL_GetError() << std::endl;
		result = false;
	}
	return result;
}

// We'll use toast::logger, this is just to make sure boost is linking right
class Log {
public:
	Log(std::string const & filename)
		: path_(filename),
		  logstream_(filename.c_str())
	{
	}

	~Log()
	{
		logstream_.close();
	}
	
	void writeToLog(std::string const & toLog)
	{
		logstream_ << toLog << std::endl;
	}

private:
	std::string path_;
	std::ofstream logstream_;
};

int main(int argc, char *argv[])
{
	int result = -1;

	Log log("nesTLog.txt");
	log.writeToLog("nesT starting up...");

    try {
        po::options_description desc("nesT allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("rom", po::value<std::string>(), "NES rom to load")
        ;

        po::variables_map vm;        
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);    

        if (vm.count("help")) {
			std::cout << desc << "\n";
            return 1;
        }

        if (vm.count("rom")) {
			std::cout << "Loading rom: " 
					  << vm["rom"].as<std::string>() << ".\n";

			std::ifstream rom_file(vm["rom"].as<std::string>().c_str(), std::ios::in | std::ios::binary);
			if(!rom_file.is_open())
				throw std::runtime_error("Couldn't open specified ROM file. Make sure the file exists and you have proper permissions.");
			rom cmd_line_rom(rom_file);
			std::vector<sprite*> sprites = cmd_line_rom.construct_sprites();
			for(std::vector<sprite*>::iterator i = sprites.begin(); i != sprites.end(); ++i) {
				//std::cout << (*i)->to_string();
				//std::cout << std::endl << std::endl;
			}
			for(std::vector<sprite*>::iterator i = sprites.begin(); i != sprites.end(); ++i)
				delete *i;
        } else {
			std::cout << "No ROM selected.\n";
        }
    }
    catch(std::exception& e) {
		std::cerr << "error: " << e.what() << "\n";
        return 1;
    }

	log.writeToLog("Setting up SDL...");
	if(!SDLSetup())
	{
		log.writeToLog("SDL init error: " + std::string(SDL_GetError()));
		SDL_ClearError();
	}

	log.writeToLog("Setting up QT4...");
	QApplication app(argc, argv);

	main_window window;
	window.resize(640, 480);
	window.show();

	result = app.exec();
	SDL_Quit();
	return result;
}
