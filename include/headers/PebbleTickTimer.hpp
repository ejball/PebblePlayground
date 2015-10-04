class PebbleTickTimer {
public:
  template <typename T> void subscribe(TimeUnits tick_units, T * handler) {
    if (handler != nullptr) {
      *(handler_ptr()) = handler;
      tick_timer_service_subscribe(tick_units, &native_handler<T>);
    }
  }
  void unsubscribe() {
    if (*(handler_ptr()) != nullptr) {
      tick_timer_service_unsubscribe();
      *(handler_ptr()) = nullptr;
    }
  }
  ~PebbleTickTimer() {
    unsubscribe();
  }
private:
  template <typename T> static void native_handler(struct tm * tick_time, TimeUnits units_changed) {
    reinterpret_cast<T *>(*(handler_ptr()))->on_tick(tick_time, units_changed);
  }
  static void ** handler_ptr() {
    static void * handler = nullptr;
    return &handler;
  }
};
