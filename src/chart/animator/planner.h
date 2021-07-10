#ifndef CHART_ANIM_PLANNER
#define CHART_ANIM_PLANNER

#include <functional>
#include <memory>
#include <vector>

#include "base/anim/control.h"
#include "base/anim/group.h"
#include "chart/generator/diagram.h"

#include "options.h"

namespace Vizzu
{
namespace Anim
{

class Planner : public ::Anim::Group
{
public:
	Planner() = default;

protected:

	void createPlan(const Diag::Diagram &source,
	    const Diag::Diagram &target,
	    Diag::Diagram &actual,
	    const Options &options);

private:
	const Diag::Diagram *source;
	const Diag::Diagram *target;
	Diag::Diagram *actual;
	const Options *options;

	void addMorph(SectionId sectionId, const ::Anim::Options &autoOptions);
	bool anyMarker(const std::function<bool(const Diag::Marker &,
	        const Diag::Marker &)> &compare) const;

	bool positionMorphNeeded() const;
	bool verticalBeforeHorizontal() const;
	size_t discreteCount(const Diag::Diagram *diagram,
	    Diag::Scale::Type type) const;

	bool needColor() const;
	bool needHorizontal() const;
	bool needVertical() const;
};
}
}

#endif
