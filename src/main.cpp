#include <Arduino.h>

#define LED 6
#define BTN 2
#define POTENTIOMETER A0

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
  Serial.begin(9600);

  digitalWrite(LED, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool btn_state = digitalRead(BTN);

  if (btn_state == LOW)
  {
    digitalWrite(LED, LOW);
    Serial.println("Button pressed!");
  }
  else
  {
    digitalWrite(LED, HIGH);
  }

  int pot_value = analogRead(POTENTIOMETER);
  float voltage = pot_value * (5.0 / 1023.0);
  Serial.println("Potentiometer value: " + String(voltage));
}
