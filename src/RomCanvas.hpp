/*
 * This is the drawing area on the main window where game graphics will be displayed.
 */

#ifndef INCLUDED_NEST_ROM_CANVAS_HPP
#define INCLUDED_NEST_ROM_CANVAS_HPP

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>
#include "TextRect.hpp"

class RomCanvas : public QGraphicsView
{
	Q_OBJECT

public:
	explicit RomCanvas(QWidget *parent = 0);
	virtual ~RomCanvas();
	
	virtual void displayText(const QString & text, int msecs = 3000);
	virtual int width();
	virtual int height();

public slots:
	virtual void resize();
	virtual void hideText();

protected:
	QGraphicsScene *m_scene;
	TextRect *m_textRect;
};

#endif // INCLUDED_NEST_ROM_CANVAS_HPP