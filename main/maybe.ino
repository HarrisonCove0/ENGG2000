/*
  Spins the motor for 3 seconds whenever an IR beacon sensor detects
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

  Sensors:
    Sensor 1 OUT -> D6
    Sensor 2 OUT -> D5
    VCC -> 5V, GND -> common ground
*/

//Pin declarations
//Direction
const uint8_t PIN_PH = 8;
//PWM speed
const uint8_t PIN_EN = 9;
const int TEST_PWM = 150;   //Speed variable

//IR sensor pins
const uint8_t PIN_IR_1 = 6;
const uint8_t PIN_IR_2 = 5;
const uint8_t NUM_SENSORS = 2;
const uint8_t sensorPins[NUM_SENSORS] = { PIN_IR_1, PIN_IR_2 };
bool lastState[NUM_SENSORS];

void setup() {
  Serial.begin(115200); // Sends a ping between the Arduino and computer at 115200 bits per second
  //Set the pins to Output mode
  pinMode(PIN_PH, OUTPUT);
  pinMode(PIN_EN, OUTPUT);
  // We set the pins to output, essentially voltage is outputted and not inputted (default).
  digitalWrite(PIN_PH, LOW);
  analogWrite(PIN_EN, 0);
  // Start up preset before values are changed to keep the system controlled.

  //Set up IR sensor pins
  for (uint8_t i = 0; i < NUM_SENSORS; i++) {
    pinMode(sensorPins[i], INPUT);
    lastState[i] = HIGH;   //Demodulating receivers idle HIGH
  }

  //Debug output statement
  Serial.println(F("Sensor-triggered motor test starting..."));
}

void loop() {
  for (uint8_t i = 0; i < NUM_SENSORS; i++) {
    bool state = digitalRead(sensorPins[i]);

    //Only trigger on the moment it changes from idle to detected (edge, not level)
    if (state == LOW && lastState[i] == HIGH) {
      Serial.print(F("Sensor "));
      Serial.print(i + 1);
      Serial.println(F(": BEACON DETECTED -- spinning motor"));

      //Sets the pin to high = forward
      digitalWrite(PIN_PH, HIGH);
      analogWrite(PIN_EN, TEST_PWM);
      delay(3000);

      //Sets the power to 0%
      analogWrite(PIN_EN, 0);
      Serial.println(F("-- STOP --"));
    }

    lastState[i] = state;
  }
}
