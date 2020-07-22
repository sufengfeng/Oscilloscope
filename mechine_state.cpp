#include "mechine_state.h"
#include "ArduinoJson-v6.9.1.h"
#include "pin_init.h"
#include "global_param.h"

//软件消抖，判断上升沿信号
bool IsRising(){
  
  static int lastLineSate=0;
  static int counter=0;
//  Serial.println(lastLineSate);       
//  Serial.println(counter);     
  counter++;
  if(counter>10){
    lastLineSate=digitalRead(BUTTON_PIN);
    counter=0;
  }
  int currentLineSate=digitalRead(BUTTON_PIN);//  当前状态
  if(lastLineSate==0&&currentLineSate==1){
    lastLineSate=1;
    counter=0;
    return true;
  }
  else
    return false;
}
//主程序中维护状态机，用于人机交互
void MechineSateLoop(){
  //根据是否在SelectMenue状态下，进行一些安全的强制状态锁定
  if((g_nCurrentState!=StateWelcom)&&(g_nCurrentState!=OsziMode)&&(g_nCurrentState!=FuncGenMode)&&(g_nCurrentState!=LogicAnMode)){
      int registerValue=analogRead(REGESTER_PIN);//根据电位器状态设置当前菜单状态
     if(registerValue>int(1024/5*4))
          g_nCurrentState=SelectMenue05;
     else if(registerValue>int(1024/5*3))
          g_nCurrentState=SelectMenue04;
     else if(registerValue>int(1024/5*2))
          g_nCurrentState=SelectMenue03;
      else if(registerValue>int(1024/5*1))
        g_nCurrentState=SelectMenue02;
      else
        g_nCurrentState=SelectMenue01;
  }else{
    if(g_nCurrentState!=LogicAnMode)//如果不是在逻辑分析仪模式下，关闭读信号使能
        g_bEnableLogicAn=false;  
  }
  
  switch(g_nCurrentState){
    case StateWelcom:
      if(IsRising()==1)//按键按下，切换状态
      {
        g_nCurrentState=SelectMenue01;    
        Serial.print("change state:"); 
        Serial.println(g_nCurrentState);       
      }
      break;
    case SelectMenue01:
            if(IsRising()==1)     //按键按下，进入示波器状态
            {
              Serial.print("change state:"); 
              Serial.println(g_nCurrentState);       
              g_nCurrentState=OsziMode;        
            }
        break;
    case SelectMenue02:
            if(IsRising()==1)     //按键按下，进入信号发生状态
              {
                g_nCurrentState=FuncGenMode;   
                Serial.print("change state:"); 
                Serial.println(g_nCurrentState); 
                if(g_nWaveType!=0){
                      g_nWaveType=0;                  //波形选型
                      g_bIsUpdateWaveDigital=true;    //置位更新波形数据
                }
              }
        break;
    case SelectMenue03:
          if(IsRising()==1)     //按键按下，进入信号发生状态
            {
              g_nCurrentState=FuncGenMode;      
              Serial.print("change state:"); 
              Serial.println(g_nCurrentState); 
              if(g_nWaveType!=1){
                    g_nWaveType=1;                  //波形选型
                    g_bIsUpdateWaveDigital=true;    //置位更新波形数据
                  }
            }
          
        break;
    case SelectMenue04:
           if(IsRising()==1)     //按键按下，进入信号发生状态
             {
                g_nCurrentState=FuncGenMode;        
                Serial.print("change state:"); 
                Serial.println(g_nCurrentState); 
                if(g_nWaveType!=2){
                    g_nWaveType=2;                  //波形选型
                    g_bIsUpdateWaveDigital=true;    //置位更新波形数据
                }
             }
        break;
    case SelectMenue05:
          if(IsRising()==1)     //按键按下，进入逻辑分析仪
            {
                g_nCurrentState=LogicAnMode;        
                g_bEnableLogicAn=true;
                Serial.print("change state:"); 
                Serial.println(g_nCurrentState); 
            }
        break;
      break;
    case OsziMode:
    case FuncGenMode:
    case LogicAnMode:
        if(IsRising()==1)     //按键按下，切换状态
        {
            g_nCurrentState=SelectMenue01;        
            Serial.print("change state:"); 
            Serial.println(g_nCurrentState); 
        }

        break;
    default:{
            g_nCurrentState=StateWelcom;
            Serial.print("change state:"); 
            Serial.println(g_nCurrentState); 
    }
  }
}

