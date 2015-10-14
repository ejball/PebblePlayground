#ifndef PBCPP_H
#error Include PbCpp.h instead.
#endif

class PbSystemFont : public PbFont {
public:
  PbSystemFont() {}

  PbSystemFont & load(const char * fontKey) {
    attach(fonts_get_system_font(fontKey));
    return *this;
  }
};
