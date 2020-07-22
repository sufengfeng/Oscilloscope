#include "waves.h"
#include "timer_handle.h"
#include "pin_init.h"
#include "oled.h"
#include "mechine_state.h"

void setup() {
  // initialize serial communications at 9600 bps:
  InitPins() ;      //初始化外部IO
  InitTimer();    //初始化定时器
  setup_oled();   //初始化oled      
  setup_wave();   //初始化波形发生器
  Serial.begin(9600);//保证串口必须可用
}

void loop() {
//  int sensorValue = analogRead(A0);
  loop_oled();    //oled循环显示
  UpdateWaveDigital();    //根据需要更新波形数据
  MechineSateLoop();      //状态机维护
  delay(10);              // delay in between reads for stability
  static  uint32_t  i=0;
  
  Serial.println("_running..."); 
}

