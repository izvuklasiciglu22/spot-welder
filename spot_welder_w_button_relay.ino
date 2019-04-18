#include <EnableInterrupt.h>
#include <Rotary.h>
#include <TM1637Display.h>


TM1637Display display(12,7);
int bpr=0;

Rotary r = Rotary(2, 3);
 volatile int counter;

void setup() {
  Serial.begin(9600);

  /* Original interrupt setup:
  PCICR |= (1 << PCIE2);
  PCMSK2 |= (1 << PCINT18) | (1 << PCINT19);
  sei();
  */
  display.setBrightness(6);
 counter=50;
  enableInterrupt(2, interruptFunction, CHANGE);
  enableInterrupt(3, interruptFunction, CHANGE);
  pinMode(10,INPUT);
  pinMode(13,OUTPUT);
}

void loop() {
display.setBrightness(0x0f);
display.showNumberDec(counter,false);
if (digitalRead(10)==HIGH) {delay(50);
          if (digitalRead(10)==LOW) {pinMode(13,HIGH);delay(counter);pinMode(13,LOW);} 
          else {delay(100);}}

}

void interruptFunction() {

  

  unsigned char result = r.process();
  if (result == DIR_NONE) {
    // do nothing
  }
  else if (result == DIR_CW) {
    Serial.println("ClockWise");
    counter=counter+5;
    Serial.println(counter);
  }
  else if (result == DIR_CCW) {
    Serial.println("CounterClockWise");
    counter=counter-5;
    Serial.println(counter);
  }
}
