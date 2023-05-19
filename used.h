#include <ESP8266WiFi.h>
#define URT_OTA "f523b409-11ef-45cb-866b-fd5c1c72ceaf"



//===========================DTQT===========================
#ifdef TONTON
#define BLYNK_TEMPLATE_ID "TMPLsrKTdMLH"
#define BLYNK_TEMPLATE_NAME "Gift for love"
#define BLYNK_AUTH_TOKEN "FjBl2_gt2PD2pcFoqQIjpTATge_iwrgE"
#define OTA_Firmware "1.2.16"
#define Name_device "TonTon"
#define Getdata_Temp V1
#define Getdata_Hum V3
#define Putdata_Temp V2
#define Putdata_Hum V4
#define Update_Code V0
#define terminal V6
#define love_button V20
#endif
////===========================NHTS===========================
#ifdef Yuta
#define BLYNK_TEMPLATE_ID "TMPLsrKTdMLH"
#define BLYNK_TEMPLATE_NAME "Gift for love"
#define BLYNK_AUTH_TOKEN "FjBl2_gt2PD2pcFoqQIjpTATge_iwrgE"
#define OTA_Firmware "1.0.16"
#define Name_device "Yuta"
#define Getdata_Temp V2
#define Getdata_Hum V4
#define Putdata_Temp V1
#define Putdata_Hum V3
#define Update_Code V0
#define terminal V5
#define love_button V20
#endif



//========Variable========
float Var_Getdata_Temp;
float Var_Getdata_Hum;

String VarPUT_Temp_Hum;
float Var_Putdata_Temp;
float Var_Putdata_Hum;
float Var_Update_Code;

//=======Pin======

#define buton_touch D6
#define led D2
#define Lig_Sensor A0
#define mr D8



