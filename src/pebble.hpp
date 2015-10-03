#pragma once

extern "C" {
#define _NEWLIB_ALLOCA_H
#include <pebble.h>
}

#include <algorithm>
#include <functional>

#if 0
#include <new>
#include <vector>

void * operator new(size_t size) {
  return malloc(size);
}

void operator delete(void * ptr) {
  free(ptr);
}
#endif

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
		//printf("available %d, needed %d", available, needed);
		if (needed > available) {
			reserve(length_ + needed + 1);
			needed = snprintf(text_ + length_, capacity_ - length_, format, args...);
			//printf("new needed %d", needed);
		}
		length_ += needed;
		return *this;
	}
	PebbleString & assign(const PebbleString & text) {
		assign(text.text_, text.length_);
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
			if (capacity_ == 0) {
				text_ = reinterpret_cast<char *>(malloc(capacity + 1));
				text_[0] = '\0';
			}
			else {
				text_ = reinterpret_cast<char *>(realloc(text_, capacity + 1));
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

enum PebbleWindowAnimation {
  PebbleWindowNotAnimated,
  PebbleWindowAnimated,
};

class PebbleApp {
public:
  template <typename TWindow> void push_window(TWindow & window, PebbleWindowAnimation animation) {
    window_stack_push(window.get_handle(), animation != PebbleWindowNotAnimated);
  }
  void event_loop() {
    app_event_loop();
  }
};

#if 0
template <typename TDerived> class PebbleApp {
public:
  template <typename TWindow> void push_window(TWindow & window, PebbleWindowAnimation animation) {
    window_stack_push(window.get_handle(), animation != PebbleWindowNotAnimated);
  }
  static void run() {
    TDerived app;
    app_event_loop();
  }
};
#endif

template <typename TDerived> class PebbleLayer {
public:
  GRect get_bounds() {
	return layer_get_bounds(static_cast<TDerived *>(this)->get_layer_handle());  
  }
  template <typename TLayer> TDerived & add_child(TLayer & layer) {
	TDerived & me = static_cast<TDerived &>(*this); 
	layer_add_child(me.get_layer_handle(), layer.get_layer_handle());
	return me;
  }
};

class PebbleWindow : public PebbleLayer<PebbleWindow> {
public:
  PebbleWindow()
  	: handle_(nullptr),
	  handlers_(nullptr) {
  }
  void create() {
    destroy();
    handle_ = window_create();
    window_set_user_data(handle_, this);
  }
  void destroy() {
    if (handle_) {
      window_destroy(handle_);
    }
  }
  template <typename T> void set_window_handlers(T * handlers) {
	handlers_ = handlers;
    WindowHandlers nativeHandlers;
    nativeHandlers.load = &load_handler<T>;
    nativeHandlers.unload = nullptr;
    nativeHandlers.appear = nullptr;
    nativeHandlers.disappear = nullptr;
    window_set_window_handlers(handle_, nativeHandlers);
  }
  Window * get_handle() {
    return handle_;
  }
  Layer * get_layer_handle() {
	return window_get_root_layer(handle_);
  }
  ~PebbleWindow() {
    destroy();
  }
  static PebbleWindow * from_handle(Window * handle) {
    return reinterpret_cast<PebbleWindow *>(window_get_user_data(handle));
  }
private:
  template <typename T> static void load_handler(Window * window) {
    PebbleWindow * pw = from_handle(window);
	reinterpret_cast<T *>(pw->handlers_)->on_window_load(pw);
  }
  Window * handle_;
  void * handlers_;
};

#if 0
template <typename TDerived> class PebbleWindowT : public PebbleWindow {
public:
  PebbleWindowT() {
    create();
    window_set_user_data(get_handle(), static_cast<TDerived *>(this));
    
    WindowHandlers handlers;
    handlers.load = &load_handler;
    handlers.unload = &unload_handler;
    handlers.appear = nullptr;
    handlers.disappear = nullptr;
    window_set_window_handlers(get_handle(), handlers);
  }
  static TDerived * from_handle(Window * handle) {
    return reinterpret_cast<TDerived *>(window_get_user_data(handle));
  }
  void on_load() {
  }
  void on_unload() {
  }
private:
  static void load_handler(Window * window) {
    from_handle(window)->on_load();
  }
  static void unload_handler(Window * window) {
    from_handle(window)->on_unload();
  }
};
#endif

class PebbleTextLayer {
public:
  PebbleTextLayer() : handle_(nullptr) {}
  void create(GRect frame) {
    destroy();
    handle_ = text_layer_create(frame);
  }
  void destroy() {
    if (handle_) {
      text_layer_destroy(handle_);
    }
  }
  void set_text(const char * text) {
    text_layer_set_text(handle_, text);
  }
  void set_text_alignment(GTextAlignment alignment) {
    text_layer_set_text_alignment(handle_, alignment);
  }
  TextLayer * get_handle() {
    return handle_;
  }
  Layer * get_layer_handle() {
	return text_layer_get_layer(handle_);
  }
  ~PebbleTextLayer() {
    destroy();
  }
private:
  TextLayer * handle_;
};
