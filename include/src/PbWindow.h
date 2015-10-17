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

  template <typename T> PbWindow & clickConfig(T * handlers) {
    window_set_click_config_provider_with_context(_handle, &provideClickConfig<T>, handlers);
    return *this;
  }

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

  template <typename T> class ClickConfig {
  public:
    ClickConfig() {}

    ClickConfig<T> & singleClickUp() {
      window_single_click_subscribe(BUTTON_ID_UP, &handleSingleClickUp);
      return *this;
    }

    ClickConfig<T> & singleClickDown() {
      window_single_click_subscribe(BUTTON_ID_DOWN, &handleSingleClickDown);
      return *this;
    }

    ClickConfig<T> & singleClickSelect() {
      window_single_click_subscribe(BUTTON_ID_SELECT, &handleSingleClickSelect);
      return *this;
    }

    ClickConfig<T> & singleClickBack() {
      window_single_click_subscribe(BUTTON_ID_BACK, &handleSingleClickBack);
      return *this;
    }

  private:
    static void handleSingleClickUp(ClickRecognizerRef recognizer, void * context) {
      reinterpret_cast<T *>(context)->onSingleClickUp(PbClickRecognizerRef(recognizer));
    }

    static void handleSingleClickDown(ClickRecognizerRef recognizer, void * context) {
      reinterpret_cast<T *>(context)->onSingleClickDown(PbClickRecognizerRef(recognizer));
    }

    static void handleSingleClickSelect(ClickRecognizerRef recognizer, void * context) {
      reinterpret_cast<T *>(context)->onSingleClickSelect(PbClickRecognizerRef(recognizer));
    }

    static void handleSingleClickBack(ClickRecognizerRef recognizer, void * context) {
      reinterpret_cast<T *>(context)->onSingleClickBack(PbClickRecognizerRef(recognizer));
    }
  };

private:
  template <typename T> static void provideClickConfig(void * context) {
    ClickConfig<T> config;
    reinterpret_cast<T *>(context)->onClickConfig(config);
  }
};
