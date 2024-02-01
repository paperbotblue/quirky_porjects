#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include "/sharedDrive/Project/SnakeV3/inc/linkedList.hpp"
#include "/sharedDrive/Project/SnakeV3/inc/food.hpp"


class Snake
{
private:
    int w,h;
  
public:
    float velocityX;
    float velocityY;
  Snake(int x, int y,int w, int h);
  linkedList<SDL_Rect> body;
  void snakeMove();
  void snakeGrown();
  bool isEaten(food* f1);
  bool isDead();
  void screenCollision();
  void snakeRender(SDL_Renderer* gRenderer);
  
};

#endif // !DEBUG
