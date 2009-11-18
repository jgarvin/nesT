/* 
 * The piece that will actually do the drawing.  This would be a sort of interface between the NES
 * PPU code and the Qt GUI code (the RomCanvas).
 *
 * This class inherits from QGraphicsItem because it needs to implement the abstract methods paint()
 * and boundingRect().
 */

#include <QGraphicsItem>
#include <QImage>
#include <QRect>
#include <boost/multi_array.hpp>

#include "nes_color_palette.hpp"

class QPainter;
class QStyleOptionGraphicsItem;

typedef struct sprite_attribute_t
{
	uint32_t y_pos:8;      // top of sprite; the NES adds 1 to this
	uint32_t tile_num:8;   // for 8x16 sprites, LSb which bank to use
	uint32_t palette:2;
	uint32_t unused:3;
	uint32_t priority:1;   // 0: in front of BG; 1: behind BG
	uint32_t flip_hor:1;
	uint32_t flip_ver:1;
	uint32_t x_pos:8;
} sprite_attribute;

typedef struct render_context_t
{
	sprite_attribute *attribute;
	nes_color_palette *palette;
	// how about a post-processor, like a scaler or something?
} render_context;

class renderer : public QGraphicsItem
{
	friend class RomCanvas;

public:
	renderer();
	virtual ~renderer();
	
	virtual void set_resolution(int w, int h);
	
	virtual void render(boost::multi_array<uint8_t, 2> *sprite, render_context *context);

private:
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
					   QWidget *widget = 0);

	boost::multi_array<uint32_t, 2> frame_buffer;

};
