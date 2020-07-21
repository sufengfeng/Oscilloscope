#include "mechine_state.h"
#include "ArduinoJson-v6.9.1.h"
#include "pin_init.h"
#include "global_param.h"



//主程序中维护状态机，用于人机交互
void MechineSateLoop(){
  //如果是在SelectMenue状态下，则根据电位器进行判断所属状态
  if((g_nCurrentState!=StateWelcom)&&(g_nCurrentState!=OsziMode)&&(g_nCurrentState!=FuncGenMode)&&(g_nCurrentState!=LogicAnMode)){
      int registerValue=analogRead(REGESTER_PIN);//根据电位器状态设置当前菜单状态
     if(registerValue>int(1024/6*5))
          g_nCurrentState=SelectMenue05;
     else if(registerValue>int(1024/6*4))
          g_nCurrentState=SelectMenue04;
     else if(registerValue>int(1024/6*3))
          g_nCurrentState=SelectMenue03;
      else if(registerValue>int(1024/6*2))
        g_nCurrentState=SelectMenue02;
      else if(registerValue>int(1024/6*1))
        g_nCurrentState=SelectMenue01;
      else 
        g_nCurrentState=StateWelcom;    
  }

            
  switch(g_nCurrentState){
    case StateWelcom:
      if(digitalRead(BUTTON_PIN)==1)//按键按下，切换状态
        g_nCurrentState=SelectMenue01;        
      break;
    case SelectMenue01:
            if(digitalRead(BUTTON_PIN)==1)     //按键按下，进入示波器状态
              g_nCurrentState=OsziMode;        
        break;
    case SelectMenue02:
            if(digitalRead(BUTTON_PIN)==1)     //按键按下，进入信号发生状态
              g_nCurrentState=FuncGenMode;   
            if(g_nWaveType!=0){
              g_nWaveType=0;                  //波形选型
              g_bIsUpdateWaveDigital=true;    //置位更新波形数据
            }
        break;
    case SelectMenue03:
          if(digitalRead(BUTTON_PIN)==1)     //按键按下，进入信号发生状态
            g_nCurrentState=FuncGenMode;      
          if(g_nWaveType!=1){
              g_nWaveType=1;                  //波形选型
              g_bIsUpdateWaveDigital=true;    //置位更新波形数据
            }
        break;
    case SelectMenue04:
           if(digitalRead(BUTTON_PIN)==1)     //按键按下，进入信号发生状态
             g_nCurrentState=FuncGenMode;        
           if(g_nWaveType!=2){
            g_nWaveType=2;                  //波形选型
            g_bIsUpdateWaveDigital=true;    //置位更新波形数据
          }
        break;
    case SelectMenue05:
          if(digitalRead(BUTTON_PIN)==1)     //按键按下，进入逻辑分析仪
            g_nCurrentState=LogicAnMode;        
        break;
      break;
    case OsziMode:
    case FuncGenMode:
    case LogicAnMode:
        if(digitalRead(BUTTON_PIN)==1)     //按键按下，切换状态
          g_nCurrentState=SelectMenue01;        
        break;
    default:
      g_nCurrentState=StateWelcom;
  }
}

