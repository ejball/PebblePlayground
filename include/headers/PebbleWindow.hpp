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
  template <typename T> PebbleWindow & handle_events(T * handlers) {
    event_handlers_ = handlers;
    EventConfig<T> config;
    handlers->on_event_config(*this, config);
    window_set_window_handlers(handle_, config.window_handlers_);
    return *this;
  }
  template <typename T> PebbleWindow & handle_clicks(T * handlers) {
    click_handlers_ = handlers;
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
  template <typename T> class EventConfig {
  public:
    EventConfig() {
      window_handlers_.load = nullptr;
      window_handlers_.unload = nullptr;
      window_handlers_.appear = nullptr;
      window_handlers_.disappear = nullptr;
    }
    EventConfig<T> & handle_load() {
      window_handlers_.load = &load_handler;
      return *this;
    }
    EventConfig<T> & handle_unload() {
      window_handlers_.unload = &unload_handler;
      return *this;
    }
    EventConfig<T> & handle_appear() {
      window_handlers_.appear = &appear_handler;
      return *this;
    }
    EventConfig<T> & handle_disappear() {
      window_handlers_.disappear = &disappear_handler;
      return *this;
    }
  private:
    static void load_handler(Window * window) {
      PebbleWindow & pw = from_handle(window);
      reinterpret_cast<T *>(pw.event_handlers_)->on_window_load(pw);
    }
    static void unload_handler(Window * window) {
      PebbleWindow & pw = from_handle(window);
      reinterpret_cast<T *>(pw.event_handlers_)->on_window_unload(pw);
    }
    static void appear_handler(Window * window) {
      PebbleWindow & pw = from_handle(window);
      reinterpret_cast<T *>(pw.event_handlers_)->on_window_appear(pw);
    }
    static void disappear_handler(Window * window) {
      PebbleWindow & pw = from_handle(window);
      reinterpret_cast<T *>(pw.event_handlers_)->on_window_disappear(pw);
    }
    friend PebbleWindow;
    WindowHandlers window_handlers_;
  };
  template <typename T> class ClickConfig {
  public:
    ClickConfig() {
    }
    ClickConfig<T> & handle_single_click_up() {
      window_single_click_subscribe(BUTTON_ID_UP, &single_click_up_handler);
      return *this;
    }
    ClickConfig<T> & handle_single_click_down() {
      window_single_click_subscribe(BUTTON_ID_DOWN, &single_click_down_handler);
      return *this;
    }
    ClickConfig<T> & handle_single_click_select() {
      window_single_click_subscribe(BUTTON_ID_SELECT, &single_click_select_handler);
      return *this;
    }
    ClickConfig<T> & handle_single_click_back() {
      window_single_click_subscribe(BUTTON_ID_BACK, &single_click_back_handler);
      return *this;
    }
  private:
    static void single_click_up_handler(ClickRecognizerRef recognizer, void * context) {
      PebbleWindow & pw = PebbleWindow::from_handle(static_cast<Window *>(context));
      reinterpret_cast<T *>(pw.click_handlers_)->on_single_click_up(pw, recognizer);
    }
    static void single_click_down_handler(ClickRecognizerRef recognizer, void * context) {
      PebbleWindow & pw = PebbleWindow::from_handle(static_cast<Window *>(context));
      reinterpret_cast<T *>(pw.click_handlers_)->on_single_click_down(pw, recognizer);
    }
    static void single_click_select_handler(ClickRecognizerRef recognizer, void * context) {
      PebbleWindow & pw = PebbleWindow::from_handle(static_cast<Window *>(context));
      reinterpret_cast<T *>(pw.click_handlers_)->on_single_click_select(pw, recognizer);
    }
    static void single_click_back_handler(ClickRecognizerRef recognizer, void * context) {
      PebbleWindow & pw = PebbleWindow::from_handle(static_cast<Window *>(context));
      reinterpret_cast<T *>(pw.click_handlers_)->on_single_click_back(pw, recognizer);
    }
  };
private:
  template <typename T> static void click_config_provider(void * context) {
    PebbleWindow & pw = from_handle(static_cast<Window *>(context));
    ClickConfig<T> config;
    reinterpret_cast<T *>(pw.click_handlers_)->on_click_config(pw, config);
  }
  Window * handle_;
  void * handlers_;
  void * event_handlers_;
  void * click_handlers_;
};
