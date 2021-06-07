#ifndef BUBBLECHART_H
#define BUBBLECHART_H

#include "base/geom/circle.h"
#include "base/geom/point.h"

#include <vector>

namespace Vizzu
{
namespace Charts
{

enum class Boundary : uint32_t { Circular, Box, Diamond };

class BubbleChart
{
public:

	struct DataRecord {
		size_t index;
		Geom::Circle circle;
	};

	typedef std::vector<DataRecord> Data;

	const Data &getData() const { return data; }

protected:

	Data data;

	void normalize(const Geom::Rect &rect);

};

}
}

#endif
