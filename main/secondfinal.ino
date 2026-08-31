/*
  Spins the motor for 3 seconds whenever the IR beacon sensor detects
  a signal (goes from idle to BEACON DETECTED).

  WIRING:
    PH     -> D8   (direction) // Yellow
    EN     -> D9   (PWM speed) // Brown
    PMODE  -> GND
    nSLEEP -> 5V // Green
    VREF   -> resistor divider (don't leave floating)
    OUT1/OUT2 -> motor terminals
    VM     -> battery pack V+
    GND    -> common ground

  Sensor:
    Sensor 1 OUT -> D6
    VCC -> 5V, GND -> common ground
*/

//Pin declarations
//Direction
const uint8_t PIN_PH = 8;
//PWM speed
const uint8_t PIN_EN = 9;
const int TEST_PWM = 150;   //Speed variable

//IR sensor pin
const uint8_t PIN_IR_1 = 6;
bool lastState = HIGH;   //Demodulating receivers idle HIGH

void setup() {
  Serial.begin(115200); // Sends a ping between the Arduino and computer at 115200 bits per second
  //Set the pins to Output mode
  pinMode(PIN_PH, OUTPUT);
  pinMode(PIN_EN, OUTPUT);
  pinMode(PIN_IR_1, INPUT);

  //Debug output statement
  Serial.println(F("Sensor-triggered motor test starting..."));

   //Start moving right away -- no longer waiting on the sensor to begin
   digitalWrite(PIN_PH, HIGH);   //Forward/search direction
   analogWrite(PIN_EN, TEST_PWM);
}

void loop() {
  bool state = digitalRead(PIN_IR_1);

  //Only trigger on the moment it changes from idle to detected (edge, not level)
  if (state == LOW && lastState == HIGH) {
    Serial.println(F("Sensor 1: BEACON DETECTED -- spinning motor"));
    analogWrite(PIN_EN, 0);
  }

  lastState = state;
}
