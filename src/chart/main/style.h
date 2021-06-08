#ifndef STYLE_H
#define STYLE_H

#include "base/anim/interpolated.h"
#include "base/math/fuzzybool.h"
#include "base/geom/rect.h"
#include "base/gfx/color.h"
#include "base/gfx/font.h"
#include "base/gfx/colorgradient.h"
#include "base/gfx/colorpalette.h"
#include "base/gfx/colortransform.h"
#include "base/gui/accessories.h"
#include "base/refl/enum.h"
#include "base/style/param.h"
#include "base/text/smartstring.h"
#include "chart/generator/colorbuilder.h"

namespace Vizzu
{
namespace Styles
{

template <typename T> using Param = ::Style::Param<T>;

class Enum(Visibility)(hidden, visible);
class Enum(Overflow)(hidden, visible);

struct Padding
{
	Param<double> paddingTop;
	Param<double> paddingRight;
	Param<double> paddingBottom;
	Param<double> paddingLeft;

	explicit operator GUI::Margin() const {
		return { *paddingTop, *paddingLeft,
			*paddingBottom,	*paddingRight };
	}

	Geom::Size paddingSize() const {
		return Geom::Size(
			*paddingRight + *paddingLeft,
		    *paddingTop + *paddingBottom);
	}

	Geom::Point paddingPos() const {
		return Geom::Point(*paddingLeft, *paddingTop);
	}

	Geom::Rect contentRect(const Geom::Rect &rect) const {
		return Geom::Rect(
			rect.pos + paddingPos(),
			Geom::Size(rect.size - paddingSize()).positive());
	}

	void visit(auto &visitor)
	{
		visitor
			(paddingTop, "paddingTop")
			(paddingBottom, "paddingBottom")
			(paddingLeft, "paddingLeft")
			(paddingRight, "paddingRight");
	}
};

struct Font {
	Param<::Anim::String> fontFamily;
	Param<Gfx::Font::Style> fontStyle;
	Param<Gfx::Font::Weight> fontWeight;
	Param<double> fontSize;

	explicit operator Gfx::Font() const
	{
		return Gfx::Font(fontFamily->values[0].value,
			*fontStyle, *fontWeight, *fontSize);
	}

	void visit(auto &visitor)
	{
		visitor
			(fontFamily, "fontFamily")
			(fontStyle, "fontStyle")
			(fontWeight, "fontWeight")
			(fontSize, "fontSize");
	}
};

struct Text {
	class Enum(TextAlign)(center, left, right);

	Param<Gfx::Color> color;
	Param<Anim::Interpolated<TextAlign>> textAlign;
	Param<Gfx::Color> backgroundColor;
	Param<Anim::Interpolated<Overflow>> overflow;
	Param<::Text::NumberFormat> numberFormat;

	void visit(auto &visitor)
	{
		visitor
			(color, "color")
			(textAlign, "textAlign")
			(backgroundColor, "backgroundColor")
			(overflow, "overflow")
			(numberFormat, "numberFormat");
	}
};

struct Box {
	Param<Gfx::Color> backgroundColor;
	Param<Gfx::Color> borderColor;
	Param<double> borderWidth;

	void visit(auto &visitor)
	{
		visitor
		    (backgroundColor, "backgroundColor")
		    (borderColor, "borderColor")
		    (borderWidth, "borderWidth");
	}
};

struct Label : Padding, Font, Text
{

	void visit(auto &visitor)
	{
		Padding::visit(visitor);
		Font::visit(visitor);
		Text::visit(visitor);
	}

};

struct Tick {
	//todo> top, bottom, both
	class Enum(Position)(outside, inside, center);

	Param<Gfx::Color> color;
	Param<double> lineWidth;
	Param<double> length;
	Param<::Anim::Interpolated<Position>> position;

	void visit(auto &visitor)
	{
		visitor
			(color, "color")
			(lineWidth, "lineWidth")
			(length, "length")
			(position, "position");
	}
};

struct Guide
{
	Param<Gfx::Color> color;
	Param<double> lineWidth;

	void visit(auto &visitor)
	{
		visitor
			(color, "color")
			(lineWidth, "lineWidth");
	}
};

struct Interlacing
{
	Param<Gfx::Color> color;

	void visit(auto &visitor)
	{
		visitor
			(color, "color");
	}
};

struct Axis
{
	Param<Gfx::Color> color;
	Label title;
	Label label;
	Tick ticks;
	Guide guides;
	Interlacing interlacing;

