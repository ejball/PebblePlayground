#ifndef PBCPP_H
#error Include PbCpp.h instead.
#endif

class PbClickRecognizerRef : public PbHandleRef<ClickRecognizerRef> {
public:
  PbClickRecognizerRef() {}

  explicit PbClickRecognizerRef(ClickRecognizerRef handle)
    : PbHandleRef(handle) {}
};
