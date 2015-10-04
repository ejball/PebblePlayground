class PebbleTextLayer {
public:
  PebbleTextLayer() : handle_(nullptr) {}
  PebbleTextLayer & create(GRect frame) {
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
  PebbleTextLayer & set_text(const char * text) {
    text_layer_set_text(handle_, text);
    return *this;
  }
  PebbleTextLayer & set_text_alignment(GTextAlignment alignment) {
    text_layer_set_text_alignment(handle_, alignment);
    return *this;
  }
  TextLayer * get_handle() {
    return handle_;
  }
  Layer * get_layer_handle() {
    return text_layer_get_layer(handle_);
  }
  ~PebbleTextLayer() {
    destroy();
  }
private:
  TextLayer * handle_;
};
