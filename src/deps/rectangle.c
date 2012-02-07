#include "rectangle.h"

void rectangle_set(Rectangle* rectangle, float x, float y, float w, float h)
{
  rectangle->x00 = x;
  rectangle->y00 = y;
  rectangle->x01 = x;
  rectangle->y01 = y + h;
  rectangle->x11 = x + w;
  rectangle->y11 = y + h;
  rectangle->x10 = x + w;
  rectangle->y10 = y;
}

float rectangle_x(Rectangle* rectangle)
{
  return rectangle->x00;
}

float rectangle_y(Rectangle* rectangle)
{
  return rectangle->y00;
}

float rectangle_width(Rectangle* rectangle)
{
  return rectangle->x10 - rectangle->x00;
}

float rectangle_height(Rectangle* rectangle)
{
  return rectangle->y01 - rectangle->y00;
}

void rectangle_setX(Rectangle* rectangle, float x)
{
  float w = rectangle_width(rectangle);
  rectangle->x00 = x;
  rectangle->x01 = x;
  rectangle->x11 = x + w;
  rectangle->x10 = x + w;
}

void rectangle_setY(Rectangle* rectangle, float y)
{
  float h = rectangle_height(rectangle);
  rectangle->y00 = y;
  rectangle->y01 = y + h;
  rectangle->y11 = y + h;
  rectangle->y10 = y;
}

void rectangle_setWidth(Rectangle* rectangle, float w)
{
  rectangle->x10 = rectangle->x00 + w;
  rectangle->x11 = rectangle->x10;
}

void rectangle_setHeight(Rectangle* rectangle, float h)
{
  rectangle->y01 = rectangle->y00 + h;
  rectangle->y11 = rectangle->y01;
}


