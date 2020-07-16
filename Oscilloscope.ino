#include "waves.h"
#include "timer_handle.h"


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  InitTimer();
}
void loop() {
  Serial.println("running...");
}

