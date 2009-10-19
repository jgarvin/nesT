/*
 * This is the drawing area on the main window where game graphics will be displayed.
 */

#include "romcanvas.hpp"
#include <iostream>
#include <QString>
#include <QTimer>
#include <QScrollBar>

RomCanvas::RomCanvas(QWidget *parent)
	: QGraphicsView(parent)
{	
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	connect(parent, SIGNAL(resized()), this, SLOT(resize()));

	m_scene = new QGraphicsScene(this);
	m_scene->setSceneRect(0, 0, viewport()->width(), viewport()->height());
	setScene(m_scene);

	m_textRect = new TextRect();
	m_scene->addItem(m_textRect);
}

RomCanvas::~RomCanvas()
{
	delete m_textRect;
}

int RomCanvas::width() const
{
	return viewport()->width();
}

int RomCanvas::height() const
{
	return viewport()->height();
}


/* Display text on screen for the given amount of time in milliseconds.  Default time is 3 seconds.
 * If the given time is 0 or less, the text will stay indefinitely.  Call hide_text() to remove it.
 */
void RomCanvas::displayText(const QString & text, int msecs)
{
	m_textRect->setText(text);
	m_textRect->setTextWidth(width()/2);
	m_textRect->setPos(5, height() - m_textRect->height() - 5);
	
	m_textRect->show();

	if(msecs > 0)
		QTimer::singleShot(msecs, this, SLOT(hide_text()));
}

/* Clear whatever text is being displayed by hiding the widget.
 */
void RomCanvas::hideText()
{
	m_textRect->hide();
}

/* A slot for resizing the canvas.  The viewport resizes with the main window automatically (since
 * it's the central widget), so we can just adjust ourselves to the new viewport size.
 */ 
void RomCanvas::resize()
{
	m_scene->setSceneRect(0, 0, width(), height());
}
