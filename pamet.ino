void zapisCharArray(int adresa,int velikost, char pole[16]){
    EEPROM.begin(EEPROM_SIZE);
    for(int i = 0; i < velikost;i++){
        EEPROM.write(adresa+i,pole[i]);
        Serial.print("zapisuji => ");
        Serial.println((int)pole[i]);
      }
    EEPROM.end();
 }
 char *ctiCharArray(int adresa,int velikost, char *pole){
    EEPROM.begin(EEPROM_SIZE);
    for(int i = 0; i < velikost;i++){
       pole[i] = EEPROM.read(adresa+i);
       Serial.print("ctu => ");
       Serial.println((int)pole[i]);     
      }
    EEPROM.end();
    return pole;
 }
 void zapisLong(int adresa, long cislo){
     EEPROM.begin(EEPROM_SIZE);
     EEPROM.write(adresa,cislo);
     EEPROM.end();
  }
 long ctiLong(int adresa){
     long cislo;
     EEPROM.begin(EEPROM_SIZE);
     cislo = EEPROM.read(adresa);
     EEPROM.end();
     return cislo;
}
void zapisChar(int adresa,char znak){
     EEPROM.begin(EEPROM_SIZE);
     EEPROM.write(adresa,znak);
     EEPROM.commit();
     EEPROM.end();
  }
char ctiChar(int adresa){
     EEPROM.begin(EEPROM_SIZE);
     char znak = EEPROM.read(adresa);
     EEPROM.end();
     return znak;
  }
