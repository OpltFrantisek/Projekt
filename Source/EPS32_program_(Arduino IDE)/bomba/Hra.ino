void Game(bool stat){
  lcd.print("game");
   char rezim;
   rezim = ctiChar(ADRESA_REZIM);
   b.casDoVybuchu = ctiLong(CAS_VYBUCHU);
   b.aktivace = new char[16];
   b.deaktivace = new char[16];
   b.aktivace = ctiCharArray(ADRESA_AKTIVACE,16,b.aktivace);
   b.deaktivace = ctiCharArray(ADRESA_DEAKTIVACE,16,b.deaktivace);
   
   b.casDoVybuchu = 30;
   for(int i = 0; i < 16;i++){
      Serial.print("aktivace => ");
      Serial.println(b.aktivace[i]);
    }
    for(int i = 0; i < 16;i++){
      Serial.print("deaktivace => ");
     Serial.println(b.deaktivace[i]);
    }
  
   switch(rezim){
       case 1:Hra1();break;
       case 2:lcd.print("2");break;
       case 3:lcd.print("3");break;
   }  
  }
void ZadejPIN(){
  preruseno = true;
  lcd.setCursor(0,0);
  lcd.print("Zadej pin:");
  lcd.setCursor(0,1);
  lcd.cursor();
    for(int index=0;index<16;index++){
       lcd.setCursor(index,1);
       char znak;     
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
          case '9': ZadanyPIN[index]= znak; Serial.println(int(ZadanyPIN[index]));lcd.print(znak);break;
          case 'D': preruseno=true;return;
          default : index--;
        }     
    }
    lcd.clear();
    lcd.noCursor();
}


 void Hra1(){
      lcd.clear();
      lcd.home();
      lcd.print("Hra 1 ...");
      delay(3000);
      lcd.clear();
      lcd.home();
      zneskodneno=true;
      bool spatny_pin = false;
      while(zneskodneno){
        server.handleClient();
        zneskodneno=true;
        ZadejPIN();
        for(int i = 0; i < b.delka_pinu;i++){
                    if(b.aktivace[i] != ZadanyPIN[i]){
                      lcd.clear();
                      lcd.home();
                      lcd.print("Spatny pin");
                      delay(3000);
                      lcd.clear();
                      spatny_pin = true; 
                    }
               }
               if(!spatny_pin){
                  lcd.setCursor(0,1);
                  lcd.print("Aktivovano");
                 zneskodneno=false;
                
                  break;
                } 
              
      } 
      bool zapnuto=false;  
      unsigned long cas;
      unsigned long Time; 
      while(!zapnuto){
          server.handleClient();
          lcd.setCursor(0,0);
          lcd.clear();
          lcd.print("Aktivace = A");
          
          if(k.stiskTl() == 'A' || WEBactivation){
             cas=millis(); 
             Time = cas;       
             while(Time-cas <=10000){
                server.handleClient();
                Time = millis();
                lcd.setCursor(0,0);
                lcd.clear();
                lcd.print("Opravdu?");
                if(k.stiskTl() == 'B' || WEBodpal){
                  zapnuto = true;
                  break;
                }
             }
          }
          WEBactivation = false;
          WEBodpal = false;
        }
      attachInterrupt(interruptPin, AlarmInterrupt, RISING );
      preruseno = false;
      spatny_pin = false;
      lcd.setCursor(0,0);
      while(!boom || !zneskodneno){
          server.handleClient();
          preruseno = false;
          if(k.stiskTl() == '#'){       
               ZadejPIN();
               spatny_pin = false;
               for(int i = 0; i < b.delka_pinu;i++){
                    if(b.deaktivace[i] != ZadanyPIN[i]){
                      lcd.clear();
                      lcd.home();
                      lcd.print("Spatny pin");
                      delay(3000);
                      lcd.clear();
                      spatny_pin = true; 
                    }
               }
               if(!spatny_pin){
                  lcd.setCursor(0,1);
                  lcd.print("Zneskodneno");
                 zneskodneno=true;
                 detachInterrupt(interruptPin);
                 return;
                }      
            preruseno = false;
            }     
        }
}
