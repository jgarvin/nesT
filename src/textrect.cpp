/* 
 * A message box for displaying text directly onto a canvas.
 */

#include <QTextDocument>
#include "textrect.hpp"

TextRect::TextRect(QGraphicsItem *parent, const QString & text)
	: QGraphicsRectItem(parent)
{
	setRect(0, 0, 1, 1);
	
	setFlags(QGraphicsItem::ItemClipsChildrenToShape |
			 QGraphicsItem::ItemDoesntPropagateOpacityToChildren);

	m_text = new QGraphicsTextItem(this);
	setText(text);
	setTextColor(QColor(Qt::black));

	m_fill = new QBrush();
	setFillStyle(Qt::SolidPattern);
	setFillColor(QColor(0, 120, 220, 128));

	m_border = new QPen();
	setBorderWidth(2);
	setBorderColor(QColor("royalblue"));
}

TextRect::~TextRect()
{
	delete m_fill;
	delete m_border;
}

/* Set the text to be displayed. 
 */
void TextRect::setText(const QString & text)
{
	m_text->setPlainText(text);
}

/* Set how wide a line of text can be before it wraps to a new line.  If the text is shorter than
 * the line, the rectangle will be sized to match when displayed.  A width of -1 stops automatic
 * wrapping.
 */
void TextRect::setTextWidth(int w)
{
	m_text->setTextWidth((qreal)w);
}

/* Set the text color.
 */
void TextRect::setTextColor(const QColor & color)
{
	m_text->setDefaultTextColor(color);
}

/* Set the color of the inside of the rectangle.
 */
void TextRect::setFillColor(const QColor & color)
{
	m_fill->setColor(color);
	setBrush(*m_fill);
}

/* Set the pattern used to fill in the rectangle.  See the QT QBrush documentation to view the
 * possible brush styles.  Use Qt::NoBrush to disable filling the rectangle.
 */
void TextRect::setFillStyle(Qt::BrushStyle style)
{
	m_fill->setStyle(style);
	setBrush(*m_fill);
}

/* Set the color of the outside edge of the rectangle.
 */
void TextRect::setBorderColor(const QColor & color)
{
	m_border->setColor(color);
	setPen(*m_border);
}

/* Set the line style of the outside edge of the rectangle.  See the QT QPen documentation to view
 * the possible pen styles.  Use Qt::NoPen to disable the border.
 */
void TextRect::setBorderStyle(Qt::PenStyle style)
{
	m_border->setStyle(style);
	setPen(*m_border);
}

/* Set the width of the outside edge of the rectangle.
 */
void TextRect::setBorderWidth(int w)
{
	m_border->setWidth(w);
	setPen(*m_border);
}	

/* Return the currently set text as a plain text QString.
 */
QString TextRect::text()
{
	return m_text->toPlainText();
}

/* Return the maximum width of the text before is wraps to the next line.
 */
int TextRect::textWidth()
{
	return (int)m_text->textWidth();
}

/* Return how wide the text actually is.  This will be less than the textWidth if the text has not
 * reached the end of the line.
 */
int TextRect::actualTextWidth()
{
	return (int)m_text->document()->idealWidth();
}

/* Return the text color.
 */
QColor TextRect::textColor()
{
	return m_text->defaultTextColor();
}
	
/* Return the color the rectangle was filled with.
 */
QColor TextRect::fillColor()
{
	return brush().color();
}

/* Return the pattern used to fill in the rectangle.
 */
Qt::BrushStyle TextRect::fillStyle()
{
	return brush().style();
}
	
/* Return the color of the outside edge of the rectangle.
 */
QColor TextRect::borderColor()
{
	return pen().color();
}

/* Return the pen style of the outside edge.
 */
Qt::PenStyle TextRect::borderStyle()
{
	return pen().style();
}

/* Return the width of the outside border.
 */
int TextRect::borderWidth()
{
	return pen().width();
}

/* Return the width the rectangle will be with the currently set text.
 */
int TextRect::width()
{
	return (int)actualTextWidth() + 4;
}

/* Return the height of the rectangle with the currently set text.
 */
int TextRect::height()
{
	return (int)m_text->document()->size().height();
}

/* Return the x coordinate of the left edge of the rectangle.
 */
int TextRect::x()
{
	return rect().x();
}

/* Return the y coordinate of the top edge of the rectangle.
 */
int TextRect::y()
{
	return rect().y();
}

void TextRect::show()
{
	setRect(x(), y(), width(), height());
	m_text->setPos(2, 0);

	QGraphicsRectItem::show();
	m_text->show();
}
