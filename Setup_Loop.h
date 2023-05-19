#include "core_esp8266_features.h"
#include "coredecls.h"
#define time_delay(t) for (static uint32_t _lasttime; \
                           (uint32_t)((uint32_t)millis() - _lasttime) >= (t); \
                           _lasttime = millis())

void onebutton_cound() {
  digitalWrite(mr, HIGH);
  bt_cound += 1;
  if (bt_cound >= 3) bt_cound = 0;
  delay(200);
  digitalWrite(mr, LOW);
}

typedef void (*FunctionPointer)();
FunctionPointer functions[] = {
  Oled_Clock,
  Oled_LOVE_DAY,
  Oled_Temp,
};

void Loop_Run() {

  time_delay(10000) {
    loop_AHT_Blynk();
  }

  time_delay(200) {
    functions[bt_cound]();
    Blynk.syncVirtual(love_button);
  }

  while (Miss_state == HIGH) {  // miss function

    if (Miss_state == HIGH) Oled_heart_animation();



    if (Miss_state == HIGH) {
      Blynk.syncVirtual(love_button);
      if (Miss_state == LOW) {  // Đối phương
        display.setFont();
        display.setTextSize(1);
        digitalWrite(mr, HIGH);
        oledDisplayCenter_W_H("I miss you");
        Miss_state = LOW;
        Blynk.virtualWrite(love_button, 0);
        delay(2000);
        digitalWrite(mr, LOW);
      }
    }

    if (Miss_state == HIGH) {
      if (digitalRead(buton_touch) == 1) {  // chính bạn
        delay(300);
        if (digitalRead(buton_touch) == 1) {
          Oled_off();
          Miss_state = LOW;
          Blynk.virtualWrite(love_button, 0);
          delay(20);
        }
      }
    }
  }
  // Serial.println(Light_Sensor());
}

//===========RUN===========
void Setup_Run() {

  Serial.begin(9600);

  pinMode(buton_touch, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(Lig_Sensor, INPUT);
  pinMode(mr, OUTPUT);
  Setup_onebutton();

  digitalWrite(mr, HIGH);

  Setup_NTPClient_time();
  Setup_AHT();
  Setup_Oled();
  Setup_updateOTA_LAN();

  delay(500);
  digitalWrite(mr, LOW);

  display.setTextSize(2);
  oledDisplayCenter_W_H("HI ^_^");
  delay(2000);
  String name;
  name += "My name is ";
  name += Name_device;
  display.setTextSize(1);
  oledDisplayCenter_W_H(name);
  delay(2000);
  // display.setFont(&FreeSans9pt7b);
  if (WiFi.status() != WL_CONNECTED) {
    display.clearDisplay();
    display.drawBitmap(64, 0, epd_bitmap_disconnect, 64, 64, 1);
    display.setCursor(0, 10);
    display.print("Connect to\nWiFi:");
    display.setCursor(0, 40);
    display.setTextSize(2);
    display.print(Name_device);
    display.display();
  }
  Setup_Wifi();  // function to connect_wifi
  Blynk_Wifi();
  Setup_updateOTA();

  display.setTextSize(1);
  display.clearDisplay();
  display.setCursor(0, 20);
  display.print("WIFI Connect:");

  display.setCursor(0, 30);
  display.print("SSID:");
  display.print(WiFi.SSID().c_str());

  display.setCursor(0, 50);
  display.print("PASS:");
  display.print(WiFi.psk().c_str());
  display.display();
  delay(2000);
  oledDisplayCenter_W_H("System is ready");
  delay(1500);
}
