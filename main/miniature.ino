/*
  Spins the motor forward for 3s, stops, reverses for 3s, stops. Repeats.

  WIRING:
    PH     -> D8   (direction) // Yellow
    EN     -> D9   (PWM speed) // Brown
    PMODE  -> GND
    nSLEEP -> 5V // Green
    VREF   -> resistor divider (don't leave floating)
    OUT1/OUT2 -> motor terminals
    VM     -> battery pack V+
    GND    -> common ground
*/

//Pin declarations
//Direction
const uint8_t PIN_PH = 8;
//PWM speed
const uint8_t PIN_EN = 9;
const int TEST_PWM = 150;   //Speed variable

void setup() {
  Serial.begin(115200); // Sends a ping between the Arduino and computer at 115200 bits per second
  //Set the pins to Output mode
  pinMode(PIN_PH, OUTPUT);
  pinMode(PIN_EN, OUTPUT);
  // We set the pins to output, essentially voltage is outputted and not inputted (default).
  digitalWrite(PIN_PH, LOW);
  analogWrite(PIN_EN, 0);
  // Start up preset before values are changed to keep the system controlled.

  // Debug output statement
  Serial.println(F("Simple motor test starting..."));
}

void loop() {
  //Debug output statement
  Serial.println(F("-- FORWARD --"));
  //Sets the pin to high = forward
  digitalWrite(PIN_PH, HIGH);
  //Sets the speed to 
  analogWrite(PIN_EN, TEST_PWM);
  delay(3000);

  //Debug output statement
  Serial.println(F("-- STOP --"));
  analogWrite(PIN_EN, 0);
  delay(1000);

  //Debug output statement
  Serial.println(F("-- REVERSE --"));
  digitalWrite(PIN_PH, LOW);
  analogWrite(PIN_EN, TEST_PWM);
  delay(3000);

  //Debug output statement
  Serial.println(F("-- STOP --"));
  //Sets the power to 0%
  analogWrite(PIN_EN, 0);
  delay(1000);
}
