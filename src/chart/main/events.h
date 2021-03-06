#ifndef EVENTS_H
#define EVENTS_H

#include "base/io/log.h"
#include "base/geom/line.h"
#include "base/geom/rect.h"
#include "base/anim/control.h"
#include "base/util/eventdispatcher.h"

namespace Vizzu
{

class Events {
public:
	Events(class Chart &chart);

	struct OnUpdateParam : public Util::EventDispatcher::Params
	{
		::Anim::Duration position;
		double progress;
		OnUpdateParam(const ::Anim::Control &control) {
			position = control.getPosition();
			progress = control.getProgress();
		}
		std::string dataToJson() const override {
			return "{"
				"\"position\":\"" + std::string(position) + "\","
				"\"progress\":" + std::to_string(progress) + 
			"}";
		}
	};

	struct OnRectDrawParam : public Util::EventDispatcher::Params
	{
		Geom::Rect rect;
		OnRectDrawParam(Geom::Rect rect) : rect(rect) {}
		std::string dataToJson() const override {
			return "{\"rect\":" + std::string(rect) + "}";
		}
	};

	struct OnLineDrawParam : public Util::EventDispatcher::Params
	{
		Geom::Line line;
		OnLineDrawParam(Geom::Line line) : line(line) {}
		std::string dataToJson() const override {
			return "{\"line\":" + std::string(line) + "}";
		}
	};

	Util::EventDispatcher::event_ptr update;
	struct Draw {
		Util::EventDispatcher::event_ptr background;
		Util::EventDispatcher::event_ptr title;
		Util::EventDispatcher::event_ptr logo;
		struct Legend {
			Util::EventDispatcher::event_ptr background;
			Util::EventDispatcher::event_ptr title;
			Util::EventDispatcher::event_ptr label;
			Util::EventDispatcher::event_ptr marker;
			Util::EventDispatcher::event_ptr bar;
		} legend;
		struct Plot {
			Util::EventDispatcher::event_ptr background;
			struct Marker {
				Util::EventDispatcher::event_ptr base;
				Util::EventDispatcher::event_ptr label;
				Util::EventDispatcher::event_ptr guide;
			} marker;
			struct Axis {
				Util::EventDispatcher::event_ptr base;
				Util::EventDispatcher::event_ptr title;
				Util::EventDispatcher::event_ptr label;
				Util::EventDispatcher::event_ptr tick;
				Util::EventDispatcher::event_ptr guide;
				Util::EventDispatcher::event_ptr interlacing;
			} axis;
		} plot;
	} draw;
	struct Animation {
		Util::EventDispatcher::event_ptr begin;
		Util::EventDispatcher::event_ptr complete;
	} animation;

protected:
    class Chart& chart;
};

}

#endif
