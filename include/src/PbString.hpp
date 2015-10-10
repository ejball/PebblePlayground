#ifndef PBCPP_H
#error Include PbCpp.hpp instead.
#endif

class PbString {
public:
  PbString() {
    init();
  }
  explicit PbString(const char * text) {
    init();
    append(text);
  }
  PbString(const char * text, size_t length) {
    init();
    append(text, length);
  }
  PbString(PbString && text) {
    init();
    swap(text);
  }
  PbString & operator =(PbString && text) {
    if (this != &text) {
      destroy();
      init();
      swap(text);
    }
    return *this;
  }
  ~PbString() {
    destroy();
  }
  PbString & append(const PbString & text) {
    append(text.text_, text.length_);
    return *this;
  }
  PbString & append(const char * text) {
    append(text, strlen(text));
    return *this;
  }
  PbString & append(const char * text, size_t length) {
    if (length != 0) {
      reserve(length_ + length);
      strncpy(text_ + length_, text, length);
      length_ += static_cast<uint16_t>(length);
      text_[length_] = '\0';
    }
    return *this;
  }
  template <typename... Args> PbString & append_format(const char * format, Args... args) {
    int available = capacity_ - length_;
    int needed = snprintf(text_ + length_, capacity_ - length_, format, args...);
    if (needed > available) {
      reserve(length_ + needed + 1);
      needed = snprintf(text_ + length_, capacity_ - length_, format, args...);
    }
    length_ += needed;
    return *this;
  }
  PbString & append_time_format(size_t max, const char * format, const struct tm * tm) {
    reserve(length_ + max + 1);
    length_ += strftime(text_ + length_, max, format, tm);
    return *this;
  }
  PbString & assign(const PbString & text) {
    clear();
    append(text);
    return *this;
  }
  PbString & assign(const char * text) {
    clear();
    append(text);
    return *this;
  }
  PbString & assign(const char * text, size_t length) {
    clear();
    append(text, length);
    return *this;
  }
  template <typename... Args> PbString & assign_format(const char * format, Args... args) {
    clear();
    append_format(format, args...);
    return *this;
  }
  PbString & assign_time_format(size_t max, const char * format, const struct tm * tm) {
    clear();
    append_time_format(max, format, tm);
    return *this;
  }
  const char * c_str() const {
    return text_;
  }
  PbString & clear() {
    if (length_ != 0) {
      text_[0] = '\0';
      length_ = 0;
    }
    return *this;
  }
  PbString clone() {
    PbString text;
    text.append(*this);
    return text;
  }
  int compare(const PbString & text) {
    return strcmp(text_, text.text_);
  }
  int compare(const char * text) {
    return strcmp(text_, text);
  }
  int compare_n(const PbString & text, size_t length) {
    return strncmp(text_, text.text_, length);
  }
  int compare_n(const char * text, size_t length) {
    return strncmp(text_, text, length);
  }
  bool empty() const {
    return length_ == 0;
  }
  bool equals(const PbString & text) {
    return strcmp(text_, text.text_) == 0;
  }
  bool equals(const char * text) {
    return strcmp(text_, text) == 0;
  }
  bool equals_n(const PbString & text, size_t length) {
    return strncmp(text_, text.text_, length) == 0;
  }
  bool equals_n(const char * text, size_t length) {
    return strncmp(text_, text, length) == 0;
  }
  size_t length() const {
    return length_;
  }
  PbString & reserve(size_t capacity) {
    if (capacity > capacity_) {
      PB_ASSERT(capacity <= max_length);
      if (capacity_ == 0) {
        text_ = reinterpret_cast<char *>(malloc(capacity + 1));
        PB_ASSERT(text_ != nullptr);
        text_[0] = '\0';
      }
      else {
        text_ = reinterpret_cast<char *>(realloc(text_, capacity + 1));
        PB_ASSERT(text_ != nullptr);
      }
      capacity_ = static_cast<uint16_t>(capacity);
    }
    return *this;
  }
  void swap(PbString & text) {
    std::swap(text_, text.text_);
    std::swap(length_, text.length_);
    std::swap(capacity_, text.capacity_);
  }
  static const size_t max_length = 65535;
private:
  PbString(char * text, uint16_t length, uint16_t capacity) {
    init(text, length, capacity);
  }
  void init() {
    text_ = const_cast<char *>("");
    length_ = 0;
    capacity_ = 0;
  }
  void init(char * text, uint16_t length, uint16_t capacity) {
    text_ = text;
    length_ = length;
    capacity_ = capacity;
  }
  void destroy() {
    if (capacity_ != 0) {
      free(text_);
    }
  }
  char * text_;
  uint16_t length_;
  uint16_t capacity_;
};
