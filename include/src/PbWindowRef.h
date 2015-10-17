#ifndef PBCPP_H
#error Include PbCpp.h instead.
#endif

class PbWindowRef : public PbHandleRef<Window *>, public PbHasLayer<PbWindowRef> {
public:
  PbWindowRef() {}

  explicit PbWindowRef(Window * handle)
    : PbHandleRef(handle) {}

  PbWindowRef & show() {
    window_stack_push(_handle, true);
    return *this;
  }

  PbLayerRef layer() {
    return PbLayerRef(window_get_root_layer(_handle));
  }

  PbWindowRef & backgroundColor(GColor color) {
    window_set_background_color(_handle, color);
    return *this;
  }
};
