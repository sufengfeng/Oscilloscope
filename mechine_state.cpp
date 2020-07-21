#include "mechine_state.h"
#include "ArduinoJson-v6.9.1.h"
#include "pin_init.h"
#include "global_param.h"



//主程序中维护状态机，用于人机交互
void MechineSateLoop(){
  //如果是在SelectMenue状态下，则根据电位器进行判断所属状态
  if((g_nCurrentState!=StateWelcom)&&(g_nCurrentState!=OsziMode)&&(g_nCurrentState!=FuncGenMode)&&(g_nCurrentState!=LogicAnMode)){
//      Serial.println(__LINE__); 
      int registerValue=analogRead(REGESTER_PIN);//根据电位器状态设置当前菜单状态
//      Serial.println(registerValue); 
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
  }

            
  switch(g_nCurrentState){
    case StateWelcom:
      if(digitalRead(BUTTON_PIN)==1)//按键按下，切换状态
      {
        g_nCurrentState=SelectMenue01;    
        Serial.print("change state:"); 
        Serial.println(g_nCurrentState);       
      }
      break;
    case SelectMenue01:
            if(digitalRead(BUTTON_PIN)==1)     //按键按下，进入示波器状态
            {
              Serial.print("change state:"); 
              Serial.println(g_nCurrentState);       
              g_nCurrentState=OsziMode;        
            }
        break;
    case SelectMenue02:
            if(digitalRead(BUTTON_PIN)==1)     //按键按下，进入信号发生状态
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
          if(digitalRead(BUTTON_PIN)==1)     //按键按下，进入信号发生状态
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
           if(digitalRead(BUTTON_PIN)==1)     //按键按下，进入信号发生状态
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
          if(digitalRead(BUTTON_PIN)==1)     //按键按下，进入逻辑分析仪
            {
                g_nCurrentState=LogicAnMode;        
                Serial.print("change state:"); 
                Serial.println(g_nCurrentState); 
            }
        break;
      break;
    case OsziMode:
    case FuncGenMode:
    case LogicAnMode:
        if(digitalRead(BUTTON_PIN)==1)     //按键按下，切换状态
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

