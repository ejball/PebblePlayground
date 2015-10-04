class PebbleApp {
public:
  template <typename TWindow> void push_window_animated(TWindow & window) {
    window_stack_push(window.get_handle(), true);
  }
  template <typename TWindow> void push_window_not_animated(TWindow & window) {
    window_stack_push(window.get_handle(), false);
  }
  void event_loop() {
    app_event_loop();
  }
};
