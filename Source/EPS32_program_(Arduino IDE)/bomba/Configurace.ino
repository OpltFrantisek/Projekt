int NastavCas(char zprava[]){
  int index=0;
  char cisla[8] = {0,0,'1',0,0,'1',0,0};
  lcd.setCursor(index, 0);
   lcd.print(zprava); // vypĂ­Ĺˇe text
   lcd.setCursor(index, 1);
    lcd.print("00:00:00");
    lcd.setCursor(index, 1);
    lcd.cursor();
    while(true){
      char customKey = k.stiskTl();
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
      case '0': if(index != 2 && index != 5){cisla[index] = '0';lcd.print(0);}index++;lcd.setCursor(index,1);break;
      case '1': if(index != 2 && index != 5){cisla[index] = '1';lcd.print(1);}index++;lcd.setCursor(index,1);break;
      case '2': if(index != 2 && index != 5){cisla[index] = '2';lcd.print(2);}index++;lcd.setCursor(index,1);break;
      case '3': if(index != 2 && index != 5){cisla[index] = '3';lcd.print(3);}index++;lcd.setCursor(index,1);break;
      case '4': if(index != 2 && index != 5){cisla[index] = '4';lcd.print(4);}index++;lcd.setCursor(index,1);break;
      case '5': if(index != 2 && index != 5){cisla[index] = '5';lcd.print(5);}index++;lcd.setCursor(index,1);break;
      case '6': if(index != 2 && index != 5){cisla[index] = '6';lcd.print(6);}index++;lcd.setCursor(index,1);break;
      case '7': if(index != 2 && index != 5){cisla[index] = '7';lcd.print(7);}index++;lcd.setCursor(index,1);break;
      case '8': if(index != 2 && index != 5){cisla[index] = '8';lcd.print(8);}index++;lcd.setCursor(index,1);break;
      case '9': if(index != 2 && index != 5){cisla[index] = '9';lcd.print(9);}index++;lcd.setCursor(index,1);break;
      }
      if (customKey =='D' || index > 10)
        break;

    }
    //int h = cisla[0]*10+cisla[1];
   // int m = cisla[3]*10+cisla[4];
   // int s = cisla[6]*10+cisla[7];
    //int cas = h*3600+m*60+s;
    zapisChar(CAS_VYBUCHU,cisla[0]);
    zapisChar(CAS_VYBUCHU+1,cisla[1]);

    zapisChar(CAS_VYBUCHU+2,cisla[3]);
    zapisChar(CAS_VYBUCHU+3,cisla[4]);
    
    zapisChar(CAS_VYBUCHU+4,cisla[6]);
    zapisChar(CAS_VYBUCHU+5,cisla[7]);  
       
    lcd.clear();
    lcd.noCursor();
    return 5;
}
void NastavPin(bool neco){
    lcd.cursor();
    lcd.setCursor(0,0);
    char  pin[16];
    if(neco){
      lcd.print("Nastav PIN1:");
    }
    else{
      lcd.print("Nastav PIN2:");
    }
    
    //char kod[16];
    char znak;
    for(int index=0;index<b.delka_pinu;index++){
      lcd.setCursor(index,1);
      znak =k.stiskTl();
       switch(znak){
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9': pin[index]= znak; Serial.println(int(pin[index]));lcd.print(znak);break;
          default : index--;
        }     
    }
    if(neco){
      zapisCharArray(ADRESA_AKTIVACE,b.delka_pinu,pin);
      //eeprom_zapis_zpravu(eeprom, 20, (byte *)PIN1, sizeof(PIN1));
    }
    else{
      zapisCharArray(ADRESA_DEAKTIVACE,b.delka_pinu,pin);
      //eeprom_zapis_zpravu(eeprom, 40, (byte *)PIN2, sizeof(PIN2));
    }
    lcd.clear();
    lcd.noCursor();
  //return kod;
}
void NastavMode(char rezim){
  zapisChar(ADRESA_REZIM,rezim);
  NastavPin(true);
  NastavPin(false);
  if(rezim!=2)
    b.casDoVybuchu = NastavCas("Cas vybuchu:");
  if(rezim!=1)
    DelkaHry=NastavCas("Cas hry:");

}
void Config(){
  char rezim= ZadejHerniRezim();
  NastavMode(rezim);
  Game(true);
}

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
      char customKey = k.stiskTl();     
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
      if(customKey == '0'){
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

