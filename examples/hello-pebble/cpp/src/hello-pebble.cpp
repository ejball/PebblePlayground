#include <PbCpp.hpp>

using namespace PbCpp;

int main() {
  PbWindow window;
  PbTextLayer textLayer;
  textLayer.create(PbRect(0, 0, 144, 40)).text("Hello, Pebble!");
  window.create().addChild(textLayer).show();
  app_event_loop();
  return 0;
}
