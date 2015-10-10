#include <PbCpp.hpp>

using namespace PbCpp;

int main() {
  PbWindow window;
  PbTextLayer textLayer;
  window.create().addChild(textLayer).show();
  app_event_loop();
  return 0;
}
