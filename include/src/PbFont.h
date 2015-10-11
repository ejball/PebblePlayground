#ifndef PBCPP_H
#error Include PbCpp.hpp instead.
#endif

class PbFont {
public:
  GFont handle() {
    return _handle;
  }
protected:
  PbFont()
    : _handle(nullptr) {
  }
  void attach(GFont handle) {
    _handle = handle;
  }
private:
  GFont _handle;
};
