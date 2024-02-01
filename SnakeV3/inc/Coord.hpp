#ifndef COORD_HPP_
#define COORD_HPP_

#include <stdio.h>

class Coord
{
  public:
  int x{};
  int y{};
  
  void operator=(Coord C2)
  {
    this->x = C2.x;
    this->y = C2.y;
  }

  bool operator==(Coord C2)
  {
    if(this->x == C2.x && this->y == C2.y )
      {
        return true;
      }
    return false;
  }
  
  void print()
  {
    printf("(%d,%d)",this->x,this->y);
  }
  
};

#endif
