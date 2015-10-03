#include "pebble.hpp"

namespace {

class OurApp : public PebbleApp {
public:
  OurApp() {
    window_.create()
      .set_fullscreen(true)
      .set_window_handlers(this);
    push_window(window_, PebbleWindowAnimated);
  }
  void on_window_load(PebbleWindow * window) {
    text_layer_.create(window_.get_bounds())
      .set_text_alignment(GTextAlignmentCenter)
      .set_text(text_layer_text_.assign_format("(watch %d.%d)", 3, 14).c_str());
    window_.add_child(text_layer_);
  }
  void on_window_unload(PebbleWindow * window) {
    text_layer_.destroy();
  }
  void on_window_appear(PebbleWindow * window) {
  }
  void on_window_disappear(PebbleWindow * window) {
  }
private:
  PebbleWindow window_;
  PebbleTextLayer text_layer_;
  PebbleString text_layer_text_;
};

}

extern "C" int main(void) {
  OurApp app;
  app.event_loop();
}
