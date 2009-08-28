#include <iostream>
#include <string>

#include <QApplication>
#include <QPushButton>

#include <boost/filesystem/fstream.hpp>

#include <SDL/SDL.h>

void SDLTest()
{
	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_Quit();
}

// We'll use toast::logger, this is just to make sure boost is linking right
using namespace boost::filesystem;
class Log {
public:
	Log(std::string const & filename)
		: path_(filename),
		  logstream_(path_)
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
	path path_;
	ofstream logstream_;
};

int main(int argc, char *argv[])
{
	Log log("nesTLog.txt");
	log.writeToLog("nesT starting up...");

	log.writeToLog("testing SDL....");
	SDLTest();

	log.writeToLog("testing QT4....");
	QApplication app(argc, argv);

	QPushButton hello("Hello world!");
	hello.resize(100, 30);

	hello.show();
	return app.exec();
}
