#ifndef PBCPP_H
#error Include PbCpp.hpp instead.
#endif

class PbFont {
public:
  PbFont()
    : _handle(nullptr),
    _custom(false) {
  }
  PbFont & loadSystemFont(const char * fontKey) {
    destroy();
    _handle = fonts_get_system_font(fontKey);
    return *this;
  }
  PbFont & loadCustomFont(uint32_t resourceId) {
    destroy();
    _handle = fonts_load_custom_font(resource_get_handle(resourceId));
    _custom = true;
    return *this;
  }
  void destroy() {
    if (_handle) {
      if (_custom) {
        fonts_unload_custom_font(_handle);
      }
      _handle = nullptr;
    }
  }
  GFont handle() {
    return _handle;
  }
  ~PbFont() {
    destroy();
  }
private:
  GFont _handle;
  bool _custom;
};
