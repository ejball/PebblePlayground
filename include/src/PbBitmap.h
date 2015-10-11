#ifndef PBCPP_H
#error Include PbCpp.hpp instead.
#endif

class PbBitmap {
public:
  PbBitmap()
    : _handle(nullptr) {
  }
  PbBitmap & createWithResource(uint32_t resourceId) {
    destroy();
    _handle = gbitmap_create_with_resource(resourceId);
    PB_ASSERT(_handle != nullptr);
    return *this;
  }
  void destroy() {
    if (_handle) {
      gbitmap_destroy(_handle);
      _handle = nullptr;
    }
  }
  GBitmap * handle() {
    return _handle;
  }
  ~PbBitmap() {
    destroy();
  }
private:
  GBitmap * _handle;
};
