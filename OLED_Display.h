//===========OLED===========
#include "OLED_SAVE.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Fonts/FreeSans9pt7b.h>

#define SCREEN_WIDTH 128  // OLED display width,  in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire, -1);

void Setup_Oled() {
  display.begin(0x3C, true);
  display.clearDisplay();
  display.display();
  display.setTextColor(SH110X_WHITE);
  display.setTextSize(1);
  display.clearDisplay();
}

void oledDisplayCenter_W_H(String text) {
  int16_t x1;
  int16_t y1;
  uint16_t width;
  uint16_t height;
  display.getTextBounds(text, 0, 0, &x1, &y1, &width, &height);

  // display on horizontal and vertical center
  display.clearDisplay();  // clear display
  display.setCursor((SCREEN_WIDTH - width) / 2, (SCREEN_HEIGHT - height) / 2);
  display.println(text);  // text to display
  display.display();
}

void Oled_off() {
  display.clearDisplay();
  display.display();
}

void Oled_Temp() {
  display.setFont(&FreeSans9pt7b);
  display.setTextSize(1);
  loop_AHT();
  display.clearDisplay();
  display.setCursor(0, 20);
  display.print(Name_device);

  display.setCursor(0, 40);
  display.print("Temp: ");
  display.print(Var_Putdata_Temp);
  display.println(" C");

  display.setCursor(0, 60);
  display.print("Hum : ");
  display.print(Var_Putdata_Hum);
  display.println(" %");
  display.display();
}

void Oled_LOVE_DAY() {
  display.setFont(&FreeSans9pt7b);
  display.setTextSize(1);
  display.clearDisplay();
  display.setCursor(0, 20);
  display.print("Hour: ");
  display.print((Day_Epochtime() - 1673834400) / 3600);

  display.setCursor(0, 40);
  display.print("Day: ");
  display.print((Day_Epochtime() - 1673834400) / 86400);

  display.setCursor(0, 60);
  display.print("Month: ");
  display.print((Day_Epochtime() - 1673834400) / 2629743);

  display.display();
}

void Oled_Clock() {
  display.setFont();
  display.setTextSize(2);
  String time;
  display.clearDisplay();
  timeClient.update();

  char HoursString[3];
  sprintf(HoursString, "%02d", timeClient.getHours());
  char minuteString[3];
  sprintf(minuteString, "%02d", timeClient.getMinutes());
  char SecondString[3];
  sprintf(SecondString, "%02d", timeClient.getSeconds());

  time = "";
  time += HoursString;
  time += ':';
  time += minuteString;
  time += ':';
  time += SecondString;
  oledDisplayCenter_W_H(time);

  // display.setCursor(0, 20);
  // display.print(daysOfTheWeek[timeClient.getDay()]);
  display.display();
  if ((timeClient.getHours() == 12) && (timeClient.getMinutes() == 0)) {
    Update_OTA();
  }
  if ((timeClient.getHours() == 4) && (timeClient.getMinutes() == 0)) {
    ESP.reset();
  }
}

void Oled_eyes_animation() {  // màn hình icon
  for (uint8_t i; frameallArray_LEN; i++) {
    display.clearDisplay();
    display.drawBitmap(22, 0, frameallArray[i], 85, 64, 1);
    display.display();
    delay(20);
  }
}

void Oled_heart_animation() {  // heart animation
  digitalWrite(mr, HIGH);
  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[0], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[1], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[2], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[3], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[4], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[5], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[6], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[7], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[8], 64, 64, 1);
  display.display();
  delay(20);
  digitalWrite(mr, LOW);
  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[9], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[10], 64, 64, 1);
  display.display();
  delay(20);
  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[11], 64, 64, 1);
  display.display();
  delay(20);

  digitalWrite(mr, HIGH);
  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[12], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[13], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[14], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[15], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[16], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[17], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[18], 64, 64, 1);
  display.display();
  delay(20);

  digitalWrite(mr, LOW);
  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[19], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[20], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[21], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[22], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[23], 64, 64, 1);
  display.display();
  delay(20);

  // digitalWrite(mr, HIGH);
  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[24], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[25], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[26], 64, 64, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(32, 0, heart_allArray[27], 64, 64, 1);
  display.display();
  delay(20);

  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[28], 64, 64, 1);
  // display.display();
  // delay(20);

  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[29], 64, 64, 1);
  // display.display();
  // delay(20);

  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[30], 64, 64, 1);
  // display.display();
  // delay(20);

  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[31], 64, 64, 1);
  // display.display();
  // delay(20);

  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[32], 64, 64, 1);
  // display.display();
  // delay(20);

  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[33], 64, 64, 1);
  // display.display();
  // delay(20);

  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[34], 64, 64, 1);
  // display.display();
  // delay(20);

  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[35], 64, 64, 1);
  // display.display();
  // delay(20);

  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[36], 64, 64, 1);
  // display.display();
  // delay(20);

  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[37], 64, 64, 1);
  // display.display();
  // delay(20);

  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[38], 64, 64, 1);
  // display.display();
  // delay(20);

  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[39], 64, 64, 1);
  // display.display();
  // delay(20);

  // digitalWrite(mr, LOW);
  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[40], 64, 64, 1);
  // display.display();
  // delay(20);

  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[41], 64, 64, 1);
  // display.display();
  // delay(20);

  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[42], 64, 64, 1);
  // display.display();
  // delay(20);

  // digitalWrite(mr, HIGH);
  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[43], 64, 64, 1);
  // display.display();
  // delay(20);

  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[44], 64, 64, 1);
  // display.display();
  // delay(20);

  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[45], 64, 64, 1);
  // display.display();
  // delay(20);

  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[46], 64, 64, 1);
  // display.display();
  // delay(20);

  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[47], 64, 64, 1);
  // display.display();
  // delay(20);

  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[48], 64, 64, 1);
  // display.display();
  // delay(20);

  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[49], 64, 64, 1);
  // display.display();
  // delay(20);

  // digitalWrite(mr, LOW);
  // display.clearDisplay();
  // display.drawBitmap(32, 0, heart_allArray[51], 64, 64, 1);
  // display.display();
  // delay(20);
}

// void Oled_heart_animation() {  // màn hình icon
//   for (unsigned int h; 27; h++) {
//     display.clearDisplay();
//     display.drawBitmap(32, 0, heart_allArray[h], 64, 64, 1);
//     display.display();
//     // Blynk.virtualWrite(Update_Code, 0);
//     delay(20);
//   }
//   bt_cound = 0;
// }
