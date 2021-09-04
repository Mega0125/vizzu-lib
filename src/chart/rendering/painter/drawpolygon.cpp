#include "drawpolygon.h"

#include "base/geom/rect.h"
#include "base/geom/triangle.h"
#include "base/io/log.h"
#include "base/math/interpolation.h"
#include "base/math/statistics.h"

using namespace Geom;
using namespace Gfx;
using namespace Vizzu;
using namespace Vizzu::Draw;

drawPolygon::drawPolygon(const std::array<Point, 4> &ps, const Options &options, ICanvas &canvas)
{
	center = Math::mean(ps);
	boundary = Rect::Boundary(ps).size;

	auto linSize = Size(
	    options.coordSys.verConvert(boundary.x),
	    options.coordSys.verConvert(boundary.y)
	);

	if (options.circ == 1.0 && linSize.isSquare(0.005))
	{
		auto centerConv = options.coordSys.convert(center);
		auto radius = fabs(linSize.x) / 2.0;
		canvas.circle(Geom::Circle(centerConv,radius));
	}
	else
	{
		canvas.beginPolygon();

		Path(ps[0], ps[1], center, linSize, canvas, options).calc();
		Path(ps[1], ps[2], center, linSize, canvas, options).calc();
		Path(ps[2], ps[3], center, linSize, canvas, options).calc();
		Path(ps[3], ps[0], center, linSize, canvas, options).calc();

		canvas.endPolygon();
	}
}

drawPolygon::Path::Path(const Point &p0, const Point &p1,
						Point center, Point linSize,
						ICanvas &canvas,
						const drawPolygon::Options &options)
	: PathSampler(p0, p1, options),
	  options(options), canvas(canvas), linSize(linSize)
{
	linP0 = options.coordSys.convert(p0);
	linP1 = options.coordSys.convert(p1);
	centerConv = options.coordSys.convert(center);
}

void drawPolygon::Path::addPoint(const Point &point)
{
	canvas.addPoint(point);
}

Point drawPolygon::Path::getPoint(double f)
{
	auto linP = Math::interpolate(linP0, linP1, f);
	auto nonlinP =
	    options.coordSys.convert(Math::interpolate(p0, p1, f));

	auto mixedP = Math::interpolate(nonlinP, linP, options.linear);

	return intpToElipse(mixedP, options.circ);
}

Point drawPolygon::Path::intpToElipse(Point point, double factor)
{
	auto projected = projectToElipse(point);
	return Math::interpolate(point, projected, factor);
}

Point drawPolygon::Path::projectToElipse(Point point)
{
	auto fi = (point - centerConv).angle();
	return centerConv + Point::Polar(1, fi) * linSize / 2.0;
}
