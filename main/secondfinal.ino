/*
  Motor spins FAST continuously from startup. Whenever the IR beacon
  sensor detects a signal (goes from idle to BEACON DETECTED), the
  motor slows down, the laser (LED_BUILTIN, pin 13) fires for 1
  second, then the motor speeds back up to fast.
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
const int FAST_PWM = 0;   //Startup/default speed -- max, for a clear contrast
const int SLOW_PWM = 30;     //Speed while sensing/firing -- fully stopped
//IR sensor pin
const uint8_t PIN_IR_1 = 6;
bool lastState = HIGH;   //Demodulating receivers idle HIGH
void setup() {
  Serial.begin(115200); // Sends a ping between the Arduino and computer at 115200 bits per second
  //Set the pins to Output mode
  pinMode(PIN_PH, OUTPUT);
  pinMode(PIN_EN, OUTPUT);

  //Laser (onboard LED)
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);   //Start off

  //Set up IR sensor pin
  pinMode(PIN_IR_1, INPUT);

  //Start the motor spinning fast on startup
  digitalWrite(PIN_PH, HIGH);
  analogWrite(PIN_EN, FAST_PWM);
  Serial.println(F("Motor spinning FAST on startup..."));

  //Debug output statement
  Serial.println(F("Sensor-triggered laser test starting..."));
}
void loop() {
  bool state = digitalRead(PIN_IR_1);
  //Only trigger on the moment it changes from idle to detected (edge, not level)
  if (state == LOW && lastState == HIGH) {
    Serial.println(F("Sensor 1: BEACON DETECTED -- SLOWING motor + laser ON"));

    //Slow the motor down (fully stop) to let the laser fire
    analogWrite(PIN_EN, SLOW_PWM);

    //Laser on/off, same logic as Blink
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);  // change state of the LED by setting the pin to the HIGH voltage level
    delay(1000);                      // wait for a second
       // change state of the LED by setting the pin to the LOW voltage level

    //Speed back up to fast
    analogWrite(PIN_EN, FAST_PWM);
    Serial.println(F("-- SPEEDING BACK UP TO FAST --"));
  }
  lastState = state;
}
