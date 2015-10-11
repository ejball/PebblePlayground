#ifndef PBCPP_H
#error Include PbCpp.hpp instead.
#endif

class PbWindow : public PbLayer<PbWindow> {
public:
  PbWindow()
    : _handle(nullptr) {
  }
  PbWindow & create() {
    destroy();
    _handle = window_create();
    window_set_user_data(_handle, this);
    window_set_fullscreen(_handle, true);
    return *this;
  }
  void destroy() {
    if (_handle) {
      window_destroy(_handle);
      _handle = nullptr;
    }
  }
  PbWindow & show() {
    window_stack_push(_handle, true);
    return *this;
  }
  template <typename T> PbWindow & eventHandlers(T * handlers) {
    _eventHandlers = handlers;
    EventConfig<T> config;
    handlers->onEventConfig(*this, config);
    window_set_window_handlers(_handle, config._windowHandlers);
    PB_LOG_DEBUG("%p %p", config._windowHandlers.load, config._windowHandlers.unload);
    return *this;
  }
/*  template <typename T> PbWindow & _handleclicks(T * handlers) {
    click_handlers_ = handlers;
    window_set_click_config_provider(_handle, &click_config_provider<T>);
    return *this;
  }*/
  Window * handle() {
    return _handle;
  }
  Layer * layerHandle() {
    return window_get_root_layer(_handle);
  }
  ~PbWindow() {
    destroy();
  }
  static PbWindow & fromHandle(Window * handle) {
    return *reinterpret_cast<PbWindow *>(window_get_user_data(handle));
  }
  template <typename T> static PbWindow & fromLayer(T & layer) {
    return fromHandle(layer_get_window(layer.layerHandle()));
  }
  template <typename T> class EventConfig {
  public:
    EventConfig() {
      _windowHandlers.load = nullptr;
      _windowHandlers.unload = nullptr;
      _windowHandlers.appear = nullptr;
      _windowHandlers.disappear = nullptr;
    }
    EventConfig<T> & load() {
      _windowHandlers.load = &loadHandler;
      return *this;
    }
    EventConfig<T> & unload() {
      _windowHandlers.unload = &unloadHandler;
      return *this;
    }
    EventConfig<T> & appear() {
      _windowHandlers.appear = &appearHandler;
      return *this;
    }
    EventConfig<T> & disappear() {
      _windowHandlers.disappear = &disappearHandler;
      return *this;
    }
  private:
    static void loadHandler(Window * window) {
      PB_LOG_DEBUG("loadHandler");
      PbWindow & pw = fromHandle(window);
      reinterpret_cast<T *>(pw._eventHandlers)->onWindowLoad(pw);
    }
    static void unloadHandler(Window * window) {
      PbWindow & pw = fromHandle(window);
      reinterpret_cast<T *>(pw._eventHandlers)->onWindowUnload(pw);
    }
    static void appearHandler(Window * window) {
      PbWindow & pw = fromHandle(window);
      reinterpret_cast<T *>(pw._eventHandlers)->onWindowAppear(pw);
    }
    static void disappearHandler(Window * window) {
      PbWindow & pw = fromHandle(window);
      reinterpret_cast<T *>(pw._eventHandlers)->onWindowDisappear(pw);
    }
    friend PbWindow;
    WindowHandlers _windowHandlers;
  };
/*  template <typename T> class ClickConfig {
  public:
    ClickConfig() {
    }
    ClickConfig<T> & _handlesingle_click_up() {
      window_single_click_subscribe(BUTTON_ID_UP, &single_click_up_handler);
      return *this;
    }
    ClickConfig<T> & _handlesingle_click_down() {
      window_single_click_subscribe(BUTTON_ID_DOWN, &single_click_down_handler);
      return *this;
    }
    ClickConfig<T> & _handlesingle_click_select() {
      window_single_click_subscribe(BUTTON_ID_SELECT, &single_click_select_handler);
      return *this;
    }
    ClickConfig<T> & _handlesingle_click_back() {
      window_single_click_subscribe(BUTTON_ID_BACK, &single_click_back_handler);
      return *this;
    }
  private:
    static void single_click_up_handler(ClickRecognizerRef recognizer, void * context) {
      PbWindow & pw = PbWindow::fromHandle(static_cast<Window *>(context));
      reinterpret_cast<T *>(pw.click_handlers_)->on_single_click_up(pw, recognizer);
    }
    static void single_click_down_handler(ClickRecognizerRef recognizer, void * context) {
      PbWindow & pw = PbWindow::fromHandle(static_cast<Window *>(context));
      reinterpret_cast<T *>(pw.click_handlers_)->on_single_click_down(pw, recognizer);
    }
    static void single_click_select_handler(ClickRecognizerRef recognizer, void * context) {
      PbWindow & pw = PbWindow::fromHandle(static_cast<Window *>(context));
      reinterpret_cast<T *>(pw.click_handlers_)->on_single_click_select(pw, recognizer);
    }
    static void single_click_back_handler(ClickRecognizerRef recognizer, void * context) {
      PbWindow & pw = PbWindow::fromHandle(static_cast<Window *>(context));
      reinterpret_cast<T *>(pw.click_handlers_)->on_single_click_back(pw, recognizer);
    }
  };
private:
  template <typename T> static void click_config_provider(void * context) {
    PbWindow & pw = fromHandle(static_cast<Window *>(context));
    ClickConfig<T> config;
    reinterpret_cast<T *>(pw.click_handlers_)->on_click_config(pw, config);
  }*/
  Window * _handle;
  void * _eventHandlers;
  //void * click_handlers_;
};
