/*
 * This is the drawing surface for nesT.  This is the black area on the main window where ROMs will
 * be displayed.
 */

#ifndef INCLUDED_NEST_ROM_CANVAS_HPP
#define INCLUDED_NEST_ROM_CANVAS_HPP

#include <QGraphicsScene>
#include <QGraphicsView>

class rom_canvas : public QGraphicsView
{
	Q_OBJECT

public:
	explicit rom_canvas(QWidget *parent = 0);
	virtual ~rom_canvas();

protected:
	QGraphicsScene *scene;

protected slots:
	void test();
};

#endif // INCLUDED_NEST_ROM_CANVAS_HPP
