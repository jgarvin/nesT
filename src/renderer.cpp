/* 
 * The piece that will actually do the drawing.  This would be a sort of interface between the NES
 * PPU code and the Qt GUI code (the RomCanvas).
 *
 * This class inherits from QGraphicsItem because it needs to implement the abstract methods paint()
 * and boundingRect().
 */

#include <QImage>
#include "renderer.hpp"

renderer::renderer()
	: QGraphicsItem(), m_framebuffer(boost::extents[NES_WIDTH][NES_HEIGHT])
{
	m_width  = NES_WIDTH;
	m_height = NES_HEIGHT;
}

renderer::~renderer()
{
}

/* Change the resolution of the final displayed imaged.  The does not change the framebuffer size,
 * but instead causes the image to be scaled up at paint time.
 */
void renderer::set_resolution(uint32_t w, uint32_t h)
{
	m_width = w;
	m_height = h;
	prepareGeometryChange();            // tells Qt that the object's size has changed
}

// TODO: this currently ignores the flip bits and priority in the attribute.  Add that later.  
/* Renders the given sprite to the renderer's internal framebuffer.  The framebuffer stores the data
 * until it is displayed using the paint() methods (called by a QGraphicsView object).
 */
void renderer::render(boost::multi_array<uint8_t, 2> *sprite, render_context *context)
{
	boost::multi_array<uint32_t, 2> colored_sprite(boost::extents[sprite->size()][sprite[0].size()]);
	auto cs_x = colored_sprite.begin();
	auto fb_x = m_framebuffer.begin() + (context->attribute->x_pos);

	context->palette->apply_colors(sprite, &colored_sprite);

	for(; cs_x < colored_sprite.end() && fb_x < m_framebuffer.end(); ++cs_x, ++fb_x)
	{
		auto cs_y = cs_x->begin();
		auto fb_y = fb_x->begin() + (context->attribute->y_pos) + 1;  // NES hardware adds 1

		for(; cs_y < cs_x->end() && fb_y < fb_x->end(); ++cs_y, ++fb_y)
			*fb_y = *cs_y;
	}		
}

///
/// Private methods
///

/* Returns the bounding rectangle of the drawn object.  Here, we're just going to draw the whole
 * framebuffer, so we can simply give the rectangle coresponding to its borders.
 */
QRectF renderer::boundingRect() const
{
	return QRectF(0, 0, m_width, m_height);
}

/* Do the actual drawing.  Called by RomCanvas (which is subbed from QGraphicsView).
 */
void renderer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QImage image((const uchar *)m_framebuffer.data(), NES_WIDTH, NES_HEIGHT, 4,
				 QImage::Format_ARGB32);

// TODO:  We'd probably want to call any image filters (scalers, shaders, etc.) here..

	painter->drawImage(QRectF(0, 0, m_width, m_height), image);  // image scaled to rectangle
}
