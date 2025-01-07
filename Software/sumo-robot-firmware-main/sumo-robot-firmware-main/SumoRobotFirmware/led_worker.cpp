#include "led_worker.h"

void turnLedOn(){
  digitalWrite(LED_BUILTIN, HIGH);
}

void turnLedOff(){
  digitalWrite(LED_BUILTIN, LOW);
}

int getSum(int a, int b){
  return a+b;
}
