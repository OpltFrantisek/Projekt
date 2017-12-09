#include <Arduino.h>
//knihovny pro displej
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//knihovny pro RTC
#include <Time.h>
#include "DS3231.h"
#define eeprom B1010000

#include <Keypad.h>
char PIN1[16];
char PIN2[16];
long DelkaHry;
long CasDoVybuchu;
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
//int t = 4563;

bool boom = false;

//char cas[] = {'0','1',':','1','2',':','2','6'};

LiquidCrystal_I2C lcd(0x3F,16,2);

bool alarm;
DS3231 clock;

void Game(bool nacteno);


void eeprom_zapis_zpravu( int adresaZarizeni, unsigned int adresaCteniZpravy, byte* data, byte delkaDat ) {
  Wire.beginTransmission(adresaZarizeni);
  Wire.write((int)(adresaCteniZpravy >> 8)); // MSB
  Wire.write((int)(adresaCteniZpravy & 0xFF)); // LSB
  byte c;
  for ( c = 0; c < delkaDat; c++)
    Wire.write(data[c]);
  Wire.endTransmission(adresaZarizeni);
}
// podprogram pro vymazání zprávy
void eeprom_vymaz_zpravu( int adresaZarizeni, unsigned int adresaCteniZpravy, byte delkaDat ) {
  Wire.beginTransmission(adresaZarizeni);
  Wire.write((int)(adresaCteniZpravy >> 8)); // MSB
  Wire.write((int)(adresaCteniZpravy & 0xFF)); // LSB
  byte c;
  for ( c = 0; c < delkaDat; c++)
    Wire.write(0xFF);
  Wire.endTransmission(adresaZarizeni);
}
// podprogram pro přečtení zprávy
void eeprom_precti_zpravu( int adresaZarizeni, unsigned int adresaCteni, byte *uloziste, int delkaDat ) {
  Wire.beginTransmission(adresaZarizeni);
  Wire.write((int)(adresaCteni >> 8)); // MSB
  Wire.write((int)(adresaCteni & 0xFF)); // LSB
  Wire.endTransmission(adresaZarizeni);
  Wire.requestFrom(adresaZarizeni,delkaDat);
  int c = 0;
  for ( c = 0; c < delkaDat; c++ )
    if (Wire.available()) uloziste[c] = Wire.read();
}
// podprogram pro přečtení zprávy
int NastavCas(char zprava[]){
  int index=0;
  int cisla[8] = {0,0,-1,0,0,-1,0,0};
  lcd.setCursor(index, 0);
   lcd.print(zprava); // vypĂ­Ĺˇe text
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

void UlozMode(char mode){
  eeprom_zapis_zpravu(eeprom, 0, (byte *)mode, sizeof(mode));
}
void NastavPin(bool neco, char kod[16]){
    lcd.cursor_on();
    lcd.setCursor(0,0);
    if(neco){
      lcd.print("Nastav PIN1:");
    }
    else{
      lcd.print("Nastav PIN2:");
    }
    //char kod[16];
    for(int index=0;index<16;index++){
      lcd.setCursor(index,1);
      char znak;
      while(!(znak =customKeypad.getKey()) )
      kod[index]= znak;
      lcd.print(znak);
    }
    if(neco){
      eeprom_zapis_zpravu(eeprom, 20, (byte *)PIN1, sizeof(PIN1));
    }
    else{
      eeprom_zapis_zpravu(eeprom, 40, (byte *)PIN2, sizeof(PIN2));
    }
    lcd.clear();
    lcd.cursor_off();
  //return kod;
}

void NastavMode(char mode){
  lcd.clear();
  lcd.print(mode == 2?"1":"2");
  UlozMode(mode);//uloží do eeprom
  NastavPin(true,PIN1);
  NastavPin(false,PIN2);
  if(mode!=2)
    CasDoVybuchu=NastavCas("Cas vybuchu:");
  if(mode!=1)
    DelkaHry=NastavCas("Cas hry:");
  Game(true);
}
char NactiHerniRezim(){
  char mode;
  eeprom_precti_zpravu(eeprom,0,(byte *)mode, sizeof(mode));
  return (char)mode;
}
void NactiPin(bool rezim,char pin[16]){
  pin = "123456789123456";
}
long NactiCas(bool rezim){
  return 15L;
}
void Hra1(){


}
void Hra2(){}
void Hra3(){}
void ZadejHerniRezim_Pom(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("herni rezim");
  lcd.setCursor(0,1);
}
char ZadejHerniRezim(){
  char rezim = 1;
  ZadejHerniRezim_Pom();
  lcd.print("Search & Destroy");
  while(true){
      char customKey = customKeypad.getKey();
      if(customKey == '#'){
        ZadejHerniRezim_Pom();
        rezim++;
        if(rezim == 4)
          rezim = 1;
      }
      if(customKey == '*'){
        ZadejHerniRezim_Pom();
        rezim--;
        if(rezim == 0)
          rezim = 3;
      }
      if(customKey == 'D'){
          lcd.clear();
          return rezim;
      }
      if(customKey == '*' || customKey == '#'){
        switch(rezim){
          case 1: lcd.print("Search & Destroy");break;
          case 2: lcd.print("Domination");break;
          case 3: lcd.print("Sabotage");break;
        }
    }
  }
  return 1;
}
void Game (bool nacteno){
 char mode;
 if(nacteno)
    mode= NactiHerniRezim();
  else{
    mode=NactiHerniRezim();//načítáme z eeprom
    NactiPin(true,PIN1);
    NactiPin(false,PIN2);
    delay(1000);
    if(mode!=2)
      CasDoVybuchu=NactiCas(true);//cas do vybuchu, když bude true... nacti délku, když bude false
    if (mode!=1)
        DelkaHry=NactiCas(false);
  }
  switch(mode){
    case 1: Hra1();break;
    case 2: Hra2();break;
    case 3: Hra3();break;
  }
}
void Config(){
  char mode= ZadejHerniRezim();
  NastavMode(mode);

}
void Boom(){
  boom = true;
  lcd.clear();
  lcd.print("Boom");
}
void pocitej(){
   lcd.clear();
   h = (CasDoVybuchu/3600);
   Serial.println(h);
   m = (CasDoVybuchu-h*3600)/60;
   Serial.println(m);
   s = CasDoVybuchu-(m*60+h*3600);
   Serial.println(s);
   CasDoVybuchu--;
   if(CasDoVybuchu == 0){
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

   if(customKeypad.getKey() == '#')
      Config();
   else
     Game(false);
   //CasDoVybuchu = NastavCas("Nastav cas:");
   clock.enableOutput(true);
}
void loop() {

}
