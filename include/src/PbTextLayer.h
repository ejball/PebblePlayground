#ifndef PBCPP_H
#error Include PbCpp.h instead.
#endif

class PbTextLayer : public PbTextLayerRef, public PbNoncopyable {
public:
  PbTextLayer() {}

  PbTextLayer & create(PbRect frame) {
    destroy();
    _handle = text_layer_create(frame);
    return *this;
  }

  void destroy() {
    if (_handle) {
      text_layer_destroy(_handle);
      _handle = nullptr;
    }
  }

  ~PbTextLayer() {
    destroy();
  }
};
