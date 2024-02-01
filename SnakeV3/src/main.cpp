#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include "/sharedDrive/Project/SnakeV3/inc/linkedList.hpp"
#include "/sharedDrive/Project/SnakeV3/inc/window.hpp"
#include "/sharedDrive/Project/SnakeV3/inc/Snake.hpp"
#include "/sharedDrive/Project/SnakeV3/inc/Coord.hpp"
#include "/sharedDrive/Project/SnakeV3/inc/food.hpp"

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

#define SNAKE_WIDTH 30
#define SNAKE_HEIGHT 30

int main()
{
  srand(time(NULL));

  Window* gameWindow = new Window(WINDOW_WIDTH,WINDOW_HEIGHT);
  Snake* snake = new Snake(400,500,SNAKE_WIDTH,SNAKE_HEIGHT);
  food* f1 = new food();
  snake->snakeGrown();
  SDL_Rect temp;
  int breaku = 0;

  bool quit = false;
  SDL_Event e;
  while (quit != true)
  {
    while(SDL_PollEvent(&e) > 0)
    {
      if(e.type == SDL_QUIT)
      {
        quit = true;
      }
      else if(e.type == SDL_KEYDOWN)
      {
        switch (e.key.keysym.sym)
        {
          case SDLK_w:

            snake->velocityX = 0;
            snake->velocityY = -1;
            break;
          case SDLK_d:

            snake->velocityX = 1;
            snake->velocityY = 0;
            break;
          case SDLK_a:

            snake->velocityX = -1;
            snake->velocityY = 0;
            break;
          case SDLK_s:

            snake->velocityX = 0;
            snake->velocityY = 1;
            break;
        }
      }
    }
    if(breaku == 500)
    {
    snake->snakeMove();
    snake->screenCollision();
    if(snake->isDead())
    {
      quit = true;
    }
    if(snake->isEaten(f1))
    {
      snake->snakeGrown();
      f1->generateFood();
    }
    temp = snake->body.head->data;
    temp.x += 30*snake->velocityX;
    temp.y += 30*snake->velocityY;
    snake->body.pushBack(temp);
    breaku = 0;
    }
    breaku++;
    gameWindow->windowRender();
    snake->snakeRender(gameWindow->getRenderer());
    f1->renderFoo(gameWindow->getRenderer());
    SDL_RenderPresent(gameWindow->getRenderer());
  }
  

}


