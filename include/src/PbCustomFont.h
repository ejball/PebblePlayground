#ifndef PBCPP_H
#error Include PbCpp.h instead.
#endif

class PbCustomFont : public PbFont {
public:
  PbCustomFont() {}

  PbCustomFont & load(uint32_t resourceId) {
    destroy();
    attach(fonts_load_custom_font(resource_get_handle(resourceId)));
    return *this;
  }

  void destroy() {
    if (handle()) {
      fonts_unload_custom_font(handle());
    }
  }

  ~PbCustomFont() {
    destroy();
  }
};
