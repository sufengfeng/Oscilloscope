#include "waves.h"


//定义8位R2R DA输出的对应值
int wavedigital[255];
//定义图形周期
int cycle;
//波形模式切换按键
const int button = 0;
//波形常数
volatile int wave = 0;


//波形数值生成
void wagegen()
{
     float x; 
     float y; 

    //正玄波的值
    if(wave==0)
    { 
       for(int i=0;i<255;i++)
       {
          x=(float)i;
          y=sin((x/255)*2*PI);
          wavedigital[i]=int(y*128)+128;
       }
     } 
    
    //三角波的值
    if(wave==1)
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
  if(wave==2)
    {   
          for(int i=0;i<255;i++)
         {
          x=(float)i;
          wavedigital[i]=x;       
          }   
    }
     
     
    //方波值得生成
    if(wave==3)
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
  wave++;
  if(wave == 4)
    {
     
    }
     wagegen();
    delay(3000);
}
//波形初始化
void setup_wave() 
{  
     Serial.begin(9600);
   
    //设置中断程序
    //attachInterrupt(button, waveSelect, RISING);  

     //输出端口 0-7
     pinMode(0, OUTPUT); 
     pinMode(1, OUTPUT); 
     pinMode(2, OUTPUT); 
     pinMode(3, OUTPUT); 
     pinMode(4, OUTPUT); 
     pinMode(5, OUTPUT); 
     pinMode(6, OUTPUT);
     pinMode(7, OUTPUT); 
    //改变输出信号频率调整完电位器后复位后生效
     //cycle=int(analogRead(A0)/10)+1;
     cycle=10000;
     //默认输出正玄波
      wave = 0;
     wagegen();
} 

//循环产生波形
void loopwave() 
{ 
     if(digitalRead(button)==1)
     {
      waveSelect(); 
     }
     //增加此句后会影响波形的质量，波形导致失真
     //cycle=int(analogRead(A0)/10)+1;
   
     for (int i=0;i<255;i++) 
     { 
          analogWrite(A14, wavedigital[i]);
         //调试各个波形的值
          Serial.println( wavedigital[i]);
         //调试波形周期
          delayMicroseconds(cycle);
         // delayMicroseconds(10);
     }
    //调试模拟量输入的值已决定波形周期
    // Serial.println(cycle); 
     
      
    
}





