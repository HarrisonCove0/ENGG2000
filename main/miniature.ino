/*
  Spins the motor forward for 3s, stops, reverses for 3s, stops. Repeats.

  WIRING:
    PH     -> D8   (direction)
    EN     -> D9   (PWM speed)
    PMODE  -> GND
    nSLEEP -> 5V
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
  Serial.begin(115200);
  //Set the pins to Output mode
  pinMode(PIN_PH, OUTPUT);
  pinMode(PIN_EN, OUTPUT);

  //
  digitalWrite(PIN_PH, LOW);
  analogWrite(PIN_EN, 0);

  //Debug output statement
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
