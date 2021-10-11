#ifndef COLOR_H
#define COLOR_H

struct Color {
  unsigned char Red = 0;
  unsigned char Green = 0;
  unsigned char Blue = 0;
  unsigned char White = 0;

  Color() {}
  Color(unsigned char R, unsigned char G, unsigned char B, unsigned char W) : Red{R}, Green{G}, Blue{B}, White{W} {}
};

#endif //COLOR_H
