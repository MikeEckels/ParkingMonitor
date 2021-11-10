#ifndef MONITOR_H
#define MONITOR_H

#include "Arduino.h"
#include <SharpIR.h>

#ifndef __AVR_ATtiny85__
#include "Leds.h"
#endif

class Monitor {
  private:
#ifdef __AVR_ATtiny85__
    const unsigned char _irPin = A1;
#else
    const unsigned char _irPin = A0;
#endif

    const unsigned int _irModel = 20150;
    
    unsigned int _parkedWatchDogInterval = 15000; // RED leds will stay on for 15 seconds after parked.
    unsigned int _updateSpeedMs = 500;
    unsigned int _closeRangeIN = 60; //5ft
    unsigned int _mediumRangeIN = 72; //6ft
    unsigned int _farRangeIN = 120; //10ft

    unsigned long _previousTime = 0;
    unsigned long _loopSpeed = 0;
    int _distance = 0;
    bool _parked = false;
    bool _parkedAndOff = false;

#ifndef __AVR_ATtiny85__
    Leds _leds;
#endif
    SharpIR _Ir = SharpIR(_irPin, _irModel);

  public:
    Monitor();
    Monitor(unsigned char irPin, unsigned int irModel, unsigned int updateSpeedMs);

    void Setup();
    void Run();

    void SetUpdateSpeedMs(unsigned int updateSpeedMs);
    void SetCloseRangeIN(unsigned int closeRangeIN);
    void SetMediumRangeIN(unsigned int mediumRangeIN);
    void SetFarRangeIN(unsigned int farRangeIN);

#ifndef  __AVR_ATtiny85__
    Leds* GetLeds();
#endif

    unsigned int GetDistanceIN();
    unsigned long GetLoopSpeedMs();
};

#endif //MONITOR_H
