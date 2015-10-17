#ifndef PBCPP_H
#error Include PbCpp.h instead.
#endif

struct PbRect : GRect {
public:
  PbRect() {
    memset(this, 0, sizeof(PbRect));
  }

  explicit PbRect(GRect rect) {
    memcpy(this, &rect, sizeof(GRect));
  }

  PbRect(int16_t x, int16_t y, int16_t w, int16_t h) {
    origin.x = x;
    origin.y = y;
    size.w = w;
    size.h = h;
  }

  int16_t left() const {
    return origin.x;
  }

  int16_t top() const {
    return origin.y;
  }

  int16_t width() const {
    return size.w;
  }

  int16_t height() const {
    return size.h;
  }
};
