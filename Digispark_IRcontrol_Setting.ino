#include "DigiKeyboard.h"

#define IR_PIN 2
#define DATA_SIZE 20
#define START_BIT 4000
int i, s, data[DATA_SIZE];

void setup() {
  pinMode(IR_PIN, INPUT);
}
void loop() {
  DigiKeyboard.update();
  DigiKeyboard.sendKeyStroke(0);

  
  s = pulseIn(IR_PIN, HIGH);
  if(s > START_BIT)
  {
    for(i = 0; i < DATA_SIZE; i++)
      data[i] = pulseIn(IR_PIN, HIGH);
    
    int result = 0;
    for(i = 12; i < DATA_SIZE; i++)
      if(data[i] > 1000)
        result |= (1 << (DATA_SIZE - 1 - i));

          DigiKeyboard.print(result,'\n'); //For Debug
          DigiKeyboard.delay(100);
  }
   delay(100);
}
