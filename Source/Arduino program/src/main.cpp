#include <Arduino.h>
//knihovny pro displej
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//knihovny pro RTC
#include <Time.h>
#include "DS3231.h"

int INTERRUPT_PIN = 2; 
int h = 1;
int m = 12;
int s = 24;
int t = 4563;
bool h_flag = false;
bool m_flag = false;
bool s_flag = false;

bool boom = false;

char cas[] = {'0','1',':','1','2',':','2','6'};

LiquidCrystal_I2C lcd(0x3F,16,2); 

bool alarm;
int count = 255;
DS3231 clock;


void Boom(){
  boom = true;
  lcd.clear();
  lcd.print("Boom");
}
void pocitej(){
   lcd.clear();
   h = (t/3600);
   Serial.println(h);
   m = (t-h*3600)/60;
   Serial.println(m);
   s = t-(m*60+h*3600);
   Serial.println(s);
   t--;
   if(t == 0){
     Boom();
   }
   else{
    lcd.print(h);
    lcd.print(":");
    lcd.print(m);
    lcd.print(":");
    lcd.print(s);
   }  
}
void AlarmInterrupt(){
  alarm = true;
  if(!boom){
    pocitej();
  }  
}

void setup() {
   Serial.begin(9600);
   delay(5000);
   clock.begin();
   clock.armAlarm1(false);
   clock.armAlarm2(false);
   clock.clearAlarm1();
   clock.clearAlarm2();
   clock.enable32kHz(false);
   clock.setOutput(DS3231_1HZ);
   clock.enableOutput(true);
   pinMode(2,INPUT_PULLUP);
   if (clock.isOutput())
   {
     Serial.println("Oscilator is enabled");
   } else
   {
     Serial.println("Oscilator is disabled");
   }
   //clock.setDateTime(2014, 4, 25, 0, 0, 0);
   //setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
   

   Serial.println("Initialize DS3231");;
   
   lcd.init();// inicializuje displej
   lcd.backlight(); // zapne podsvětlení
   lcd.print("Ahoj lidi"); // vypíše text
   alarm = false;
   attachInterrupt(2, AlarmInterrupt, RISING);
}


void loop() {
  
}