#ifndef PBCPP_H
#error Include PbCpp.h instead.
#endif

struct PbNoncopyable {
public:
  PbNoncopyable() = default;
  ~PbNoncopyable() = default;
  PbNoncopyable(const PbNoncopyable &) = delete;
  PbNoncopyable & operator=(const PbNoncopyable &) = delete;
};
