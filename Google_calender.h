#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// Thông tin xác thực Adafruit IO
#define IO_USERNAME "nguyenson"
#define IO_KEY "aio_TaLR528FhBX7bACl8ZeD1oluSw1u"

// ID của feed
const char* feedId = "calender-son";

String Get_calender() {
  // Gửi yêu cầu HTTP GET để lấy dữ liệu từ webhook
  HTTPClient http;
  String webhookURL = "https://io.adafruit.com/api/v2/" + String(aioUsername) + "/feeds/" + String(feedId);
  http.begin(webhookURL);
  http.addHeader("X-AIO-Key", aioKey);
  int httpResponseCode = http.GET();

  // Kiểm tra mã phản hồi
  if (httpResponseCode == HTTP_CODE_OK) {
    String response = http.getString();

    // Phân tích phản hồi JSON
    DynamicJsonDocument jsonDoc(512);
    deserializeJson(jsonDoc, response);
    JsonObject root = jsonDoc.as<JsonObject>();

    // Lấy giá trị trong phần last_value
    if (root.containsKey("last_value")) {
      String lastValue = root["last_value"].as<String>();
      Serial.println("Last Value:");
      Serial.println(lastValue);

    } else {
      Serial.println("Last Value not found");
    }
  } else {
    Serial.print("Error accessing URL. HTTP code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
  return lastValue;
}
