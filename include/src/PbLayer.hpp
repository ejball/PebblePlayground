#ifndef PBCPP_H
#error Include PbCpp.hpp instead.
#endif

template <typename TDerived> class PbLayer {
public:
  template <typename TLayer> TDerived & add_child(TLayer & layer) {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_add_child(derived.get_layer_handle(), layer.get_layer_handle());
    return derived;
  }
  GRect get_bounds() {
    TDerived & derived = static_cast<TDerived &>(*this);
    return layer_get_bounds(derived.get_layer_handle());
  }
  GRect get_frame() {
    TDerived & derived = static_cast<TDerived &>(*this);
    return layer_get_frame(derived.get_layer_handle());
  }
  bool get_hidden() {
    TDerived & derived = static_cast<TDerived &>(*this);
    return layer_get_hidden(derived.get_layer_handle());
  }
  template <typename TLayer> TDerived & insert_above_sibling(TLayer & layer) {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_insert_above_sibling(derived.get_layer_handle(), layer.get_layer_handle());
    return derived;
  }
  template <typename TLayer> TDerived & insert_below_sibling(TLayer & layer) {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_insert_below_sibling(derived.get_layer_handle(), layer.get_layer_handle());
    return derived;
  }
  TDerived & remove_child_layers() {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_remove_child_layers(derived.get_layer_handle());
    return derived;
  }
  TDerived & remove_from_parent() {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_remove_from_parent(derived.get_layer_handle());
    return derived;
  }
  TDerived & set_bounds(GRect bounds) {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_set_bounds(derived.get_layer_handle(), bounds);
    return derived;
  }
  TDerived & set_frame(GRect frame) {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_set_frame(derived.get_layer_handle(), frame);
    return derived;
  }
  TDerived & set_hidden(bool hidden) {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_set_hidden(derived.get_layer_handle(), hidden);
    return derived;
  }
};
