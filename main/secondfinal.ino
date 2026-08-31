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

bool locked = false; //True once we've found and stopped on a beacon.

void setup() {
  Serial.begin(115200); // Sends a ping between the Arduino and computer at 115200 bits per second
  //Set the pins to Output mode
  pinMode(PIN_PH, OUTPUT);
  pinMode(PIN_EN, OUTPUT);
  // We set the pins to output, essentially voltage is outputted and not inputted (default).
  digitalWrite(PIN_PH, LOW);
  analogWrite(PIN_EN, 0);
  // Start up preset before values are changed to keep the system controlled.

  //Set up IR sensor pin
  pinMode(PIN_IR_1, INPUT);

  //Start sweeping immediately in setup(), since loop just needs to loop for the stop conditions.
  Serial.println(F("Searching for beacon...")); 
  digitalWrite(PIN_PH, HIGH); //Forward/search direction
  analogWrite(PIN_EN, TEST_PWM);
}

void loop() {
  if (locked) return; //Don't rotate since we're pointing at the source

  bool state = digitalRead(PIN_IR_1);

  //Only trigger on the moment it changes from idle to detected (edge, not level)
  if (state == LOW) {
    analogWrite(PIN_EN, 0); //Stop rotation since we're pointing at the source
    locked = true;
    Serial.println(F("Sensor 1: BEACON DETECTED -- spinning motor"));
  }
}
