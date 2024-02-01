#include "/sharedDrive/Project/SnakeV3/inc/food.hpp"


food::food()
{
  this->x = rand()%1050;
  this->y = rand()%690;
  foo = {x,y,30,30};
}

void food::generateFood()
{
  this->x = rand()%1040;
  this->y = rand()%680;
  foo = {x,y,30,30};
}

void food::renderFoo(SDL_Renderer* gRenderer)
{
    SDL_SetRenderDrawColor(gRenderer,0xDC,0x14,0x03,0xFF);
    SDL_RenderFillRect(gRenderer,&this->foo);
}
