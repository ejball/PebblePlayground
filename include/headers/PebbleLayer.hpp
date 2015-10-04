template <typename TDerived> class PebbleLayer {
public:
  GRect get_bounds() {
    return layer_get_bounds(static_cast<TDerived *>(this)->get_layer_handle());
  }
  template <typename TLayer> TDerived & add_child(TLayer & layer) {
    TDerived & derived = static_cast<TDerived &>(*this);
    layer_add_child(derived.get_layer_handle(), layer.get_layer_handle());
    return derived;
  }
};
