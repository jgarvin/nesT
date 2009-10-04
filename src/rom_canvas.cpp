/*
 * This is the drawing surface for nesT.  This is the black area on the main window where ROMs will
 * be displayed.
 *
 */

#include "rom_canvas.hpp"
#include <iostream>
#include <cstdlib>
#include <QString>

rom_canvas::rom_canvas(QWidget *parent)
	: QWidget(parent)
{
	m_parent = parent;

	// a hack I found online to get the SDL surface to appear in our own window
	QString id;
	id.setNum(parent->winId());
	setenv("SDL_WINDOWID", id.toAscii().data(), 1);
	SDL_InitSubSystem(SDL_INIT_VIDEO);

	m_screen = SDL_SetVideoMode(m_parent->width(), m_parent->height(), DEFAULT_BPP, SDL_SWSURFACE);

	if(!m_screen)
		std::cout << "couldn't create screen" << std::endl;

	SDL_LockSurface(m_screen);
	SDL_FillRect(m_screen, NULL, 0x00FF0000);
	SDL_UnlockSurface(m_screen);
	SDL_UpdateRect(m_screen, 0, 0, 0, 0);
}

rom_canvas::~rom_canvas()
{
	// do NOT release screen here; that's done when SDL_Quit() is called in main().
}

void rom_canvas::test()
{
	SDL_LockSurface(m_screen);
	SDL_FillRect(m_screen, NULL, 0x00FF0000);
	SDL_UnlockSurface(m_screen);
	SDL_UpdateRect(m_screen, 0, 0, 0, 0);
}

void rom_canvas::set_size(int w, int h)
{
	m_screen = SDL_SetVideoMode(w, h, DEFAULT_BPP, SDL_SWSURFACE);
}

void rom_canvas::update()
{
	SDL_LockSurface(m_screen);
	SDL_FillRect(m_screen, NULL, 0x00FF0000);
	SDL_UnlockSurface(m_screen);
	SDL_UpdateRect(m_screen, 0, 0, 0, 0);
}

