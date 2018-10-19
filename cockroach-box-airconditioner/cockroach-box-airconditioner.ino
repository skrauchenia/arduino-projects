#define relay_pin 2
#define fan_on_duration 300000
#define fan_off_duration 3600000

unsigned long last_run_time;

void setup() {
  pinMode(relay_pin, OUTPUT);
}

void loop() {
  digitalWrite(relay_pin, 1);
  delay(fan_on_duration);
  digitalWrite(relay_pin, 0);
  delay(fan_off_duration);
}
