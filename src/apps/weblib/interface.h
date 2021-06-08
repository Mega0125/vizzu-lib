#ifndef LIB_INTERFACE_H
#define LIB_INTERFACE_H

#include "chart/main/version.h"
#include "chart/ui/chart.h"

namespace Vizzu
{

class Interface
{
public:
	static Interface instance;

	Interface();
	const char *version() const;
	void init(double dpi, double width_mm, double height_mm);
	void setLogging(bool enable) { logging = enable; }
	void keyPress(int key, bool ctrl, bool alt, bool shift);
	void mouseMove(double x, double y);
	void mouseDown(double x, double y);
	void mouseUp(double x, double y);
	void update(double scale, double width, double height, bool force);
	void poll();

	void setStyleValue(const char *path, const char *value);
	void setChartValue(const char *path, const char *value);
	void addCategories(const char *name, const char **categories, int count);
	void addValues(const char *name, double *values, int count);
	void animate(void (*callback)());
	void animControl(const char *command, const char *param);

private:
	std::string versionStr;
	std::shared_ptr<GUI::TaskQueue> taskQueue;
	std::shared_ptr<UI::ChartWidget> chart;
	bool needsUpdate;
	bool logging;
	void log(const char* str);
};

}

#endif