#ifndef DRAWORIENTEDLABEL_H
#define DRAWORIENTEDLABEL_H

#include "drawingcontext.h"

namespace Vizzu
{
namespace Draw
{

class drawOrientedLabel : private DrawingContext
{
public:
	drawOrientedLabel(
		const DrawingContext &context,
		const std::string &text,
		const Geom::Line &labelPos,
		const Styles::OrientedLabel &labelStyle,
		const Util::EventDispatcher::event_ptr &event,
		double centered,
		const Gfx::Color &textColor,
		const Gfx::Color &bgColor);
};

}
}

#endif
