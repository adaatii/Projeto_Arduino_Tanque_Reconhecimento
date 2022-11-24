
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
char comando;

void setup() {
  Serial.begin(115200);    //configura comunicação serial com 115200 bps

}
 
void loop() {
  if(Serial.available()>0){
    char test = Serial.read();
   
     if(test != ""){
       comando = test;
         Serial.println(comando);
     }
    
  }

//delay(1000);
 }
