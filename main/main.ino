/*
  MOTOR SPIN TEST - FIT0186 gearmotor via DRV8874 driver
  --------------------------------------------------------
  Spins the motor forward, then reverse, and prints encoder counts +
  measured RPM to Serial so you can confirm direction and rough speed
  match expectations.

  WIRING:
    DRV8874:
      PH     -> D8   (direction)
      EN     -> D9   (PWM speed)
      PMODE  -> GND  (selects PH/EN control mode)
      nSLEEP -> 5V   (driver always enabled)
      VREF   -> resistor divider (sets current limit - don't leave floating)
      OUT1/OUT2 -> motor terminals
      VM     -> battery pack V+
      GND    -> common ground

    Encoder:
      Channel A -> D2 (INT0)
      Channel B -> D3 (INT1)

  Open Serial Monitor at 115200 baud to watch it run.
*/

const uint8_t PIN_ENC_A = 2;
const uint8_t PIN_ENC_B = 3;
const uint8_t PIN_PH    = 8;
const uint8_t PIN_EN    = 9;   // PWM

// Verify this empirically (see note at bottom) before trusting RPM numbers.
const long COUNTS_PER_REV = 2800;

volatile long encoderCount = 0;
static const int8_t QUAD_TABLE[16] = {
   0, -1,  1,  0,
   1,  0,  0, -1,
  -1,  0,  0,  1,
   0,  1, -1,  0
};
volatile uint8_t lastEncState = 0;

unsigned long lastReportTime = 0;
long lastReportCount = 0;
const unsigned long REPORT_INTERVAL_MS = 500;

void setup() {
    Serial.begin(115200);

    pinMode(PIN_ENC_A, INPUT_PULLUP);
    pinMode(PIN_ENC_B, INPUT_PULLUP);
    pinMode(PIN_PH, OUTPUT);
    pinMode(PIN_EN, OUTPUT);
  
    digitalWrite(PIN_PH, LOW);
    analogWrite(PIN_EN, 0);
  
    lastEncState = (digitalRead(PIN_ENC_A) << 1) | digitalRead(PIN_ENC_B);
    attachInterrupt(digitalPinToInterrupt(PIN_ENC_A), encoderISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_ENC_B), encoderISR, CHANGE);
  
    Serial.println(F("Motor spin test starting..."));
}

// Loop to help calibrate the motor.
void loop(){
    static unsigned long lastPrint = 0;
        if (millis() - lastPrint >= 100) {
          lastPrint = millis();
          Serial.println(encoderCount);
        }
    }
    
void runFor(unsigned long durationMs, bool forward, int pwm) {
    setMotor(forward, pwm);
    unsigned long start = millis();
    lastReportTime = start;
    lastReportCount = encoderCount;
  
    while (millis() - start < durationMs) {
      reportSpeed();
    }
  }
  
  void reportSpeed() {
    unsigned long now = millis();
    if (now - lastReportTime >= REPORT_INTERVAL_MS) {
      long count = encoderCount;
      long deltaCounts = count - lastReportCount;
      float deltaSec = (now - lastReportTime) / 1000.0;
      float rpm = (deltaCounts / (float)COUNTS_PER_REV) / (deltaSec / 60.0);
  
      Serial.print(F("count="));
      Serial.print(count);
      Serial.print(F("  rpm="));
      Serial.println(rpm);
  
      lastReportTime = now;
      lastReportCount = count;
    }
  }
  
  void setMotor(bool forward, int pwm) {
    digitalWrite(PIN_PH, forward ? HIGH : LOW);
    analogWrite(PIN_EN, pwm);
  }
  
  void encoderISR() {
    uint8_t a = digitalRead(PIN_ENC_A);
    uint8_t b = digitalRead(PIN_ENC_B);
    uint8_t state4 = (a << 1) | b;
    uint8_t idx = (lastEncState << 2) | state4;
    encoderCount += QUAD_TABLE[idx & 0x0F];
    lastEncState = state4;
  }
  
  /*
    TO VERIFY COUNTS_PER_REV:
    Print encoderCount, rotate the flywheel by hand exactly one full
    turn, then print encoderCount again. The difference is your true
    counts/rev - update the constant above to match.
  */

  
  /*
    will add this after calibrating.

    // Forward for 4 seconds
    Serial.println(F("-- FORWARD --"));
    runFor(4000, true, 100);

    // Stop for 1 second
    setMotor(true, 0);
    delay(1000);

    // Reverse for 4 seconds
    Serial.println(F("-- REVERSE --"));
    runFor(4000, false, 100);

    // Stop for 1 second
    setMotor(true, 0);
    delay(1000);
  */