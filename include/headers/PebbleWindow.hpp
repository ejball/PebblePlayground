class PebbleWindow : public PebbleLayer<PebbleWindow> {
public:
  PebbleWindow()
    : handle_(nullptr),
    handlers_(nullptr) {
  }
  PebbleWindow & create() {
    destroy();
    handle_ = window_create();
    window_set_user_data(handle_, this);
    return *this;
  }
  void destroy() {
    if (handle_) {
      window_destroy(handle_);
      handle_ = nullptr;
    }
  }
  template <typename T> PebbleWindow & set_window_handlers_load_unload(T * handlers) {
    set_window_handlers(handlers, &load_handler<T>, &unload_handler<T>, nullptr, nullptr);
    return *this;
  }
  template <typename T> PebbleWindow & set_window_handlers_appear_disappear(T * handlers) {
    set_window_handlers(handlers, nullptr, nullptr, &appear_handler<T>, &disappear_handler<T>);
    return *this;
  }
  template <typename T> PebbleWindow & set_window_handlers(T * handlers) {
    set_window_handlers(handlers, &load_handler<T>, &unload_handler<T>, &appear_handler<T>, &disappear_handler<T>);
    return *this;
  }
  PebbleWindow & set_fullscreen(bool enabled) {
    window_set_fullscreen(handle_, enabled);
    return *this;
  }
  Window * get_handle() {
    return handle_;
  }
  Layer * get_layer_handle() {
    return window_get_root_layer(handle_);
  }
  ~PebbleWindow() {
    destroy();
  }
  static PebbleWindow & from_handle(Window * handle) {
    return *reinterpret_cast<PebbleWindow *>(window_get_user_data(handle));
  }
private:
  template <typename T> void set_window_handlers(T * handlers,
    WindowHandler load, WindowHandler unload, WindowHandler appear, WindowHandler disappear) {
    handlers_ = handlers;
    WindowHandlers nativeHandlers;
    nativeHandlers.load = load;
    nativeHandlers.unload = unload;
    nativeHandlers.appear = appear;
    nativeHandlers.disappear = disappear;
    window_set_window_handlers(handle_, nativeHandlers);
  }
  template <typename T> static void load_handler(Window * window) {
    PebbleWindow & pw = from_handle(window);
    reinterpret_cast<T *>(pw.handlers_)->on_window_load(pw);
  }
  template <typename T> static void unload_handler(Window * window) {
    PebbleWindow & pw = from_handle(window);
    reinterpret_cast<T *>(pw.handlers_)->on_window_unload(pw);
  }
  template <typename T> static void appear_handler(Window * window) {
    PebbleWindow & pw = from_handle(window);
    reinterpret_cast<T *>(pw.handlers_)->on_window_appear(pw);
  }
  template <typename T> static void disappear_handler(Window * window) {
    PebbleWindow & pw = from_handle(window);
    reinterpret_cast<T *>(pw.handlers_)->on_window_disappear(pw);
  }
  Window * handle_;
  void * handlers_;
};
