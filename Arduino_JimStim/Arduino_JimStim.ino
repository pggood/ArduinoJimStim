// analogue pot on anaglog pin0
// this represents routput of 1,000 to 8,000 RPM
#include "wheels_default.h"
#define ledPin 4
volatile uint8_t degree = 0;
uint8_t WheelType=0;
uint8_t WheelTypeSet=0;
uint16_t WheelTypeStart=0;
uint16_t WheelTypeEnd=0;
uint16_t WheelTypeNow=0;
uint8_t WheelValue=0;
uint8_t WheelValueTime=2;
uint8_t WheelValueTimer=0;
uint16_t WheelValueTotal=0;

void setup()
{
  Serial.begin(115200);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  if (digitalRead(2))WheelType=1;
  if (digitalRead(3))WheelType=WheelType+2;
  if (digitalRead(4))WheelType=WheelType+4;
  if (digitalRead(5))WheelType=WheelType+8;
  if (digitalRead(6))WheelType=WheelType+16;
  if (digitalRead(7))WheelType=WheelType+32;
  //WheelTypeSet=0; Manually set wheel type to overide dip switches 
  //digitalWrite(ledPin, LOW);
// initialize timer1
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 2600;            // compare match register 16MHz/256/2Hz
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS10) | (0 << CS11) | (0 << CS12);    // 1 prescaler
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
  for (int i = 0; i < sizeof(WHEEL); i=i+2) {
    //Serial.print(i, DEC);
    //Serial.print(" = ");
    WheelValue = pgm_read_byte_near(WHEEL + i);
    if (WheelValue==255){
      if (WheelTypeSet++<=WheelType){
        WheelTypeStart=WheelTypeEnd+2;
        WheelTypeEnd=i;
      }
    }
    WheelValueTime = pgm_read_byte_near(WHEEL + i+1);
  /*  Serial.print(WheelValue,DEC);
    Serial.print(" , ");
    Serial.print(WheelValueTime,DEC);
    Serial.print(" , ");
    Serial.print(WheelType,DEC);
    Serial.print(" , ");
    Serial.print(WheelTypeStart,DEC);
    Serial.print(" , ");
    Serial.println(WheelTypeEnd,DEC);
    */
  }
  Serial.print(WheelType,DEC);
  Serial.print(" , ");
  Serial.print(WheelTypeStart,DEC);
  Serial.print(" , ");
  Serial.println(WheelTypeEnd,DEC);
  for (int i = WheelTypeStart; i < WheelTypeEnd; i=i+2) {
    WheelValue = pgm_read_byte_near(WHEEL + i);
    WheelValueTime = pgm_read_byte_near(WHEEL + i+1);
    WheelValueTotal = WheelValueTotal+WheelValueTime;
    Serial.print(i/2, DEC);
    Serial.print(" = ");
    Serial.print(WheelValue,DEC);
    Serial.print(" , ");
    Serial.println(WheelValueTime,DEC);
  }
  Serial.println(WheelValueTotal,DEC);
  WheelTypeNow=WheelTypeStart;
}

ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
 if (WheelValueTimer==WheelValueTime){
  //digitalWrite(ledPin, HIGH);
  WheelValueTimer=0;     
  WheelValue = pgm_read_byte_near(WHEEL + WheelTypeNow); 
  WheelValueTime = pgm_read_byte_near(WHEEL + WheelTypeNow+1);
  PORTB=WheelValue;
  WheelTypeNow=WheelTypeNow+2; 
  if (WheelTypeNow>=WheelTypeEnd){
    //digitalWrite(ledPin, HIGH);
    WheelTypeNow=WheelTypeStart;     
  }   
 }
 WheelValueTimer++;
 //digitalWrite(ledPin, LOW);
}

void loop()
{
  // your program here...
  //OCR1A = map(analogRead(A0), 0, 1023, 1667, 13333);
  if (WheelValueTotal==360){
    OCR1A = map(analogRead(A0), 0, 1023, 325, 2600);
  }else{
    OCR1A = map(analogRead(A0), 0, 1023, 163, 1300);
  }
  delay(250);
}
