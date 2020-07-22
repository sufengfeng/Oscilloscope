#include "pin_init.h"

//外部上升沿触发事件
void ButtonDownHandle(){
  
}
//初始化所有IO口
void InitPins(){
  pinMode(BUTTON_PIN, INPUT);     
  attachInterrupt(BUTTON_PIN, ButtonDownHandle, RISING);  
  
}

////ADC输入
//int  GetAINValue(){
//  return analogRead(AIN_PIN);
//}
////获得滑动变阻器输入
//int  GetRegisterValue(){
//  return analogRead(REGESTER_PIN);
//}
////DAC输出
//void  SetDIValue(uint8_t outputValue){
//   analogWrite(DI_PIN, outputValue);
//}


