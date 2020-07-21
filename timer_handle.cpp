#include <FlexiTimer2.h>
#include "pin_init.h"
#include "waves.h"
const int LED = LED_BUILTIN;

void UpdateLED(){
  static boolean output=HIGH;
    digitalWrite(LED,output);  
    static int counter=0;
    counter++;
    if(counter>25){
      counter=0;
      output=!output;  
    }
}

void TimerHandle()
{
    UpdateLED();   
//    int sensorValue =  analogRead(A0);
//    Serial.println(sensorValue); 
    loopwave() ;//更新波形数据
}
//设置定时器基准为20ms
void InitTimer(){
    pinMode(LED,OUTPUT);
    FlexiTimer2::set(20,1.0/1000,TimerHandle);
    FlexiTimer2::start();
}

