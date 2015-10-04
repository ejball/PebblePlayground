#include "../include/pebble.hpp"

class OurApp : public PebbleApp {
public:
  OurApp() {
    tick_timer_.subscribe(SECOND_UNIT, this);
    window_.create()
      .set_fullscreen(true)
      .set_window_handlers_load_unload(this)
      .set_click_config_provider(this);
    push_window_animated(window_);
  }
  void on_window_load(PebbleWindow & window) {
    text_layer_.create(window_.get_bounds())
      .set_text_alignment(GTextAlignmentCenter);
    time_t now = time(nullptr);
    refresh_time(localtime(&now));
    window_.add_child(text_layer_);
  }
  void on_window_unload(PebbleWindow & window) {
    text_layer_.destroy();
  }
  void on_tick(struct tm * tick_time, TimeUnits units_changed) {
    refresh_time(tick_time);
  }
  void on_click_config(PebbleWindow & window, PebbleClickConfig<OurApp> config) {
    config.single_click_subscribe(BUTTON_ID_SELECT)
      .single_click_subscribe(BUTTON_ID_UP)
      .single_click_subscribe(BUTTON_ID_DOWN);
  }
  void on_single_click(PebbleWindow & window, ClickRecognizerRef ref) {
    ButtonId button_id = click_recognizer_get_button_id(ref);
    text_layer_.set_text(button_id == BUTTON_ID_UP ? "up" : button_id == BUTTON_ID_DOWN ? "down" : "click");
  }
private:
  void refresh_time(struct tm * tick_time) {
    text_layer_.set_text(text_layer_text_.assign_time_format(20, "%F %T", tick_time).c_str());
  }
  PebbleTickTimer tick_timer_;
  PebbleWindow window_;
  PebbleTextLayer text_layer_;
  PebbleString text_layer_text_;
};

extern "C" int main(void) {
  OurApp app;
  app.event_loop();
}
