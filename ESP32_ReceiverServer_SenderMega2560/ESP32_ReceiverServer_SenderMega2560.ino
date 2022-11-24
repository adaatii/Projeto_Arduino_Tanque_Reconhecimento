#include <HTTPClient.h>
#include <WiFi.h>
#include <stdio.h>
#include <string.h>

const int trigPin = 5;
const int echoPin = 18;
// define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;

const char * ssid = "VIVOFIBRA-391C";
const char * password = "33d76e391c";

void concatenar(char s1[], char s2[]) {
  int i, j;

  // Olha que laço for maroto!!!
  // Com ele eu vou pegar o tamanho da primeira string...
  // descomente o `printf` para ver o tamnho da primeira string.
  for (i = 1; s1[i] != '\0'; ++i);
  //Serial.printf("%d \n", i);

  for (j = 1; s2[j] != '\0'; ++j, ++i) {
    s1[i] = s2[j];
  }
  s1[i] = '\0';
}

// rota
String arquivoPHP = "https://tankmuitolouco.droanle.repl.co/api/set.php";
void setup() {
  // Inicia a porta Serial
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Serial.println("Conectando");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  // Serial.println(WiFi.localIP());
  // Serial.println(WiFi.macAddress());
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    int dado = 35; // coletar o dado na variavel intermediaria
    String url = arquivoPHP; //? = construindo url trasmissão via GET para o
    // servidor, v = variavel;
    // char *trilha = "";
    int comando = 0;

    http.begin(url);

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      // Serial.print("HTTP Response code: ");
      // Serial.println(httpResponseCode);
      String var = http.getString();
      
      comando = var.length();
      Serial.println(comando);
    
    }
    // else {
    // Serial.print("Erros code: ");
    // Serial.println(httpResponseCode);
    // }
    http.end();

    // strcmp(trilha, "");

    
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculate the distance
    distanceCm = duration * SOUND_SPEED / 2;

    // Prints the distance in the Serial Monitor
    // Serial.print("Distance (cm): ");
    // Serial.println(distanceCm);

    delay(500);
  }
}
