/* 
 * The piece that will actually do the drawing.  This would be a sort of interface between the NES
 * PPU code and the Qt GUI code (the RomCanvas).
 *
 * This class inherits from QGraphicsItem because it needs to implement the abstract methods paint()
 * and boundingRect().
 */

#include "renderer.hpp"

renderer::renderer()
	: QGraphicsItem(), frame_buffer(boost::extents[320][240])
{
}

renderer::~renderer()
{
}
