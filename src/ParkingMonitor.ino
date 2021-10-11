#define DEBUG

#ifdef __AVR_ATtiny85__
#include <SoftwareSerial.h>
SoftwareSerial softSerial(3, 4);
#define SER softSerial
#endif

#include "Monitor.h"
#include "DebugUtils.h"

Monitor monitor;

void setup() {
  DEBUG_BEGIN(9600);
  monitor.Setup();
  monitor.SetUpdateSpeedMs(200);
}

void loop() {
  monitor.Run();
  DEBUG_PRINT_NOTICE("Refreshed in: " + (String)monitor.GetLoopSpeedMs() + " Millis");
  DEBUG_PRINT_INFO("Distance: " + (String)monitor.GetDistanceIN() + " Inches");
  DEBUG_PRINTLN(" ");
}
