#ifndef DRAWAXES_H
#define DRAWAXES_H

#include "drawingcontext.h"
#include "guides.h"
#include "base/geom/line.h"

namespace Vizzu
{
namespace Draw
{

class drawAxes : private DrawingContext
{
public:
	drawAxes(const DrawingContext &context, const Guides &guides);

	void drawBase();
	void drawLabels();

private:
	const Guides &guides;

	Geom::Line getAxis(Diag::Scale::Type axisIndex) const;
	void drawAxis(Diag::Scale::Type axisIndex,
	    const Gfx::Color &lineBaseColor);
	void drawTitle(Diag::Scale::Type axisIndex);
	void drawDiscreteLabels(bool horizontal);
};

}
}

#endif