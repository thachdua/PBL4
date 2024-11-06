/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
#define BLYNK_TEMPLATE_ID "TMPL6K023mA7M"
#define BLYNK_TEMPLATE_NAME "4RL"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"

WidgetLED LED_KETNOI(V0);
unsigned long timeT = millis();
void setup()
{
  Serial.begin(115200);
  delay(100);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
  //Chương trình điều khiển LED KET NOI chớp tắt mỗi giây
  if(millis()-timeT>1000){
    if(LED_KETNOI.getValue()) LED_KETNOI.off();
    else LED_KETNOI.on();
    timeT=millis();
  }
}
BLYNK_CONNECTED(){
  Blynk.syncAll(); //Đồng bộ data từ server xuống esp khi kết nối
}
BLYNK_WRITE(V1){ 
  int p = param.asInt();
  digitalWrite(D1,p);
}
BLYNK_WRITE(V2){ 
  int p = param.asInt();
  digitalWrite(D2,p);
}
BLYNK_WRITE(V3){ 
  int p = param.asInt();
  digitalWrite(D5,p);
}
BLYNK_WRITE(V4){ 
  int p = param.asInt();
  digitalWrite(D6,p);
}
