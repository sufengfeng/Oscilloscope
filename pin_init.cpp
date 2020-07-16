#include "pin_init.h"

//初始化所有IO口
void InitPin(){
  //attachInterrupt(button, waveSelect, RISING);  
  
}

//ADC输入
int  GetAIValue(){
  return analogRead(AI_PIN);
}
//获得滑动变阻器输入
int  GetRegisterValue(){
  return analogRead(REGESTER_PIN);
}
//DAC输出
void  SetDIValue(uint8_t outputValue){
   analogWrite(DI_PIN, outputValue);
}


