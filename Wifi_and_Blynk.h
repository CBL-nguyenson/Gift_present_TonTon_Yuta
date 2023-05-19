
//========================= Wifi_ Connect ====================== kết nối wifi
#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp8266.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
void restartMCU() {
  ESP.restart();
  delay(1000);
  ESP.reset();
  while (1) {};
}

void wifi_reset() {  //reset wifi
  WiFiManager wifiManager;
  wifiManager.resetSettings();
}
void configModeCallback(WiFiManager* myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());                       // in ra địa chỉ wifi
  Serial.println(myWiFiManager->getConfigPortalSSID());  //in ra tên wifi sẽ phát ra
}

void Setup_Wifi() {  // khởi động wifi
  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);
  if (!wifiManager.autoConnect(Name_device)) {
    Serial.println("KẾT NỐI THẤT BẠI ĐANG RESET ESP CHỜ.....");
    ESP.reset();  //Nếu kết nối thất bại, thử kết nối lại bằng cách reset thiết bị
    delay(500);
  }
}

void Blynk_Wifi() {                                                        // kết nối mạch với blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, WiFi.SSID().c_str(), WiFi.psk().c_str());  //Kết nối vào Server
  while (!Blynk.connected()) {
    Serial.print(".");
    delay(500);
  }
  Blynk.virtualWrite(Update_Code, 0);
}

//==============================================================
//========================= OTA ====================== hệ thống nạp code từ xa

#include <otadrive_esp.h>
void Setup_updateOTA() {
  OTADRIVE.setInfo(URT_OTA, OTA_Firmware);
  // OTADRIVE.onUpdateFirmwareProgress(ota_proggress);
}

void Update_OTA() {
  if (WiFi.status() == WL_CONNECTED) {
    OTADRIVE.updateFirmware();
  }
}


//==============================================================
//========================= OTA_lan ====================== hệ thống nạp code từ xa qua mạng lan

#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>

void Setup_updateOTA_LAN() {
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname(Name_device);

  // No authentication by default
  ArduinoOTA.setPassword(Name_device);

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


//===========NTPclient.==========
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>

char daysOfTheWeek[7][12] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 7 * 3600, 60000);  //7 là múi giờ

void Setup_NTPClient_time() {
  timeClient.begin(7);
  struct tm timeinfo = { 0 };
  timeinfo.tm_year = 2023 - 1900;  // Năm tính từ 1900
  timeinfo.tm_mon = 0;             // Tháng 1 (tính từ 0)
  timeinfo.tm_mday = 16;           // Ngày 16
  timeinfo.tm_hour = 0;            // Giờ 9
  timeinfo.tm_min = 0;             // Phút 0
  timeinfo.tm_sec = 0;             // Giây 0
  time_t epoch_time_day_love = mktime(&timeinfo);
}

void Loop_NTPClient_time() {
  timeClient.update();
  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
}

unsigned long Day_Epochtime() {
  timeClient.update();
  return timeClient.getEpochTime();
}
