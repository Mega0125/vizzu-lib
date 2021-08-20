#include "stylesheet.h"

using namespace Vizzu;
using namespace Vizzu::Styles;

Chart Sheet::getFullParams(const Diag::DiagramOptionsPtr &options)
{
	this->options = options.get();

	calcDefaults();

	return Base::getFullParams();
}

void Sheet::calcDefaults()
{
	setAxis();
	setMarkers();
	setData();
}

void Sheet::setAxis()
{
	setAxisLabels();
	setAxisTitle();
}

void Sheet::setAxisLabels()
{
	if (options->polar.get())
	{
		auto &def = defaultParams.plot.xAxis.label;
		def.position = AxisLabel::Position::max_edge;
		def.side = AxisLabel::Side::positive;
	}
}

void Sheet::setAxisTitle()
{
	if (options->polar.get())
	{
		auto &def = defaultParams.plot.xAxis.title;
		def.position = AxisTitle::Position::max_edge;
		def.side = AxisTitle::Side::negative;
	}
}

void Sheet::setMarkers()
{
	setMarkerLabels();

	if (!options->getScales().anyAxisSet() && 
		options->shapeType.get() == Diag::ShapeType::Type::Rectangle)
	{
		defaultParams.plot.marker.borderWidth = 0.5;
		defaultParams.plot.marker.borderOpacity = 0.7;
	}
}

void Sheet::setMarkerLabels()
{
	auto &def = defaultParams.plot.marker.label;

	if (options->getScales().bothAxisSet()
		&& (
			options->shapeType.get() == Diag::ShapeType::Type::Line
			|| options->shapeType.get() == Diag::ShapeType::Type::Area
			|| (
				options->shapeType.get() == Diag::ShapeType::Type::Rectangle
				&& options->subAxis().discreteCount() == 0
				)
			)	
		)
	{
		def.position = options->horizontal.get() 
			? MarkerLabel::Position::top
			: MarkerLabel::Position::right;
	}

	const auto &pos =
		(activeParams && activeParams->plot.marker.label.position)
		? activeParams->plot.marker.label.position
		: def.position;

	if (pos == MarkerLabel::Position::center)
	{
		def.filter = Gfx::ColorTransform::Lightness(0.7);
	}
}

void Sheet::setData()
{
	defaultParams.data.circleMinRadius = 
		options->getScales().at(Diag::Scale::Type::Size).isEmpty()
		? 7 : 4;
}
