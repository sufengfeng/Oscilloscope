#include "global_param.h"
//全局变量参数配置
volatile bool g_bIsUpdateWaveDigital=false;  //更新波形数据标识位
volatile int g_nWaveType = 0;                //默认正弦信号
volatile uint8_t g_nCurrentState=0;         // 状态机
volatile bool g_bEnableLogicAn=false;       //更新逻辑分析仪标识位


volatile uint32_t g_nLogicAnValue=false;       //当前逻辑分析仪的数值
