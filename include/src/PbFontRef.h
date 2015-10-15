#ifndef PBCPP_H
#error Include PbCpp.h instead.
#endif

class PbFontRef : public PbHandleRef<GFont> {
public:
  PbFontRef() {}

  PbFontRef(GFont handle)
    : PbHandleRef(handle) {}

  static PbFontRef fromSystem(const char * fontKey) {
    return PbFontRef(fonts_get_system_font(fontKey));
  }
};
