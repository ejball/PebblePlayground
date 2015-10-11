#ifndef PBCPP_H
#error Include PbCpp.hpp instead.
#endif

template <typename TDerived> class PbLayer {
public:
  template <typename TLayer> TDerived & addChild(TLayer & layer) {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_add_child(derived.layerHandle(), layer.layerHandle());
    return derived;
  }
  GRect get_bounds() {
    TDerived & derived = static_cast<TDerived &>(*this);
    return layer_get_bounds(derived.layerHandle());
  }
  GRect get_frame() {
    TDerived & derived = static_cast<TDerived &>(*this);
    return layer_get_frame(derived.layerHandle());
  }
  bool get_hidden() {
    TDerived & derived = static_cast<TDerived &>(*this);
    return layer_get_hidden(derived.layerHandle());
  }
  template <typename TLayer> TDerived & insert_above_sibling(TLayer & layer) {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_insert_above_sibling(derived.layerHandle(), layer.layerHandle());
    return derived;
  }
  template <typename TLayer> TDerived & insert_below_sibling(TLayer & layer) {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_insert_below_sibling(derived.layerHandle(), layer.layerHandle());
    return derived;
  }
  TDerived & remove_child_layers() {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_remove_child_layers(derived.layerHandle());
    return derived;
  }
  TDerived & remove_from_parent() {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_remove_from_parent(derived.layerHandle());
    return derived;
  }
  TDerived & set_bounds(GRect bounds) {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_set_bounds(derived.layerHandle(), bounds);
    return derived;
  }
  TDerived & set_frame(GRect frame) {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_set_frame(derived.layerHandle(), frame);
    return derived;
  }
  TDerived & set_hidden(bool hidden) {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_set_hidden(derived.layerHandle(), hidden);
    return derived;
  }
};
