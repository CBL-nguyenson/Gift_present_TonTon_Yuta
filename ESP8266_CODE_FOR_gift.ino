// #define time_delay(t) for (static uint32_t _lasttime; \
//                            (uint32_t)((uint32_t)millis() - _lasttime) >= (t); \
//                            _lasttime += (t))

void wait(unsigned long time_wait) {
  unsigned long start = millis();
  while (millis() - start < time_wait) {
    yield();
  };
}

#define BLYNK_PRINT Serial

#define Yuta
// #define TONTON

// Các thư viện
#include "used.h"
#include "Wifi_and_Blynk.h"
#include "Device.h"
#include "OLED_Display.h"
#include "Blynk_Control.h"
// #include "Google_calender.h"
#include "Setup_Loop.h"

void setup() {
  Serial.begin(9600);
  Setup_Run();  // function to start Pins
  delay(1000);
  Serial.println(ESP.getChipId());
}

void loop() {

  Blynk.run();
  bt_port.tick();  //Thư viện nút nhấn
  bt_touch.tick();
  Loop_Run();
}
