#include <Arduino.h>
//knihovny pro displej
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//knihovny pro RTC
#include <Time.h>
#include "DS3231.h"

#include <Keypad.h>
//keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


//-----------------------------------------------------------------------

int INTERRUPT_PIN = 10; 
int h;
int m;
int s;
int t = 4563;

bool boom = false;

//char cas[] = {'0','1',':','1','2',':','2','6'};

LiquidCrystal_I2C lcd(0x3F,16,2); 

bool alarm;
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
int NastavCas(){
  int index=0;
  int cisla[8] = {0,0,-1,0,0,-1,0,0};
  lcd.setCursor(index, 0);
   lcd.print("Nastav cas:"); // vypĂ­Ĺˇe text
   lcd.setCursor(index, 1);
    lcd.print("00:00:00");
    lcd.setCursor(index, 1);
    lcd.cursor_on();
    while(true){
      char customKey = customKeypad.getKey();
      switch(customKey){
        case 'D': break;
        case '*': if(index > 0){
                        index--;
                        lcd.setCursor(index, 1);
                      }
                  break;
        case '#': if(index < 15){
                        index++;
                        lcd.setCursor(index, 1);
                      }
                  break;
      case '0': if(index != 2 && index != 5){cisla[index] = 0;lcd.print(0);}index++;lcd.setCursor(index,1);break;
      case '1': if(index != 2 && index != 5){cisla[index] = 1;lcd.print(1);}index++;lcd.setCursor(index,1);break;
      case '2': if(index != 2 && index != 5){cisla[index] = 2;lcd.print(2);}index++;lcd.setCursor(index,1);break;
      case '3': if(index != 2 && index != 5){cisla[index] = 3;lcd.print(3);}index++;lcd.setCursor(index,1);break;
      case '4': if(index != 2 && index != 5){cisla[index] = 4;lcd.print(4);}index++;lcd.setCursor(index,1);break;
      case '5': if(index != 2 && index != 5){cisla[index] = 5;lcd.print(5);}index++;lcd.setCursor(index,1);break;
      case '6': if(index != 2 && index != 5){cisla[index] = 6;lcd.print(6);}index++;lcd.setCursor(index,1);break;
      case '7': if(index != 2 && index != 5){cisla[index] = 7;lcd.print(7);}index++;lcd.setCursor(index,1);break;
      case '8': if(index != 2 && index != 5){cisla[index] = 8;lcd.print(8);}index++;lcd.setCursor(index,1);break;
      case '9': if(index != 2 && index != 5){cisla[index] = 9;lcd.print(9);}index++;lcd.setCursor(index,1);break;
      }
      if (customKey =='D')
        break;

    }
    int h = cisla[0]*10+cisla[1];
    int m = cisla[3]*10+cisla[4];
    int s = cisla[6]*10+cisla[7];
    int cas = h*3600+m*60+s;
    lcd.clear();
    lcd.cursor_off();
    return cas;
}

void setup() {
   Serial.begin(9600);
   delay(5000);
   clock.begin();

   clock.enable32kHz(false);
   clock.setOutput(DS3231_1HZ);
   clock.enableOutput(false);
   pinMode(INTERRUPT_PIN,INPUT_PULLUP);

   Serial.println("Initialize DS3231");;

   lcd.init();// inicializuje displej
   lcd.backlight(); // zapne podsvětlení
   lcd.print("Ahoj lidi"); // vypíše text
   alarm = false;
   attachInterrupt(INTERRUPT_PIN, AlarmInterrupt, RISING);
   t = NastavCas();
   clock.enableOutput(true);
}


void loop() {
  
}