#include "../../../include/PbCpp.cpp"

using namespace PbCpp;

class App : public PbApp<App> {
public:
  App() {
    // Create main Window element and assign to pointer
    _window.create();

    // Set handlers to manage the elements inside the Window
    _window.eventHandlers(this);

    // Show the Window on the watch, with animated=true
    _window.show();

    // Register with TickTimerService
    tickTimerHandler(MINUTE_UNIT, this);
  }

  void onEventConfig(PbWindow & window, PbWindow::EventConfig<App> & config) {
    config.load();
  }

  void onWindowLoad(PbWindow & window) {
    // Create time TextLayer
    _timeLayer.create(PbRect(0, 55, 144, 50))
      .backgroundColor(GColorClear)
      .textColor(GColorBlack)
      .text("00:00");

    // Improve the layout to be more like a watchface
    _timeLayer.font(fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD))
      .textAlignment(GTextAlignmentCenter);

    // Add it as a child layer to the Window's root layer
    _window.addChild(_timeLayer);

    // Make sure the time is displayed from the start
    updateTime();
  }

  void onTick(const PbDateTimeInfo & dateTimeInfo, TimeUnits unitsChanged) {
    updateTime();
  }

private:
  void updateTime() {
    // Get the current time
    PbDateTime now = PbDateTime::now();

    // Write the current hours and minutes into the buffer
    if (clock_is_24h_style()) {
      // Use 2h hour format
      _timeText.assignDateTimeFormat(sizeof("00:00"), "%H:%M", now.localInfo());
    } else {
      // Use 12 hour format
      _timeText.assignDateTimeFormat(sizeof("00:00"), "%I:%M", now.localInfo());
    }

    // Display this time on the TextLayer
    _timeLayer.text(_timeText.c_str());
  }

  PbWindow _window;
  PbTextLayer _timeLayer;
  PbString _timeText;
};

extern "C" int main() {
  return App::main();
}
