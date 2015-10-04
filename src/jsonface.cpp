#include "../include/pebble.hpp"

class OurApp : public PebbleApp {
public:
  OurApp() {
    tick_timer_.subscribe(SECOND_UNIT, this);
    window_.create()
      .set_window_handlers_load_unload(this)
      .handle_clicks(this);
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
    config.handle_single_click_select()
      .handle_single_click_up()
      .handle_single_click_down()
      .handle_single_click_back();
  }
  void on_single_click_select(PebbleWindow & window, ClickRecognizerRef ref) {
    text_layer_.set_text("select");
  }
  void on_single_click_up(PebbleWindow & window, ClickRecognizerRef ref) {
    text_layer_.set_text("up");
  }
  void on_single_click_down(PebbleWindow & window, ClickRecognizerRef ref) {
    text_layer_.set_text("down");
  }
  void on_single_click_back(PebbleWindow & window, ClickRecognizerRef ref) {
    text_layer_.set_text("back");
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
