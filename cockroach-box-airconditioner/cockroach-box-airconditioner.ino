#include "timer-api.h"



void setup() {
  // частота=1Гц, период=1с
  timer_init_ISR_1Hz(TIMER_DEFAULT);

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
}

void loop() {
  
}

void timer_handle_interrupts(int timer) {
  static int fanOnSeconds = 60;
  static int fanOffSeconds = 1200;
  static boolean fanTurnedOn = true;

  if (fanTurnedOn) {
    if (fanOnSeconds == 0) {
      digitalWrite(2, LOW);
      fanTurnedOn = false;
      fanOnSeconds = 60;
    } else {
      fanOnSeconds--;
    }
  } else {
    if (fanOffSeconds == 0) {
      digitalWrite(2, HIGH);
      fanTurnedOn = true;
      fanOffSeconds = 1200;
    } else {
      fanOffSeconds--;
    }
  }
}
