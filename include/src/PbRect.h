#ifndef PBCPP_H
#error Include PbCpp.h instead.
#endif

struct PbRect : GRect {
public:
  PbRect(int16_t x, int16_t y, int16_t w, int16_t h) {
    origin.x = x;
    origin.y = y;
    size.w = w;
    size.h = h;
  }
};
