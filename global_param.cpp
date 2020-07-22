#include "global_param.h"
//全局变量参数配置
volatile bool g_bIsUpdateWaveDigital=false;  //更新波形数据标识位
volatile int g_nWaveType = 1;                //默认正弦信号
volatile uint8_t g_nCurrentState=0;         // 状态机
volatile bool g_bEnableLogicAn=false;       //更新逻辑分析仪标识位


volatile uint32_t g_nLogicAnValue=false;       //当前逻辑分析仪的数值
                  
volatile int g_aWavedigital[255];             //定义8位R2R DA输出的对应值
volatile boolean g_tTimer20ms=HIGH;           //全局20ms标志位

