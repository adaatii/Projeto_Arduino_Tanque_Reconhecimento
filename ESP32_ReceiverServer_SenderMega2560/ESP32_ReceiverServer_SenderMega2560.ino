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

const char *ssid = "";
const char *password = "";

void concatenar(char s1[], char s2[]) {
  int i, j;

  // Olha que laço for maroto!!!
  // Com ele eu vou pegar o tamanho da primeira string...
  // descomente o `printf` para ver o tamnho da primeira string.
  for (i = 1; s1[i] != '\0'; ++i)
    ;
  // Serial.printf("%d \n", i);

  for (j = 1; s2[j] != '\0'; ++j, ++i) {
    s1[i] = s2[j];
  }
  s1[i] = '\0';
}

// rota
String getCommand = "https://tankmuitolouco.droanle.repl.co/api/set.php";
String setLog = "https://tankmuitolouco.droanle.repl.co/api/get.php";

void setup() {
  // Inicia a porta Serial
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Serial.println("Conectando");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    // Serial.print(".");
  }
  // Serial.println(WiFi.localIP());
  // Serial.println(WiFi.macAddress());
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    int comando = 0;
    bool send = false;

    http.begin(getCommand);

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      // Serial.print("HTTP Response code: ");
      // Serial.println(httpResponseCode);
      String var = http.getString();

      comando = var.length();

      if (comando != 15) {
        for (int i = 0; i < 10; i++) {
          if (comando < 10)
            Serial.println(comando);
          else {
            switch (comando) {
            case 10:
              Serial.println('A');
              break;
            case 11:
              Serial.println('B');
              break;
            case 12:
              Serial.println('C');
              break;
            case 13:
              Serial.println('D');
              break;
            case 14:
              Serial.println('E');
              break;
            default:
              Serial.println(0);
            }
          }
          delay(500);
        }
      } else {
        Serial.println(0);
        send = true;
      }
    }
    // else {
    // Serial.print("Erros code: ");
    // Serial.println(httpResponseCode);
    // }
    http.end();

    if (send) {

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

      do {
        bool sent = false;

        http.begin(setLog);

        int httpResponseCode = http.GET();

        if (httpResponseCode > 0) sent = true;

        http.end();
        
      } while (!sent)
      // servidor, v = variavel;
      // char *trilha = "";
    }

    delay(500);
    Serial.println('0');
    delay(10000);
  }
}
