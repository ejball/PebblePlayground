class PebbleString {
public:
  PebbleString() {
    init();
  }
  explicit PebbleString(const char * text) {
    init();
    append(text);
  }
  PebbleString(const char * text, size_t length) {
    init();
    append(text, length);
  }
  PebbleString(PebbleString && text) {
    init();
    swap(text);
  }
  PebbleString & operator =(PebbleString && text) {
    if (this != &text) {
      destroy();
      init();
      swap(text);
    }
    return *this;
  }
  ~PebbleString() {
    destroy();
  }
  PebbleString & append(const PebbleString & text) {
    append(text.text_, text.length_);
    return *this;
  }
  PebbleString & append(const char * text) {
    append(text, strlen(text));
    return *this;
  }
  PebbleString & append(const char * text, size_t length) {
    if (length != 0) {
      reserve(length_ + length);
      strncpy(text_ + length_, text, length);
      length_ += static_cast<uint16_t>(length);
      text_[length_] = '\0';
    }
    return *this;
  }
  template <typename... Args> PebbleString & append_format(const char * format, Args... args) {
    int available = capacity_ - length_;
    int needed = snprintf(text_ + length_, capacity_ - length_, format, args...);
    if (needed > available) {
      reserve(length_ + needed + 1);
      needed = snprintf(text_ + length_, capacity_ - length_, format, args...);
    }
    length_ += needed;
    return *this;
  }
  PebbleString & append_time_format(size_t max, const char * format, const struct tm * tm) {
    reserve(length_ + max + 1);
    length_ += strftime(text_ + length_, max, format, tm);
    return *this;
  }
  PebbleString & assign(const PebbleString & text) {
    clear();
    append(text);
    return *this;
  }
  PebbleString & assign(const char * text) {
    clear();
    append(text);
    return *this;
  }
  PebbleString & assign(const char * text, size_t length) {
    clear();
    append(text, length);
    return *this;
  }
  template <typename... Args> PebbleString & assign_format(const char * format, Args... args) {
    clear();
    append_format(format, args...);
    return *this;
  }
  PebbleString & assign_time_format(size_t max, const char * format, const struct tm * tm) {
    clear();
    append_time_format(max, format, tm);
    return *this;
  }
  const char * c_str() const {
    return text_;
  }
  PebbleString & clear() {
    if (length_ != 0) {
      text_[0] = '\0';
      length_ = 0;
    }
    return *this;
  }
  PebbleString clone() {
    PebbleString text;
    text.append(*this);
    return text;
  }
  int compare(const PebbleString & text) {
    return strcmp(text_, text.text_);
  }
  int compare(const char * text) {
    return strcmp(text_, text);
  }
  int compare_n(const PebbleString & text, size_t length) {
    return strncmp(text_, text.text_, length);
  }
  int compare_n(const char * text, size_t length) {
    return strncmp(text_, text, length);
  }
  bool empty() const {
    return length_ == 0;
  }
  bool equals(const PebbleString & text) {
    return strcmp(text_, text.text_) == 0;
  }
  bool equals(const char * text) {
    return strcmp(text_, text) == 0;
  }
  bool equals_n(const PebbleString & text, size_t length) {
    return strncmp(text_, text.text_, length) == 0;
  }
  bool equals_n(const char * text, size_t length) {
    return strncmp(text_, text, length) == 0;
  }
  size_t length() const {
    return length_;
  }
  PebbleString & reserve(size_t capacity) {
    if (capacity > capacity_) {
      ASSERT(capacity <= max_length);
      if (capacity_ == 0) {
        text_ = reinterpret_cast<char *>(malloc(capacity + 1));
        ASSERT(text_ != nullptr);
        text_[0] = '\0';
      }
      else {
        text_ = reinterpret_cast<char *>(realloc(text_, capacity + 1));
        ASSERT(text_ != nullptr);
      }
      capacity_ = static_cast<uint16_t>(capacity);
    }
    return *this;
  }
  void swap(PebbleString & text) {
    std::swap(text_, text.text_);
    std::swap(length_, text.length_);
    std::swap(capacity_, text.capacity_);
  }
  static const size_t max_length = 65535;
private:
  PebbleString(char * text, uint16_t length, uint16_t capacity) {
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
