#ifndef DRAWINGCONTEXT_H
#define DRAWINGCONTEXT_H

#include "base/gfx/canvas.h"
#include "chart/generator/diagram.h"
#include "chart/main/style.h"

#include "painter/coordinatesystem.h"
#include "drawoptions.h"
#include "painter/painter.h"

namespace Vizzu
{
namespace Draw
{

class DrawingContext
{
public:
	DrawingContext(const Geom::Rect &rect,
	    const Diag::Diagram &diagram,
	    Gfx::ICanvas &canvas,
	    const DrawOptions &drawOptions,
	    const Styles::Chart &style) :
	    drawOptions(drawOptions),
	    diagram(diagram),
	    canvas(canvas),
	    painter(dynamic_cast<IPainter &>(canvas)),
	    options(*diagram.getOptions()),
	    style(style)
	{
		coordSys = CoordinateSystem(style.plot.contentRect(rect),
		    options.angle.get(),
		    options.polar.get(),
			diagram.keepAspectRatio);

		painter.setCoordSys(coordSys);
	}

	const DrawOptions &drawOptions;
	const Diag::Diagram &diagram;
	CoordinateSystem coordSys;
	Gfx::ICanvas &canvas;
	IPainter &painter;
	const Diag::DiagramOptions &options;
	const Styles::Chart &style;
};

}
}

#endif