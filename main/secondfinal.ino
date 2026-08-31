/*
  Spins the motor for 3 seconds whenever the IR beacon sensor detects
  a signal (goes from idle to BEACON DETECTED). Also turns the laser
  (LED_BUILTIN, pin 13) on for 1 second on the same trigger.
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
  Laser: LED_BUILTIN (pin 13) -- no separate pin declaration needed
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
  // We set the pins to output, essentially voltage is outputted and not inputted (default).
  digitalWrite(PIN_PH, LOW);
  analogWrite(PIN_EN, 0);
  // Start up preset before values are changed to keep the system controlled.

  //Laser (onboard LED)
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);   //Start off

  //Set up IR sensor pin
  pinMode(PIN_IR_1, INPUT);
  //Debug output statement
  Serial.println(F("Sensor-triggered motor test starting..."));
}
void loop() {
  bool state = digitalRead(PIN_IR_1);
  //Only trigger on the moment it changes from idle to detected (edge, not level)
  if (state == LOW && lastState == HIGH) {
    Serial.println(F("Sensor 1: BEACON DETECTED -- spinning motor + laser ON"));
    //Sets the pin to high = forward
    digitalWrite(PIN_PH, HIGH);
    analogWrite(PIN_EN, TEST_PWM);
    delay(3000);
    //Sets the power to 0%
    analogWrite(PIN_EN, 0);
    Serial.println(F("-- STOP --"));

    //Laser on/off, same logic as Blink
    digitalWrite(LED_BUILTIN, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
    delay(1000);                      // wait for a second
    digitalWrite(LED_BUILTIN, LOW);   // change state of the LED by setting the pin to the LOW voltage level
  }
  lastState = state;
}
