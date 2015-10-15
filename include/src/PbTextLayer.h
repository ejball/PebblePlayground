#ifndef PBCPP_H
#error Include PbCpp.h instead.
#endif

class PbTextLayer : public PbHasLayer<PbTextLayer> {
public:
  PbTextLayer()
    : _handle(nullptr) {
  }

  PbTextLayer & create(GRect frame) {
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

  GSize contentSize() {
    return text_layer_get_content_size(_handle);
  }

  PbTextLayer & backgroundColor(GColor color) {
    text_layer_set_background_color(_handle, color);
    return *this;
  }

  PbTextLayer & font(PbFontRef font) {
    text_layer_set_font(_handle, font.handle());
    return *this;
  }

  PbTextLayer & overflowMode(GTextOverflowMode line_mode) {
    text_layer_set_overflow_mode(_handle, line_mode);
    return *this;
  }

  PbTextLayer & size(const GSize max_size) {
    text_layer_set_size(_handle, max_size);
    return *this;
  }

  PbTextLayer & text(const char * text) {
    text_layer_set_text(_handle, text);
    return *this;
  }

  PbTextLayer & textAlignment(GTextAlignment alignment) {
    text_layer_set_text_alignment(_handle, alignment);
    return *this;
  }

  PbTextLayer & textColor(GColor color) {
    text_layer_set_text_color(_handle, color);
    return *this;
  }

  TextLayer * handle() {
    return _handle;
  }

  PbLayerRef layer() {
    return PbLayerRef(text_layer_get_layer(_handle));
  }

  ~PbTextLayer() {
    destroy();
  }

private:
  TextLayer * _handle;
};
