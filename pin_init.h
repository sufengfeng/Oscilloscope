#ifndef __PIN_DEFINE__H
#define __PIN_DEFINE__H
#include "Arduino.h"
//定义所有的IO引脚
enum PinAssignments {
  AIN_PIN = A1 ,     //模拟量输入
  AOUT_PIN = A14,   //模拟量输入
  BUTTON_PIN=0,   //
  REGESTER_PIN=A0, //滑动变阻器 
  
  encoderPinB = 3,
  driveLed = 10,
  drivePin = 6,
  loadLed = 12,
  loadPin = 4,
  brakingLed = 8
};
void InitPins();
#endif
