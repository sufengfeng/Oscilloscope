#include "waves.h"
#include "timer_handle.h"
#include "pin_init.h"
#include "oled.h"

void setup() {
  // initialize serial communications at 9600 bps:
  
  InitTimer();    //初始化定时器
  setup_oled();         
  Serial.begin(9600);//保证串口必须可用
  setup_wave(); 
}
int analogOutPin=A14;
void loop() {
//  int sensorValue = analogRead(A0);
//  Serial.println(sensorValue);
  
//  int outputValue = map(sensorValue, 0, 1023, 0, 255);
//  analogWrite(analogOutPin, outputValue);
  //loop_oled();    //oled循环显示
  
  loopwave() ;
  delay(10);        // delay in between reads for stability
}

