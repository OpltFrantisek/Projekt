#include "Klavesnice.h"
#include <stddef.h>
#include <Arduino.h>
void Key::Init(int r[],int  c[],int rl,int sl){
    row = new int[rl];
    col = new int[sl];
    for(int i; i < rl;i++){
        pinMode(r[i],OUTPUT);
        digitalWrite(r[i],1);
        row[i] = r[i];
    }

    for(int i; i < sl;i++){
        pinMode(c[i],INPUT_PULLUP);
        col[i] = c[i];
    }
}
char Key::stiskTl(){
    for(int i = 0; i < 4; i++){
        digitalWrite(row[i],0);
        for(int j = 0; j < 4; j++){
            if(digitalRead(col[j]) == 0){
                delay(500);
                digitalWrite(row[i],1);
                return keyMap[i][j];
            }
        }
        digitalWrite(row[i],1);
        delay(1);
    }
    return NULL;
}
