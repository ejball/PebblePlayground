template <typename T> class PebbleClickConfig {
public:
  PebbleClickConfig<T> & single_click_subscribe(ButtonId button_id) {
    window_single_click_subscribe(button_id, &single_click_handler);
    return *this;
  }
private:
  static void single_click_handler(ClickRecognizerRef recognizer, void * context);
};

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
    window_set_fullscreen(handle_, true);
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
  template <typename T> PebbleWindow & set_click_config_provider(T * provider) {
    click_config_provider_ = provider;
    window_set_click_config_provider(handle_, &click_config_provider<T>);
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
  template <typename T> static void click_config_provider(void * context) {
    PebbleWindow & pw = from_handle(static_cast<Window *>(context));
    PebbleClickConfig<T> config;
    reinterpret_cast<T *>(pw.click_config_provider_)->on_click_config(pw, config);
  }
  template <typename T> friend class PebbleClickConfig;
  Window * handle_;
  void * handlers_;
  void * click_config_provider_;
};

template <typename T> void PebbleClickConfig<T>::single_click_handler(ClickRecognizerRef recognizer, void * context) {
  PebbleWindow & pw = PebbleWindow::from_handle(static_cast<Window *>(context));
  reinterpret_cast<T *>(pw.click_config_provider_)->on_single_click(pw, recognizer);
}
