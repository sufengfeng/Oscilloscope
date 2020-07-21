#ifndef __MECHINE_STATE__H
#define __MECHINE_STATE__H
#include "Arduino.h"

enum MechineState {
  StateWelcom = 0,   //欢迎界面
  SelectMenue01,            //菜单01
  SelectMenue02,            //菜单02
  SelectMenue03,            //菜单03
  SelectMenue04,            //菜单04
  SelectMenue05,            //菜单05
  
  OsziMode,       //示波器状态
  FuncGenMode,    //信号发生器状态
  LogicAnMode     //逻辑分析仪状态
};


void MechineSateLoop();

#endif
