#ifndef PBCPP_H
#error Include PbCpp.h instead.
#endif

template <typename TDerived> class PbHasLayer {
public:
  template <typename THasLayer> TDerived & addChild(THasLayer & layer) {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_add_child(derived.layerHandle(), layer.layerHandle());
    return derived;
  }

  GRect bounds() {
    TDerived & derived = static_cast<TDerived &>(*this);
    return layer_get_bounds(derived.layerHandle());
  }

  GRect frame() {
    TDerived & derived = static_cast<TDerived &>(*this);
    return layer_get_frame(derived.layerHandle());
  }

  bool isHidden() {
    TDerived & derived = static_cast<TDerived &>(*this);
    return layer_get_hidden(derived.layerHandle());
  }

  template <typename THasLayer> TDerived & insertAboveSibling(THasLayer & layer) {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_insert_above_sibling(derived.layerHandle(), layer.layerHandle());
    return derived;
  }

  template <typename THasLayer> TDerived & insertBelowSibling(THasLayer & layer) {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_insert_below_sibling(derived.layerHandle(), layer.layerHandle());
    return derived;
  }

  TDerived & removeChildLayers() {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_remove_child_layers(derived.layerHandle());
    return derived;
  }

  TDerived & removeFromParent() {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_remove_from_parent(derived.layerHandle());
    return derived;
  }

  TDerived & bounds(GRect bounds) {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_set_bounds(derived.layerHandle(), bounds);
    return derived;
  }

  TDerived & frame(GRect frame) {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_set_frame(derived.layerHandle(), frame);
    return derived;
  }
  
  TDerived & isHidden(bool hidden) {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_set_hidden(derived.layerHandle(), hidden);
    return derived;
  }
};
