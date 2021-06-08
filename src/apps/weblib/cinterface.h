#ifndef LIB_CINTERFACE_H
#define LIB_CINTERFACE_H

extern "C" {

extern void vizzu_init(double dpi, double width_mm, double height_mm);
extern void vizzu_poll();
extern void vizzu_mouseDown(double x, double y);
extern void vizzu_mouseUp(double x, double y);
extern void vizzu_mouseMove(double x, double y);
extern void vizzu_keyPress(int key, bool ctrl, bool alt, bool shift);
extern void vizzu_setLogging(bool enable);
extern void vizzu_update(double scale, double width, double height, bool force);
extern const char *vizzu_errorMessage(int exceptionPtr);
extern const char *vizzu_version();

extern void data_addCategories(const char *name, const char **categories, int count);
extern void data_addValues(const char *name, double *values, int count);
extern void style_setValue(const char *path, const char *value);
extern void chart_setValue(const char *path, const char *value);
extern void chart_animate(void (*callback)());
extern void anim_control(const char *command, const char *param);

}

#endif