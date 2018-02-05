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
 void zapisLong(int adresa, long value){
     EEPROM.begin(EEPROM_SIZE);
     byte four = (value & 0xFF);
     byte three = ((value >> 8) & 0xFF);
     byte two = ((value >> 16) & 0xFF);
     byte one = ((value >> 24) & 0xFF);
     EEPROM.write(adresa, four);
     EEPROM.write(adresa + 1, three);
     EEPROM.write(adresa + 2, two);
     EEPROM.write(adresa + 3, one);     
     EEPROM.end();
  }
 long ctiLong(int adresa){

     long four = EEPROM.read(adresa);
     long three = EEPROM.read(adresa + 1);
     long two = EEPROM.read(adresa + 2);
     long one = EEPROM.read(adresa + 3);
     return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
  
    // long cislo;
    // EEPROM.begin(EEPROM_SIZE);
     //cislo = EEPROM.read(adresa);
     //EEPROM.end();
    
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
