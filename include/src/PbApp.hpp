#ifndef PBCPP_H
#error Include PbCpp.hpp instead.
#endif

template <typename TDerived> class PbApp {
public:
  void push_window_animated(PbWindow & window) {
    window_stack_push(window.get_handle(), true);
  }
  void push_window_not_animated(PbWindow & window) {
    window_stack_push(window.get_handle(), false);
  }
  static TDerived & get_app() {
    return *app_ptr_;
  }
  static int main() {
    app_ptr_ = new TDerived();
    app_event_loop();
    delete app_ptr_;
    return 0;
  }
private:
  static TDerived * app_ptr_;
};

template <typename TDerived> TDerived * PbApp<TDerived>::app_ptr_;