	void visit(auto &visitor)
	{
		visitor
			(color, "color")
			(title, "title")
			(label, "label")
			(ticks, "ticks")
			(guides, "guides")
			(interlacing, "interlacing");
	}
};

struct MarkerLabel : Label
{
	class Enum(Position)(below, center, above);
	class Enum(Format)(valueFirst, categoriesFirst);

	Param<::Anim::Interpolated<Position>> position;
	Param<Gfx::ColorTransform> filter;
	Param<Format> format;

	void visit(auto &visitor)
	{
		Label::visit(visitor);
		visitor
			(position, "position")
			(filter, "filter")
			(format, "format");
	}
};

struct Marker
{
	class Enum(RenderingOrder)(forward,reverse);
	class Enum(BorderOpacityMode)(straight, premultiplied);

	Param<double> borderWidth;
	Param<double> borderOpacity;
	Param<Anim::Interpolated<BorderOpacityMode>> borderOpacityMode;
	Param<double> fillOpacity;
	Param<RenderingOrder> renderingOrder;
	Guide guides;
	MarkerLabel label;

	void visit(auto &visitor)
	{
		visitor
			(borderWidth, "borderWidth")
			(borderOpacity, "borderOpacity")
			(borderOpacityMode, "borderOpacityMode")
			(fillOpacity, "fillOpacity")
			(renderingOrder, "renderingOrder")
			(guides, "guides")
			(label, "label");
	}
};

struct Legend : Padding, Box
{
	struct Marker {
		class Enum(Type)(circle, square);

		Param<::Anim::Interpolated<Type>> type;
		Param<double> size;

		void visit(auto &visitor)
		{
			visitor
				(type, "type")
				(size, "size");
		}
	};

	Param<double> width;
	Label title;
	Label label;
	Marker marker;

	void visit(auto &visitor)
	{
		Padding::visit(visitor);
		Box::visit(visitor);
		visitor
			(width, "width")
		    (title, "title")
		    (label, "label")
		    (marker, "marker");
	}
};

struct Plot : Padding, Box
{
	Marker marker;
	Axis axis;

	void visit(auto &visitor)
	{
		Padding::visit(visitor);
		Box::visit(visitor);
		visitor
			(marker, "marker")
			(axis, "axis");
	}
};

struct Hint
{
	Param<double> visible;

	void visit(auto &visitor) { visitor(visible, "visible"); }
};

struct Data
{
	Param<Gfx::ColorGradient> colorGradient;
	Param<Gfx::ColorPalette> colorPalette;
	Param<double> minLightness;
	Param<double> maxLightness;
	Param<double> lineWidth;
	Param<double> lineMinWidth;
	Param<double> lineMaxWidth;
	Param<double> circleMinRadius;
	Param<double> circleMaxRadius;
	Param<double> barMaxPadding;
	Param<double> barPaddingDecrease;
	Param<double> columnMaxPadding;
	Param<double> columnPaddingDecrease;

	Diag::ColorBuilder::LighnessRange lightnessRange() const
	{
		return { *minLightness, *maxLightness};
	}

	Geom::Point maxPadding() const {
		return { *columnMaxPadding, *barMaxPadding };
	}

	Geom::Point paddingDecrease() const
	{
		return {*columnPaddingDecrease, *barPaddingDecrease };
	}

	void visit(auto &visitor)
	{
		visitor
			(colorGradient, "colorGradient")
			(colorPalette, "colorPalette")
			(minLightness, "maxLightness")
			(lineWidth, "lineWidth")
			(lineMinWidth, "lineMinWidth")
			(lineMaxWidth, "lineMaxWidth")
			(circleMinRadius, "circleMinRadius")
			(circleMaxRadius, "circleMaxRadius")
			(barMaxPadding, "barMaxPadding")
			(barPaddingDecrease, "barPaddingDecrease")
			(columnMaxPadding, "columnMaxPadding")
			(columnPaddingDecrease, "columnPaddingDecrease");
	}
};

struct Chart : Padding, Box, Font
{
	Plot plot;
	Legend legend;
	Label title;
	Hint hint;
	Data data;

	void visit(auto &visitor)
	{
		Padding::visit(visitor);
		Box::visit(visitor);
		Font::visit(visitor);
		visitor
			(plot, "plot")
			(legend, "legend")
			(title, "title")
			(hint, "hint")
			(data, "data");
	}

	static Chart def();
};

}
}

#endif