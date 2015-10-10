#include "../include/PbCpp.hpp"
#include "../include/PbCpp.cpp"

using namespace PbCpp;

class OurApp : public PbApp<OurApp> {
public:
  OurApp() {
    PB_LOG_DEBUG("App starting.");
    tick_timer_.subscribe(MINUTE_UNIT, this);
    window_.create()
      .handle_events(this)
      .handle_clicks(this);
    push_window_animated(window_);
  }
  ~OurApp() {
    PB_LOG_DEBUG("App finishing.");
  }
  void on_window_load(PbWindow & window) {
    text_layer_.create(window_.get_bounds())
      .set_font(fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD))
      .set_text_alignment(GTextAlignmentLeft);
    time_t now = time(nullptr);
    refresh_time(localtime(&now));
    window_.add_child(text_layer_);
  }
  void on_window_unload(PbWindow & window) {
    text_layer_.destroy();
  }
  void on_tick(struct tm * tick_time, TimeUnits units_changed) {
    refresh_time(tick_time);
  }
  void on_event_config(PbWindow & window, PbWindow::EventConfig<OurApp> & config) {
    config.handle_load().handle_unload();
  }
  void on_click_config(PbWindow & window, PbWindow::ClickConfig<OurApp> & config) {
    config.handle_single_click_select()
      .handle_single_click_up()
      .handle_single_click_down()
      .handle_single_click_back();
  }
  void on_single_click_select(PbWindow & window, ClickRecognizerRef ref) {
    text_layer_.set_text("select");
  }
  void on_single_click_up(PbWindow & window, ClickRecognizerRef ref) {
    text_layer_.set_text("up");
  }
  void on_single_click_down(PbWindow & window, ClickRecognizerRef ref) {
    text_layer_.set_text("down");
  }
  void on_single_click_back(PbWindow & window, ClickRecognizerRef ref) {
    text_layer_.set_text("back");
  }
private:
  void refresh_time(struct tm * time) {
    if (clock_is_24h_style()) {
      text_layer_text_.assign_format( "{\n  \"time\": \"%02d:%02d\"\n}", time->tm_hour, time->tm_min);
    } else {
      text_layer_text_.assign_format( "{\n  \"time\": \"%d:%02d %s\"\n}",
        time->tm_hour > 12 ? time->tm_hour - 12 : time->tm_hour == 0 ? 12 : time->tm_hour,
        time->tm_min, time->tm_hour >= 12 ? "pm" : "am");
    }
    text_layer_.set_text(text_layer_text_.c_str());
  }
  PbTickTimer tick_timer_;
  PbWindow window_;
  PbTextLayer text_layer_;
  PbString text_layer_text_;
};

extern "C" int main() {
  return OurApp::main();
}
