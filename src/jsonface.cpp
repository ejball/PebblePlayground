#include "pebble.hpp"

#if 0
extern "C" {

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Select");
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Up");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Down");
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

}
#endif

namespace {

#if 0  
class OurWindow : public PebbleWindowT<OurWindow> {
public:
  void on_load() {
    GRect bounds = get_bounds();
    text_layer_.create(bounds);
    text_layer_text_.reserve(100).assign_format("(watch %d.%d)", 3, 14);
    text_layer_.set_text(text_layer_text_.c_str());
    text_layer_.set_text_alignment(GTextAlignmentCenter);
    add_child(text_layer_);
  }
  void on_unload() {
    text_layer_.destroy();
  }
private:
  PebbleTextLayer text_layer_;
  PebbleString text_layer_text_;
};

class OurApp : public PebbleApp<OurApp> {
public:
  OurApp() {
    //window_set_click_config_provider(m_window.get_handle(), click_config_provider);
    m_window.create();
    push_window(m_window, PebbleWindowAnimated);
  }
private:
  PebbleWindow m_window;
};
#endif

}

extern "C" int main(void) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Initializing...");
  PebbleApp app;
  
  PebbleWindow window;
  window.create();
  GRect bounds = window.get_bounds();
  
  PebbleTextLayer text_layer;
  text_layer.create(bounds);
  text_layer.set_text_alignment(GTextAlignmentCenter);
  
  PebbleString text_layer_text;
  text_layer_text.assign_format("(watch %d.%d)", 3, 14);
  text_layer.set_text(text_layer_text.c_str());
  //text_layer.set_text("what?");
  
  window.add_child(text_layer);
  
  app.push_window(window, PebbleWindowAnimated);

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Starting...");
  app.event_loop();
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Finishing...");
}
