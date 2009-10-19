/* 
 * A message box for displaying text directly onto a canvas.
 */

#ifndef INCLUDED_NEST_TEXT_RECT_HPP
#define INCLUDED_NEST_TEXT_RECT_HPP

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QString>
#include <QBrush>
#include <QPen>
#include <QColor>

class TextRect : public QGraphicsRectItem
{
public:
	TextRect(QGraphicsItem *parent = 0, const QString & text = "");
	virtual ~TextRect();

	void setText(const QString & text);
	void setTextWidth(int w);
	void setTextColor(const QColor & color);

	void setFillColor(const QColor & color);
	void setFillStyle(Qt::BrushStyle style);
	
	void setBorderColor(const QColor & color);
	void setBorderStyle(Qt::PenStyle style);
	void setBorderWidth(int w);
	

	QString text() const;
	int textWidth() const;
	int actualTextWidth() const;
	QColor textColor() const;
	
	QColor fillColor() const;
	Qt::BrushStyle fillStyle() const;
	
	QColor borderColor() const;
	Qt::PenStyle borderStyle() const;
	int borderWidth() const;

	int width() const;
	int height() const;
	int x() const;
	int y() const;

	void show();

protected:
	QGraphicsTextItem *m_text;
	QBrush *m_fill;
	QPen   *m_border;

private:
	// nothing
};

#endif  // INCLUDED_NEST_TEXT_RECT_HPP
