#ifndef PBCPP_H
#error Include PbCpp.hpp instead.
#endif

class PbTextLayer : public PbLayer<PbTextLayer> {
public:
  PbTextLayer()
    : handle_(nullptr) {
  }
  PbTextLayer & create(GRect frame) {
    destroy();
    handle_ = text_layer_create(frame);
    return *this;
  }
  void destroy() {
    if (handle_) {
      text_layer_destroy(handle_);
      handle_ = nullptr;
    }
  }
  GSize get_content_size() {
    return text_layer_get_content_size(handle_);
  }
  const char * get_text() {
    return text_layer_get_text(handle_);
  }
  PbTextLayer & set_background_color(GColor color) {
    text_layer_set_background_color(handle_, color);
    return *this;
  }
  PbTextLayer & set_font(GFont font) {
    text_layer_set_font(handle_, font);
    return *this;
  }
  PbTextLayer & set_overflow_mode(GTextOverflowMode line_mode) {
    text_layer_set_overflow_mode(handle_, line_mode);
    return *this;
  }
  PbTextLayer & set_size(const GSize max_size) {
    text_layer_set_size(handle_, max_size);
    return *this;
  }
  PbTextLayer & text(const char * text) {
    text_layer_set_text(handle_, text);
    return *this;
  }
  PbTextLayer & set_text_alignment(GTextAlignment alignment) {
    text_layer_set_text_alignment(handle_, alignment);
    return *this;
  }
  PbTextLayer & set_text_color(GColor color) {
    text_layer_set_text_color(handle_, color);
    return *this;
  }
  TextLayer * get_handle() {
    return handle_;
  }
  Layer * get_layer_handle() {
    return text_layer_get_layer(handle_);
  }
  ~PbTextLayer() {
    destroy();
  }
private:
  TextLayer * handle_;
};
