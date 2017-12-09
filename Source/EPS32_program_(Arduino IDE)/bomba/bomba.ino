#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS3231.h>
#include <LiquidCrystal_PCF8574.h>
#include "Klavesnice.h"
#include "EEPROM.h"

#define EEPROM_SIZE 64
#define ADRESA_AKTIVACE 1
#define ADRESA_DEAKTIVACE 17
#define ADRESA_REZIM  0
#define CAS_VYBUCHU  33
#define CAS_HRY 37

class Bomba{
    public:
      long casDoVybuchu = 30;
      char *aktivace;
      char *deaktivace;
      int delka_pinu = 16;
      int neuspesna_dekativace = 0;
};
bool preruseno = false;
bool zneskodneno = false;


char ZadanyPIN[16];
Bomba b;
RtcDS3231<TwoWire> Rtc(Wire);
const byte interruptPin = 2;
volatile bool state = false;
LiquidCrystal_PCF8574 lcd(0x3F); 
int radky[4] = {32,33,25,26};
int sloupce[4] = {27,14,12,13};
long DelkaHry;
Key k;
int h;
int m;
int s;
//int t = 4563;

bool boom = false;

void Game(bool nacteno);
int NastavCas(char zprava[]);
void NastavPin(bool neco, char kod[16]);
void NastavMode(char rezim);
char NactiHerniRezim();
void NactiPin(bool rezim,char pin[16]);
long NactiCas(bool rezim);
void ZadejHerniRezim_Pom();
char ZadejHerniRezim();
void Game (bool nacteno);
void Config();
void Boom();
void pocitej();
void AlarmInterrupt(){
  if(!boom){
    pocitej();
  }
}

void setup() {
  pinMode(interruptPin,INPUT_PULLUP);
  Serial.begin(9600);
  Wire.begin();
  Rtc.Begin();
  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeClock);
  Rtc.SetSquareWavePinClockFrequency(DS3231SquareWaveClock_1Hz);
  //attachInterrupt(interruptPin, AlarmInterrupt, RISING );
  lcd.begin(16, 2);
  k.Init(radky,sloupce,4,4);
  lcd.setBacklight(255);
  lcd.print("Zapinani....");
  delay(2000);
  if(k.stiskTl() == '#')
      Config();
  else{
      lcd.clear();
      Game(false);
    }
  
}

void loop() {
 
}

