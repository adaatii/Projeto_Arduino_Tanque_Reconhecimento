#include "Servo.h"

// Criar um Objeto Servo
Servo servo1;
   
const int motorA1  = 11;   
const int motorA2  = 10;   
const int motorB1  = 5;   
const int motorB2  = 4;    
 
// Variáveis Úteis
int i = 0;
int j = 0;
int state_rec;
int vSpeed = 200;   // Define velocidade padrão 0 &lt; x &lt; 255.
char state;
char servo;
char servo2;
 
void setup() {
  // Inicializa as portas como entrada e saída.

  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  servo1.attach(7); 
  
  // Inicializa a comunicação serial em 9600 bits.
  Serial.begin(115200);
}
 
void loop() {
 
  if (Serial.available() > 0) {
    state_rec = Serial.read();
    state = state_rec;
    servo = state_rec;  
    Serial.println(state_rec); 
    
    //   Serial.println(vSpeed);
  }

  bool spin = false;
 
  // Altera a velocidade de acordo com valores especificados.
  if (servo == '1') {
    servo2 = 0;
    spin = true;
  } else if (servo == '2') {
    servo2 = 10;
    spin = true;
  } else if (servo == '3') {
    servo2 = 21;
    spin = true;
  } else if (servo == '4') {
    servo2 = 32;
    spin = true;
  } else if (servo == '5') {
    servo2 = 43;
    spin = true;
  } else if (servo == '6') {
    servo2 = 54;
    spin = true;
  } else if (servo == '7') {
    servo2 = 65;
    spin = true;
  } else if (servo == '8') {
    servo2 = 75;
    spin = true;
  } else if (servo == '9') {
    servo2 = 86;
    spin = true;
  } else if (servo == 'A') {
    servo2 = 97;
    spin = true;
  } 
  //state=map(state, 0, 1023, 0, 180);
  // Repassa o angulo ao ServoWrite

  if(spin){
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 0);  
    
    servo1.write(0);
    servo1.write(servo2); 
    // Delay de 15ms para o Servo alcançar a posição
    delay(15);
  } 
 
  if (state == 'B') {  // Se o estado recebido for igual a 'F', o carro se movimenta para frente.
    analogWrite(motorA1, vSpeed);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, vSpeed);
    analogWrite(motorB2, 0);
  }
 
    else if (state == 'D') { // Se o estado recebido for igual a 'I', o carro se movimenta para Esquerda.
    analogWrite(motorA1, vSpeed);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vSpeed); 
   
  }
 
    else if (state == 'E') {   // Se o estado recebido for igual a 'G', o carro se movimenta para Direita. 
    analogWrite(motorA1, 0);
    analogWrite(motorA2, vSpeed);
    analogWrite(motorB1, 250);
    analogWrite(motorB2, 0);
  }
 
  else if (state == 'C') { // Se o estado recebido for igual a 'B', o carro se movimenta para trás.
    analogWrite(motorA1, 0);
    analogWrite(motorA2, vSpeed);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vSpeed);
  }

  else if (state == '0') {   // Se o estado recebido for igual a 'S', o carro permanece parado.
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 0);   
  }
 
}
