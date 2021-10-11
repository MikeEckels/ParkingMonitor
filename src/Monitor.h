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
    
    unsigned int _updateSpeedMs = 500;
    unsigned int _closeRangeIN = 9;
    unsigned int _mediumRangeIN = 48; //4ft
    unsigned int _farRangeIN = 96; //8ft

    unsigned long _loopSpeed = 0;
    int _distance = 0;
    bool _parked = false;

#ifndef __AVR_ATtiny85__
    Leds _leds;
    Color _RED = Color(255, 0, 0, 0);
    Color _GREEN = Color(0, 255, 0, 0);
    Color _YELLOW = Color(255, 128, 0, 0);
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

    unsigned int GetDistanceIN();
    unsigned long GetLoopSpeedMs();
};

#endif //MONITOR_H
