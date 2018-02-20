void allah_akbar(){
  boom = true;
  lcd.clear();
  lcd.print("Boom");
}
void pocitej(){
   h = (b.casDoVybuchu/3600);
   Serial.println(h);
   m = (b.casDoVybuchu-h*3600)/60;
   Serial.println(m);
   s = b.casDoVybuchu-(m*60+h*3600);
   Serial.println(s);
   if(b.casDoVybuchu == 0){
     allah_akbar();
   }
   else{
    if(!preruseno){
          lcd.clear();
          lcd.print(h);
          lcd.print(":");
          lcd.print(m);
          lcd.print(":");
          lcd.print(s);
      }

   }
   b.casDoVybuchu--;
}
