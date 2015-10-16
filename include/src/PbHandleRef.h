#ifndef PBCPP_H
#error Include PbCpp.h instead.
#endif

template <typename T> class PbHandleRef {
public:
  PbHandleRef()
    : _handle(nullptr) {
  }

  explicit PbHandleRef(T handle)
    : _handle(handle) {
  }

  T handle() {
    return _handle;
  }

protected:
  T _handle;
};
