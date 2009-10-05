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
	: QGraphicsView(parent)
{	
	scene = new QGraphicsScene(this);
	setScene(scene);
	
	scene->addText("Hello, world!");
}

rom_canvas::~rom_canvas()
{
	// do NOT release screen here; that's done when SDL_Quit() is called in main().
}

void rom_canvas::test()
{
}

