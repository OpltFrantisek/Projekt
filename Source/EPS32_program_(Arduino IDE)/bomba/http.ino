void handleActivation(){
    
    if(!zneskodneno){
        server.send(200,"text/plain","6");
        WEBactivation = true;
      }
    else
      server.send(200,"text/plain","0");
  }
void handleOK(){
  if(WEBactivation){
    server.send(200,"text/plain","9");
    WEBodpal = true;
  }
  else{
    server.send(200,"text/plain","0");
    }
    
}
void handleRestart(){
  restart = true;
  server.send(200,"text/plain","OK");
}
void handleStatus(){
   char msg[100];
   char m;
   if(rezim == 1){
      m = '1';
    }
    else{
      if(rezim == 2){
          m = '2';
        }
        else{
          m = '3';
          }
      }
   sprintf(msg, " %c | %ld | %ld | %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c | %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",m,b.casDoVybuchu,b.casHry,
   b.aktivace[0],b.aktivace[1],b.aktivace[2], b.aktivace[3],b.aktivace[4],b.aktivace[5], b.aktivace[6],b.aktivace[7],b.aktivace[8], b.aktivace[9],b.aktivace[10],b.aktivace[11],b.aktivace[12],b.aktivace[13],b.aktivace[14],b.aktivace[15],
   b.deaktivace[0],b.deaktivace[1],b.deaktivace[2],b.deaktivace[4],b.deaktivace[4],b.deaktivace[5],b.deaktivace[6],b.deaktivace[7],b.deaktivace[8],b.deaktivace[9],b.deaktivace[10],b.deaktivace[11],b.deaktivace[12],b.deaktivace[13],b.deaktivace[14],b.deaktivace[15]); 
   server.send(200,"text/plain",msg);  
}
void handleTime(){
   char msg[50];
  sprintf(msg,"%ld",b.casDoVybuchu); 
  server.send(200,"text/plain",msg);
  }
void handleNotFound(){
  
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  
}
