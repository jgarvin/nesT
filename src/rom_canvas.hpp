/*
 * This is the drawing surface for nesT.  This is the black area on the main window where ROMs will
 * be displayed.
 */

#ifndef INCLUDED_NEST_ROM_CANVAS_HPP
#define INCLUDED_NEST_ROM_CANVAS_HPP

#include <SDL/SDL.h>
#include <QWidget>
#include <QResizeEvent>

class rom_canvas : public QWidget
{
	Q_OBJECT

public:
	explicit rom_canvas(QWidget *parent);
	virtual ~rom_canvas();

	virtual void set_size(int w, int h);
	virtual void update();

protected:
	SDL_Surface *m_screen;
	QWidget *m_parent;

protected slots:
	void test();

private:
	static const int DEFAULT_WIDTH  = 640;
	static const int DEFAULT_HEIGHT = 480;
	static const int DEFAULT_BPP    = 32;
};

#endif // INCLUDED_NEST_ROM_CANVAS_HPP
