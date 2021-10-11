#include "Leds.h"

Leds::Leds() {}

Leds::Leds(unsigned char r, unsigned char g, unsigned char b, unsigned char w) : _redPin(r), _greenPin(g), _bluePin(b), _whitePin(w){}

void Leds::Setup() {
    pinMode(this->_redPin, OUTPUT);
    pinMode(this->_greenPin, OUTPUT);
    pinMode(this->_bluePin, OUTPUT);
    pinMode(this->_whitePin, OUTPUT);
}

void Leds::Show() {
    analogWrite(this->_redPin, this->_color.Red);
    analogWrite(this->_greenPin, this->_color.Green);
    analogWrite(this->_bluePin, this->_color.Blue);
    analogWrite(this->_whitePin, this->_color.White);
}

void Leds::Stop() {
    analogWrite(this->_redPin, 0);
    analogWrite(this->_greenPin, 0);
    analogWrite(this->_bluePin, 0);
    analogWrite(this->_whitePin, 0);
}

void Leds::Clear() {
  Leds::Stop();
    this->_color.Red = 0;
    this->_color.Green = 0;
    this->_color.Blue = 0;
    this->_color.White = 0;
}

Color Leds::GetColor() {
  return this->_color;
}

void Leds::SetColor(Color color) {
  this->_color = color;
}
