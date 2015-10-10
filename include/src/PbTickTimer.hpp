#ifndef PBCPP_H
#error Include PbCpp.hpp instead.
#endif

class PbTickTimer {
public:
  template <typename T> void subscribe(TimeUnits tick_units, T * handler) {
    if (handler != nullptr) {
      void ** ptr = get_handler_ptr();
      PB_ASSERT(*ptr == nullptr);
      *ptr = handler;
      tick_timer_service_subscribe(tick_units, &native_handler<T>);
    }
  }
  void unsubscribe() {
    void ** ptr = get_handler_ptr();
    if (*ptr != nullptr) {
      tick_timer_service_unsubscribe();
      *ptr = nullptr;
    }
  }
  ~PbTickTimer() {
    unsubscribe();
  }
private:
  template <typename T> static void native_handler(struct tm * tick_time, TimeUnits units_changed) {
    reinterpret_cast<T *>(*get_handler_ptr())->on_tick(tick_time, units_changed);
  }
  static void ** get_handler_ptr() {
    static void * handler = nullptr;
    return &handler;
  }
};
