
#include <Arduino.h>
#include <Wire.h>         // this #include still required because the RTClib depends on it
#include "RTClib.h"
//#include <virtuabotixRTC.h>
#include <LiquidCrystal.h>

#define relay1      0
#define relay2      1
#define relay3      2
#define relay4      3
#define relay5      12
#define relay6      13
#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

RTC_Millis rtc;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
void setup() {
 Serial.begin(9600);
 pinMode(0, OUTPUT);
 pinMode(1, OUTPUT);
 pinMode(2, OUTPUT);
 pinMode(3, OUTPUT);
 pinMode(12, OUTPUT);
 pinMode(13, OUTPUT);
    rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

}

void loop() {
DateTime now = rtc.now();  // put your main code here, to run repeatedly:
lcd.setCursor(3,0); 
lcd.print(now.hour(), DEC);
lcd.print(':');
lcd.print(now.minute(), DEC);
lcd.print(':');
lcd.print(now.second(), DEC);
delay(1000);
Serial.print(now.hour(), DEC);
Serial.print(':');
Serial.print(now.minute(), DEC);
Serial.print(':');
Serial.print(now.second(), DEC);
Serial.println();    
Serial.print(" seconds since 1970: ");
Serial.println(now.unixtime());
delay(3000);
int jam = now.hour();
int menit = now.minute();
int detik = now.second();
 
int waktu[3] = {jam,menit,detik};

if (( waktu >= 17,00,00)||(waktu <= 06,00,00)) {
 lcd.setCursor(1,1); 
 lcd.print("Lampu 123456 ON");
 digitalWrite(relay1,HIGH);
 delay(1500);
 digitalWrite(relay2,HIGH);
 delay(2000);
 digitalWrite(relay3,HIGH);
 delay(2500);
 digitalWrite(relay4,HIGH);
 delay(3000);
 digitalWrite(relay5,HIGH);
 delay(3500);
 digitalWrite(relay6,HIGH);
 delay(4000); 
}
 else{
 
digitalWrite(relay1,LOW);
 delay(1000); 
 digitalWrite(relay2,LOW);
 delay(1000); 
 digitalWrite(relay3,LOW);
 delay(1000); 
 digitalWrite(relay4,LOW);
 delay(1000); 
 digitalWrite(relay5,LOW);
 delay(1000); 
 digitalWrite(relay6,LOW);
 delay(1000); 
}
}
