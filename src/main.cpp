#include <Arduino.h>
#include <DHT11.h>
#include <ezButton.h>

const int TOGGLE_BUTTON_PIN = 2;
const int DHT11_PIN = 4;
const int PENTIOMETER_PIN = A0;
const int RED_LED_PIN = 5;
const int GREEN_LED_PIN = 6;
const int BLUE_LED_PIN = 7;

const int MAX_DEVIATION = 3;

DHT11 dht11(DHT11_PIN);
ezButton toggleButton(TOGGLE_BUTTON_PIN);

int buttonState = 0;

/**
 * @brief Checks if the current temperature is within the acceptable range of the desired temperature.
 *
 * This function calculates the absolute difference between the current temperature and the desired temperature,
 * and checks if it is within the specified maximum deviation.
 *
 * @param current_temperature The current temperature to check.
 * @param desired_temperature The desired temperature to compare against.
 * @param max_deviation The maximum allowable deviation from the desired temperature.
 * @return true if the current temperature is within the acceptable range, false otherwise.
 */
bool isTemperatureWithinRange(int current_temperature, int desired_temperature, int max_deviation) {
  return abs(current_temperature - desired_temperature) <= max_deviation;
}


/**
 * @brief Toggles the state of the RGB LED.
 * 
 * This function sets the state of the RGB LED by writing the specified values
 * to the respective LED pins.
 * 
 * @param red The state to set for the red LED (HIGH or LOW).
 * @param green The state to set for the green LED (HIGH or LOW).
 * @param blue The state to set for the blue LED (HIGH or LOW).
 */
void toggleLed(int red, int green, int blue) {
  digitalWrite(RED_LED_PIN, red);
  digitalWrite(GREEN_LED_PIN, green);
  digitalWrite(BLUE_LED_PIN, blue);
}

void setup() {
  Serial.begin(9600);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  toggleButton.setDebounceTime(100);
  toggleLed(LOW, LOW, LOW);
}

void loop() {
  toggleButton.loop();

  if (toggleButton.isPressed()) {
    buttonState = !buttonState;
    Serial.println("Button pressed!");
  }

  if (buttonState) {
    toggleLed(LOW, LOW, LOW);
    return;
  }

  // Temperature read from the DHT11 sensor
  int current_temperature = dht11.readTemperature();
  Serial.println("Current temperature: " + String(current_temperature) + "°C");
  
  // Value read from the potentiometer
  int pot_value = analogRead(PENTIOMETER_PIN);
  
  // A value between 0 and 50 for the desired temperature
  int desired_temperature = map(pot_value, 0, 1023, 0, 50);
  Serial.println("Desired temperature: " + String(desired_temperature) + "°C");

  if (isTemperatureWithinRange(current_temperature, desired_temperature, MAX_DEVIATION)) {
    toggleLed(LOW, HIGH, LOW);
  } else if (current_temperature < desired_temperature) {
    toggleLed(HIGH, LOW, LOW);
  } else {
    toggleLed(LOW, LOW, HIGH);
  }

}

/* const int LED = 6;
const int BTN = 2;
const uint8_t POTENTIOMETER = A0;

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
} */
