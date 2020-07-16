#include "waves.h"
#include "timer_handle.h"
#include "pin_init.h"
#include "oled.h"

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  InitTimer();    //初始化定时器
}
void loop() {
  Serial.println("running...");
  //OledTest();
}

