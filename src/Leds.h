#ifndef LEDS_H
#define LEDS_H

#include "Arduino.h"
#include "Color.h"

class Leds {
  private:
    const unsigned char _redPin = 9;
    const unsigned char _greenPin = 6;
    const unsigned char _bluePin = 10;
    const unsigned char _whitePin = 11;
  
    Color _color;

  public:
    Leds();
    Leds(unsigned char r, unsigned char g, unsigned char b, unsigned char w);

    void Setup();
    void Show();
    void Stop();
    void Clear();

    Color GetColor();

    void SetColor(Color color);
};

#endif //LEDS_H
