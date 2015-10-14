#ifndef PBCPP_H
#error Include PbCpp.h instead.
#endif

class PbDateTime {
public:
  PbDateTime(size_t c_time = 0)
    : _c_time(c_time) {}

  time_t c_time() const {
    return _c_time;
  }

  PbDateTimeInfo localInfo() const {
    return PbDateTimeInfo(*localtime(&_c_time));
  }

  static PbDateTime now() {
    return PbDateTime(time(nullptr));
  }

private:
  time_t _c_time;
};
