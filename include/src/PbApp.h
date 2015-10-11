#ifndef PBCPP_H
#error Include PbCpp.hpp instead.
#endif

template <typename TDerived> class PbApp {
public:
  static int main() {
    _appPtr = new TDerived();
    app_event_loop();
    delete _appPtr;
    return 0;
  }
  static TDerived & app() {
    return *_appPtr;
  }
  template <typename T> void tickTimerHandler(TimeUnits tick_units, T * handler) {
    _tickTimerHandler = handler;
    if (handler != nullptr) {
      tick_timer_service_subscribe(tick_units, &tickTimerHandler<T>);
    } else {
      tick_timer_service_unsubscribe();
    }
  }
  void tickTimerHandler(std::nullptr_t handler) {
    _tickTimerHandler = nullptr;
    tick_timer_service_unsubscribe();
  }
private:
  template <typename T> static void tickTimerHandler(struct tm * tick_time, TimeUnits units_changed) {
    reinterpret_cast<T *>(app()._tickTimerHandler)->onTick(*reinterpret_cast<const PbDateTimeInfo *>(tick_time), units_changed);
  }
  static TDerived * _appPtr;
  void * _tickTimerHandler;
};

template <typename TDerived> TDerived * PbApp<TDerived>::_appPtr;
