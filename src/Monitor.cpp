#include "Monitor.h"

Monitor::Monitor() {}

Monitor::Monitor(unsigned char irPin, unsigned int irModel, unsigned int updateSpeedMs) : _irPin(irPin), _irModel(irModel), _updateSpeedMs(updateSpeedMs) {}

void Monitor::Setup() {
#ifdef __AVR_ATtiny85__
    pinMode(1, OUTPUT);
    pinMode(0, OUTPUT);
#else
  this->_leds.Setup();
#endif

  pinMode(this->_irPin, INPUT);
  delay(500);
}

void Monitor::Run() {
  unsigned long start = millis();
  delay(this->_updateSpeedMs);

  this->_distance = _Ir.distance();
  this->_distance = constrain(this->_distance, 20, 460);
  this->_distance = (float)this->_distance / (float)2.54;
  
  if(this->_distance >= this->_farRangeIN) {
    this->_parked = false;
    this->_parkedAndOff = false;
    this->_previousTime = millis();
#ifdef __AVR_ATtiny85__
    analogWrite(1, 0);
    analogWrite(0, 0);
#else
    this->_leds.Clear();
#endif
  }

  if (this->_parked == false && this->_parkedAndOff == false && this->_distance >= this->_mediumRangeIN && this->_distance < this->_farRangeIN) {
#ifdef __AVR_ATtiny85__
      analogWrite(1, 0);
      analogWrite(0, 0);
      analogWrite(1, 255);
#else
      this->_leds.Clear();
      this->_leds.SetColor(this->_leds.Colors.Green);
#endif
  }

  if(this->_parked == false && this->_parkedAndOff == false && this->_distance >= this->_closeRangeIN && this->_distance < this->_mediumRangeIN) {
#ifdef __AVR_ATtiny85__
      analogWrite(1, 0);
      analogWrite(0, 0);
      analogWrite(0, 255);
      analogWrite(1, 128);
#else
      this->_leds.Clear();
      this->_leds.SetColor(this->_leds.Colors.Yellow);
#endif
  }

  if(this->_parked == false && this->_parkedAndOff == false && this->_distance <= this->_closeRangeIN){
#ifdef __AVR_ATtiny85__
      analogWrite(1, 0);
      analogWrite(0, 0);
      analogWrite(0, 255);
#else
      this->_leds.Clear();
      this->_leds.SetColor(this->_leds.Colors.Red);
#endif
      this->_parked = true;
  }

  if (this->_parked == true && this->_parkedAndOff == false) {
      unsigned long startTime = millis();
      if (startTime - this->_previousTime > this->_parkedWatchDogInterval) {
          this->_previousTime = startTime;
#ifdef __AVR_ATtiny85__
          analogWrite(1, 0);
          analogWrite(0, 0);;
#else
          this->_leds.Clear();
#endif
          this->_parkedAndOff = true;
      }
  }

#ifndef __AVR_ATtiny85__
  this->_leds.Show();
#endif

  this->_loopSpeed = millis() - start;
}

void Monitor::SetUpdateSpeedMs(unsigned int updateSpeedMs) {
  this->_updateSpeedMs = updateSpeedMs;
}

void Monitor::SetCloseRangeIN(unsigned int closeRangeIN) {
  this->_closeRangeIN = closeRangeIN;
}

void Monitor::SetMediumRangeIN(unsigned int mediumRangeIN) {
  this->_mediumRangeIN = mediumRangeIN;
}

void Monitor::SetFarRangeIN(unsigned int farRangeIN) {
  this->_farRangeIN = farRangeIN;
}

#ifndef  __AVR_ATtiny85__
Leds* Monitor::GetLeds() {
    return &_leds;
}
#endif

unsigned int Monitor::GetDistanceIN() {
  return this->_distance;
}

unsigned long Monitor::GetLoopSpeedMs() {
  return this->_loopSpeed;
}
