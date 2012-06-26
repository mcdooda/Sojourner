#ifndef DEPS_RECTANGLE_H
 #define DEPS_RECTANGLE_H

typedef struct {
  float x00, y00;
  float x01, y01;
  float x11, y11;
  float x10, y10;
} Rectangle;

void  rectangle_set       (Rectangle* rectangle, float x, float y, float h, float w);
float rectangle_x         (Rectangle* rectangle);
float rectangle_y         (Rectangle* rectangle);
float rectangle_width     (Rectangle* rectangle);
float rectangle_height    (Rectangle* rectangle);
void  rectangle_setX      (Rectangle* rectangle, float x);
void  rectangle_setY      (Rectangle* rectangle, float y);
void  rectangle_setWidth  (Rectangle* rectangle, float w);
void  rectangle_setHeight (Rectangle* rectangle, float h);

#endif
