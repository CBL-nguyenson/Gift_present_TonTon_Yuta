#include <sys/types.h>
//==============================================================
//========================= Device ======================
#include "OneButton.h"
#define PIN_INPUT_PORT D3
OneButton bt_port(PIN_INPUT_PORT, true);
OneButton bt_touch(buton_touch, false);  //vcc-false; gnd-true

uint8_t bt_cound = 0;
bool shouldBreak = false;

void onebutton_cound();
void Loop_updateOTA_LAN();
void Miss_button();
void Oled_heart_animation();

void Setup_onebutton() {
  bt_port.attachLongPressStart(wifi_reset);
  bt_port.attachClick(Loop_updateOTA_LAN);

  bt_touch.attachLongPressStart(Miss_button);
  bt_touch.attachClick(onebutton_cound);
}

//===========AHT(TEMP)===========
#include <Adafruit_AHTX0.h>
Adafruit_AHTX0 aht;

void Setup_AHT() {
  aht.begin();
}

void loop_AHT() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  Var_Putdata_Temp = temp.temperature;
  Var_Putdata_Hum = humidity.relative_humidity;
}

void loop_AHT_Blynk() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  Var_Putdata_Temp = temp.temperature;
  Var_Putdata_Hum = humidity.relative_humidity;
  Blynk.virtualWrite(Putdata_Temp, Var_Putdata_Temp);
  Blynk.virtualWrite(Putdata_Hum, Var_Putdata_Hum);
}
//===========MR===========
void mr_run() {
  // Serial.println(digitalRead(buton_touch));
  if (digitalRead(buton_touch) == 1) {
    digitalWrite(mr, HIGH);
  } else {
    digitalWrite(mr, LOW);
  }
}

//===========Light_Sensor===========


byte Light_Sensor() {
  uint8_t lig = map(analogRead(Lig_Sensor), 0, 1024, 100, 0);
  // Serial.println(lig);
  // Blynk.virtualWrite(MD_Light, lig);
  return lig;
}
