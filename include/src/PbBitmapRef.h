#ifndef PBCPP_H
#error Include PbCpp.h instead.
#endif

class PbBitmapRef : public PbHandleRef<GBitmap *> {
public:
  PbBitmapRef() {}

  explicit PbBitmapRef(GBitmap * handle)
    : PbHandleRef(handle) {}
};
