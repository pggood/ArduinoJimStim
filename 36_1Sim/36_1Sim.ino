// analogue pot on anaglog pin0
// this represents routput of 1,000 to 8,000 RPM
#define ledPin 10
volatile int toothCount = 0;
volatile int missingTick = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
// initialize timer1
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 13333;            // compare match register 16MHz/256/2Hz
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS10) | (0 << CS11) | (0 << CS12);    // 1 prescaler
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
}

ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  if (toothCount <= 69) // 0 thru 69 is 70 toggles or 35 pulses per rev.
  {
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1);   // toggle LED pin
    toothCount++;
  }
  else {
    missingTick++;  // 2 toggles - 1 missing pulse per revolution
    if (missingTick == 2) {
      toothCount = 0;
      missingTick = 0;
    }
  }
}

void loop()
{
  // your program here...
  OCR1A = map(analogRead(A0), 0, 1023, 1667, 13333);
  delay(250);
}
