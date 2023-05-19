

BLYNK_WRITE(Getdata_Temp) {
  Blynk.syncVirtual(V2);
  float Var_Getdata_Temp = param.asDouble();
  Serial.println(Var_Getdata_Temp);
}

BLYNK_WRITE(Getdata_Hum) {
  float Var_Getdata_Hum = param.asDouble();
  Serial.println(Var_Getdata_Hum);
}

BLYNK_WRITE(terminal) {
  float lig = param.asDouble();
}

BLYNK_WRITE(Update_Code) {
  if (param.asInt() == 1) {
    Update_OTA();
  }
}

uint8_t Miss_state = LOW;
void Miss_button() {
  Miss_state = HIGH;
  Blynk.virtualWrite(love_button, 1);
}

BLYNK_WRITE(love_button) {
  if (param.asInt() == 1) {
    Miss_state = HIGH;
  }
  if (param.asInt() == 0) {
    Miss_state = LOW;
  }
}

BLYNK_READ(V1) {
}

void Loop_updateOTA_LAN() {  //Mở cổng OTA lan
  while (true) {
    display.clearDisplay();
    display.drawBitmap(64, 0, epd_bitmap_dowload_img, 64, 64, 1);
    display.setFont();
    display.setTextSize(1);
    display.setCursor(0, 40);
    display.print("Password:");
    display.setCursor(0, 50);
    display.setTextSize(2);
    display.print(Name_device);
    display.display();
    // bt_cound = 0;
    ArduinoOTA.handle();
    if (digitalRead(buton_touch) == 1) {
      break;
    }
  }
}
