#ifndef PBCPP_H
#error Include PbCpp.h instead.
#endif

class PbBitmapRef : public PbHandleRef<GBitmap *> {
public:
  PbBitmapRef() {}

  PbBitmapRef(GBitmap * handle)
    : PbHandleRef(handle) {}
};
