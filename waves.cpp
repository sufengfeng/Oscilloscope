#include "waves.h"
#include "pin_init.h"
#include "global_param.h"
//定义8位R2R DA输出的对应值
int wavedigital[255];
//定义图形周期
int cycle;
//波形模式切换按键
const int buttonPin = 0;
//波形常数



//波形数值生成
void wagegen()
{
     float x; 
     float y; 

    //正玄波的值
    if(g_nWaveType==0)
    { 
       for(int i=0;i<255;i++)
       {
          x=(float)i;
          y=sin((x/255)*2*PI);
          wavedigital[i]=int(y*128)+128;
       }
     } 
    
    //三角波的值
    if(g_nWaveType==1)
    { 
   
         for(int i=0;i<128;i++)
         {
          x=(float)i;
          wavedigital[i]=int(2*x);       
         }
 
         for(int i=128;i<255;i++)
         {
          x=(float)i;
          wavedigital[i]=255-int((x-128)*2);              
          }
     }
  //锯齿波
  if(g_nWaveType==2)
    {   
          for(int i=0;i<255;i++)
         {
          x=(float)i;
          wavedigital[i]=x;       
          }   
    }
     
     
    //方波值得生成
    if(g_nWaveType==3)
    {   
       for(int i=0;i<128;i++)
       {
         wavedigital[i]=255;      
       }
 
        for(int i=128;i<255;i++)
        {
          wavedigital[i]=0;
         }  
     }
}
// 波形选择程序
void waveSelect() {
 //选择所需波形 0-正玄波 1-三角波 2-锯齿波 3-矩形波
  g_nWaveType++;
  if(g_nWaveType == 4)
    {
     g_nWaveType=0;
    }
     wagegen();
    delay(3000);
}
//波形初始化
void setup_wave() 
{  
     wagegen();
} 

//循环产生波形，周期不可修改
void loopwave() 
{ 
//     if(digitalRead(buttonPin)==1)
//     {
//      waveSelect(); 
//     }
     //增加此句后会影响波形的质量，波形导致失真
     //cycle=int(analogRead(A0)/10)+1;
   
//     for (int i=0;i<255;i++) 
//     { 
          static int i=0;
          analogWrite(AOUT_PIN, wavedigital[i]);
          i++;
          if (i>=255)i=0;
          
         //调试各个波形的值
          //Serial.println( wavedigital[i]);
         //调试波形周期
          //delayMicroseconds(cycle);
         // delayMicroseconds(10);
//     }
    //调试模拟量输入的值已决定波形周期
    // Serial.println(cycle); 
}
//先选择所需波形 wave：0-正玄波 1-三角波 2-锯齿波 3-矩形波
//更新波形数据  
void UpdateWaveDigital(){
  if(g_bIsUpdateWaveDigital){
    g_bIsUpdateWaveDigital=false;
    wagegen();
    delay(100); 
  }
    
}





