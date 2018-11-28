#include "WM.h"

#include <WiFi.h>
#include <time.h>
 
#define JST     3600* 9
 
const char* ssid = "AndroidAP";
const char* password = "12345678";
 
void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.print("\n\nStart\n");
 
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println();
  Serial.printf("Connected, IP address: ");
  Serial.println(WiFi.localIP());


//  unsigned long value = 1896456;
//  byte * tes = (byte *)&value;
//  Serial.print("before - ");
//  for(int i = 0; i < 8; i++) {
//    char str[3];
//    sprintf(str, "%02x:", tes[i]);
//    Serial.print(str);
//  }
//  Serial.println();
// 
  configTime( JST, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp");
}
 
void loop() {
  time_t now;
  struct tm *tm;
 
  now = time(NULL);


  unsigned long t = now / 30000;

  generateToken("GRBDCMKTGVGEIU2Q", t, 6);

  tm = localtime(&now);
  Serial.printf("%04d-%02d-%02d %02d:%02d:%02d - ",
        tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
        tm->tm_hour, tm->tm_min, tm->tm_sec);
        
  Serial.println();
//  tm = localtime(&t);
//  Serial.printf(" %04d-%02d-%02d %02d:%02d:%02d - ",
//        tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
//        tm->tm_hour, tm->tm_min, tm->tm_sec);
//  test();

 
  delay(1000);
}
