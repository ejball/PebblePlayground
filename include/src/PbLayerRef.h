#ifndef PBCPP_H
#error Include PbCpp.h instead.
#endif

class PbLayerRef : public PbHandleRef<Layer *> {
public:
  PbLayerRef() {}

  PbLayerRef(Layer * handle)
    : PbHandleRef(handle) {}

  GRect bounds() {
    return layer_get_bounds(_handle);
  }

  PbLayerRef & bounds(GRect bounds) {
    layer_set_bounds(_handle, bounds);
    return *this;
  }

  GRect frame() {
    return layer_get_frame(_handle);
  }

  PbLayerRef & frame(GRect frame) {
    layer_set_frame(_handle, frame);
    return *this;
  }

  bool isHidden() {
    return layer_get_hidden(_handle);
  }

  PbLayerRef & isHidden(bool hidden) {
    layer_set_hidden(_handle, hidden);
    return *this;
  }

  PbLayerRef & addChild(PbLayerRef layer) {
    layer_add_child(_handle, layer._handle);
    return *this;
  }

  PbLayerRef & insertAboveSibling(PbLayerRef layer) {
    layer_insert_above_sibling(_handle, layer._handle);
    return *this;
  }

  PbLayerRef & insertBelowSibling(PbLayerRef layer) {
    layer_insert_below_sibling(_handle, layer._handle);
    return *this;
  }

  PbLayerRef & removeChildLayers() {
    layer_remove_child_layers(_handle);
    return *this;
  }

  PbLayerRef & removeFromParent() {
    layer_remove_from_parent(_handle);
    return *this;
  }
};
