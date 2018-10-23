float open_door_distance = 84.0;

#define ECHO 2
#define TRIG 3
#define sensVCC 4
#define relay_pin 5

#include <NewPing.h>
NewPing sonar(TRIG, ECHO, 400);

float dist_3[3] = {0.0, 0.0, 0.0};
float middle, dist, dist_filtered;
float k;
byte i, delta;
unsigned long dispIsrTimer, sensTimer;

void setup() {
  Serial.begin(9600);

  pinMode(sensVCC, OUTPUT);
  pinMode(relay_pin, OUTPUT);

  digitalWrite(sensVCC, 1);
}

void printDistance() {
    Serial.print(dist_3[0]);
    Serial.print(", ");
    Serial.print(dist_3[1]);
    Serial.print(", ");
    Serial.print(dist_3[2]);
    Serial.print(": ");
    Serial.println(dist_filtered);
}

void loop() {
  if (millis() - sensTimer > 500) {
    int dist_i = (float)sonar.ping() / 57.5;

    if (dist_i > 0.0) {
      dist_3[i] = dist_i;                 
      dist = middle_of_3(dist_3[0], dist_3[1], dist_3[2]);
  
      delta = abs(dist_filtered - dist);                      
      if (delta > 1) k = 0.7;                                 
      else k = 0.1;                                           
  
      dist_filtered = dist * k + dist_filtered * (1 - k);     
//      printDistance();
      sensTimer = millis();                                   
      
      if (i > 1) i = 0;
      else i++;
    }
  }

  if (micros() - dispIsrTimer > 1500) {       
    if (dist_filtered >= open_door_distance) {
      digitalWrite(relay_pin, 1);
    } else {
      digitalWrite(relay_pin, 0);
    }
    dispIsrTimer = micros();                 
  }
}

float middle_of_3(float a, float b, float c) {
  if ((a <= b) && (a <= c)) {
    middle = (b <= c) ? b : c;
  }
  else {
    if ((b <= a) && (b <= c)) {
      middle = (a <= c) ? a : c;
    }
    else {
      middle = (a <= b) ? a : b;
    }
  }
  return middle;
}
