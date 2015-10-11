#ifndef PBCPP_H
#error Include PbCpp.hpp instead.
#endif

class PbDateTimeInfo : public tm {
public:
  PbDateTimeInfo(const tm & tm) {
    memcpy(this, &tm, sizeof(tm));
  }
};
