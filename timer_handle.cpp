#include <FlexiTimer2.h>
#include "pin_init.h"
const int LED = LED_BUILTIN;

void TimerHandle()
{
    static boolean output=HIGH;
    digitalWrite(LED,output);
    output=!output;
//    int sensorValue =  analogRead(A0);
//    Serial.println(sensorValue); 
}
//设置定时器基准为125ms
void InitTimer(){
    pinMode(LED,OUTPUT);
    FlexiTimer2::set(125,1.0/1000,TimerHandle);
    FlexiTimer2::start();
}

