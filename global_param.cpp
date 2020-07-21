#include "global_param.h"
//全局变量参数配置
volatile bool g_bIsUpdateWaveDigital=false;  //更新波形数据标识位
volatile int g_nWaveType = 0;                //默认正弦信号
volatile uint8_t g_nCurrentState=0;         // 状态机
