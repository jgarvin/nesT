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

void SDLTest()
{
	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_Quit();
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
        } else {
			std::cout << "No ROM selected.\n";
        }
    }
    catch(std::exception& e) {
		std::cerr << "error: " << e.what() << "\n";
        return 1;
    }

	log.writeToLog("testing SDL....");
	SDLTest();

	log.writeToLog("testing QT4....");
	QApplication app(argc, argv);

	main_window window;
	window.resize(640, 480);
	window.show();
/*
	QPushButton hello("Hello world!");
	hello.resize(100, 30);

	hello.show();
*/
	return app.exec();
}
