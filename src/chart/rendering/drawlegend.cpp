#include "drawlegend.h"

#include "base/gfx/draw/roundedrect.h"
#include "chart/generator/colorbuilder.h"
#include "chart/rendering/drawlabel.h"
#include "chart/rendering/drawbackground.h"

using namespace Vizzu;
using namespace Vizzu::Draw;

drawLegend::drawLegend(const Geom::Rect &rect,
    const Diag::Diagram &diagram,
    Gfx::ICanvas &canvas,
    Diag::Scale::Type scaleType,
    double weight) :
    diagram(diagram),
    canvas(canvas),
    type(scaleType),
    weight(weight),
    style(diagram.getStyle().legend)
{
	contentRect = style.contentRect(rect);
	itemHeight = drawLabel::getHeight(style.label, canvas);
	titleHeight = drawLabel::getHeight(style.title, canvas);

	drawBackground(rect, canvas, style);

	if (type < Diag::Scale::Type::id_size)
	{
		const auto axis = diagram.axises.at(type);
		const auto discreteAxis = diagram.discreteAxises.at(type);

		if ((double)discreteAxis.enabled > 0)
			drawDiscrete(discreteAxis);

		if ((double)axis.enabled > 0) drawContinous(axis);
	}
}

void drawLegend::drawTitle(const std::string &title)
{
	auto rect = contentRect;
	rect.size.y += titleHeight;
	drawLabel(rect, title, style.title, canvas, true, weight * enabled);
}

void drawLegend::drawDiscrete(const Diag::DiscreteAxis &axis)
{
	enabled = (double)axis.enabled;

	drawTitle(axis.title);

	for (const auto &value : axis) if (value.second.weight > 0)
	{
		auto itemRect = getItemRect(value.second.range.getMin());
		if (itemRect.y().getMax() > contentRect.y().getMax()) break;
		auto alpha = value.second.weight * weight * enabled;
		auto markerColor = value.second.color * alpha;
		drawMarker(markerColor, getMarkerRect(itemRect));
		drawLabel(getLabelRect(itemRect), value.second.label,
			style.label, canvas, true, alpha);
	}
}

Geom::Rect drawLegend::getItemRect(double index) const
{
	Geom::Rect res = contentRect;
	res.pos.y += titleHeight + index * itemHeight;
	res.size.y = itemHeight;
	if (res.size.x < 0) res.size.x = 0;
	return res;
}

Geom::Rect drawLegend::getMarkerRect(const Geom::Rect &itemRect) const
{
	Geom::Rect res = itemRect;
	res.pos.y += itemHeight / 2.0 - *style.marker.size / 2.0;
	res.size = Geom::Size::Square(*style.marker.size);
	return res;
}

Geom::Rect drawLegend::getLabelRect(const Geom::Rect &itemRect) const
{
	Geom::Rect res = itemRect;
	res.pos.x += *style.marker.size;
	res.size.x -= std::max(0.0, res.size.x - *style.marker.size);
	return res;
}

void drawLegend::drawMarker(Gfx::Color color, const Geom::Rect &rect)
{
	canvas.setBrushColor(color);
	canvas.setLineColor(color);

	auto radius = diagram.getStyle().legend.marker.type
		->factor(Styles::Legend::Marker::Type::circle)
	    * rect.size.minSize() / 2.0;

	Gfx::Draw::RoundedRect(canvas, rect, radius);
}

void drawLegend::drawContinous(const Diag::Axis &axis)
{
	enabled = (double)axis.enabled;

	drawTitle(axis.title);

	extremaLabel(axis.range.getMax(), 0);
	extremaLabel(axis.range.getMin(), 5);

	auto bar = getBarRect();

	using ST = Diag::Scale::Type;
	switch (type)
	{
	case ST::Color: colorBar(bar); break;
	case ST::Lightness: lightnessBar(bar); break;
	case ST::Size: sizeBar(bar); break;
	default: break;
	}
}

void drawLegend::extremaLabel(double value, int pos)
{
	auto format = *style.label.numberFormat;
	auto text = Text::SmartString::fromNumber(value, format);
	auto itemRect = getItemRect(pos);
	drawLabel(getLabelRect(itemRect), text, style.label, canvas, true,
		weight * enabled);
}

void drawLegend::colorBar(const Geom::Rect &rect)
{
	canvas.setBrushGradient(rect.leftSide(),
	    *diagram.getStyle().data.colorGradient * (weight * enabled));
	canvas.setLineColor(Gfx::Color::Transparent());
	canvas.setLineWidth(0);
	canvas.rectangle(rect);
}

void drawLegend::lightnessBar(const Geom::Rect &rect)
{
	Gfx::ColorGradient gradient;
	const auto &style = diagram.getStyle().data;

	auto range = style.lightnessRange();
	const auto &palette = *style.colorPalette;
	gradient.stops.push_back(
	    {0.0, Diag::ColorBuilder(range, palette, 0, 0.0).render()});
	gradient.stops.push_back(
	    {0.5, Diag::ColorBuilder(range, palette, 0, 0.5).render()});
	gradient.stops.push_back(
	    {1.0, Diag::ColorBuilder(range, palette, 0, 1.0).render()});

	canvas.setBrushGradient(rect.leftSide(), gradient * (weight * enabled));
	canvas.setLineColor(Gfx::Color::Transparent());
	canvas.setLineWidth(0);
	canvas.rectangle(rect);
}

void drawLegend::sizeBar(const Geom::Rect &rect)
{
	canvas.setBrushColor(Gfx::Color::Gray(0.8) * (weight * enabled));
	canvas.beginPolygon();
	canvas.addPoint(rect.bottomLeft());
	canvas.addPoint(rect.bottomRight());
	canvas.addPoint(rect.topSide().center());
	canvas.endPolygon();
}

Geom::Rect drawLegend::getBarRect() const
{
	Geom::Rect res = contentRect;
	res.pos.y += titleHeight + itemHeight / 2.0;
	res.size.y = 5 * itemHeight;
	res.size.x = *style.marker.size;
	return res;
}