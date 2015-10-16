#ifndef PBCPP_H
#error Include PbCpp.h instead.
#endif

class PbDictionaryIteratorRef : public PbHandleRef<DictionaryIterator *> {
public:
  PbDictionaryIteratorRef() {}

  explicit PbDictionaryIteratorRef(DictionaryIterator * handle)
    : PbHandleRef(handle) {}

  uint32_t size() {
    return dict_size(_handle);
  }

  PbTupleRef readFirst() {
    return PbTupleRef(dict_read_first(_handle));
  }

  PbTupleRef readNext() {
    return PbTupleRef(dict_read_next(_handle));
  }
};
