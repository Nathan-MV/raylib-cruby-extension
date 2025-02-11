#ifndef TEXT_H
#define TEXT_H

#include "ruby_values.h"
#include "raylib_values.h"

extern "C" void Init_Font();

inline Font* get_font(VALUE obj) {
  Font *font;
  Data_Get_Struct(obj, Font, font);

  return font;
}

template <typename T>
void rb_font_free(void *ptr) {
  T *obj = static_cast<T *>(ptr);
  UnloadFont(*obj);
  delete obj;
}

template <typename T>
VALUE rb_font_alloc(VALUE klass) {
  try {
    T *obj = new T();
    return Data_Wrap_Struct(klass, nullptr, rb_font_free<T>, obj);
  } catch (const std::bad_alloc& e) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for %s.", typeid(T).name());
    return Qnil;
  }
}

#endif // TEXT_H
