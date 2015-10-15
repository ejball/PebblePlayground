#ifndef PBCPP_H
#error Include PbCpp.h instead.
#endif

class PbWindow : public PbWindowRef, public PbNoncopyable {
public:
  PbWindow() {}

  PbWindow & create() {
    destroy();
    _handle = window_create();
    window_set_fullscreen(_handle, true);
    return *this;
  }

  void destroy() {
    if (_handle) {
      window_destroy(_handle);
      _handle = nullptr;
    }
  }

  template <typename T> PbWindow & subscribe(T * handlers) {
    Subscriber<T> subscriber;
    if (handlers) {
      handlers->onWindowSubscribe(subscriber);
    }
    window_set_user_data(_handle, handlers);
    window_set_window_handlers(_handle, subscriber._windowHandlers);
    return *this;
  }

/*  template <typename T> PbWindow & _handleclicks(T * handlers) {
    click_handlers_ = handlers;
    window_set_click_config_provider(_handle, &click_config_provider<T>);
    return *this;
  }*/

  ~PbWindow() {
    destroy();
  }

  template <typename T> class Subscriber {
  public:
    Subscriber() {
      _windowHandlers.load = nullptr;
      _windowHandlers.unload = nullptr;
      _windowHandlers.appear = nullptr;
      _windowHandlers.disappear = nullptr;
    }

    Subscriber<T> & load() {
      _windowHandlers.load = &handleLoad;
      return *this;
    }

    Subscriber<T> & unload() {
      _windowHandlers.unload = &handleUnload;
      return *this;
    }

    Subscriber<T> & appear() {
      _windowHandlers.appear = &handleAppear;
      return *this;
    }

    Subscriber<T> & disappear() {
      _windowHandlers.disappear = &handleDisappaer;
      return *this;
    }

  private:
    static void handleLoad(Window * window) {
      reinterpret_cast<T *>(window_get_user_data(window))->onWindowLoad();
    }

    static void handleUnload(Window * window) {
      reinterpret_cast<T *>(window_get_user_data(window))->onWindowUnload();
    }

    static void handleAppear(Window * window) {
      reinterpret_cast<T *>(window_get_user_data(window))->onWindowAppear();
    }

    static void handleDisappaer(Window * window) {
      reinterpret_cast<T *>(window_get_user_data(window))->onWindowDisappear();
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

  //void * click_handlers_;
};
