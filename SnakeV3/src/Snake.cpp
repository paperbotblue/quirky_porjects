#include "/sharedDrive/Project/SnakeV3/inc/Snake.hpp"

Snake::Snake(int x, int y, int w, int h)
{
  SDL_Rect head{x,y,w,h};
  this->body.addNode(head);
  head = {x-40,y,w,h};
  this->body.addNode(head);
  this->velocityX = 1;
  this->velocityY = 0;
  this->w = w;
  this->h = h;
}   

void Snake::snakeRender(SDL_Renderer* gRenderer)
{
  SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
  for(int i = 0 ; i < this->body.size ; i++)
  {
  SDL_RenderFillRect(gRenderer,&this->body.getNode(i)->data);
  }
}

void Snake::screenCollision()
{
  if(this->body.head->data.x > 1080)
  {
    this->body.head->data.x = 0;
  }
  if(this->body.head->data.x < -30)
  {
    this->body.head->data.x = 1080;
  }

  if(this->body.head->data.y > 720)
  {
    this->body.head->data.y = 0;
  }
  if(this->body.head->data.y < 0)
  {
    this->body.head->data.y = 720;
  }
}

void Snake::snakeMove()
{

  for(int i = 0 ; i < this->body.size ; i++)
  {
    this->body.getNode(i)->data.x+=velocityX;
    this->body.getNode(i)->data.y+=velocityY;
  }
  
}

bool Snake::isEaten(food* f1)
{
  if(f1->x <= this->body.head->data.x && 
    f1->x+30 >= this->body.head->data.x &&
    f1->y <= this->body.head->data.y &&
    f1->y+30 >= this->body.head->data.y)
    {
      return true;
    }
  if(f1->x <= this->body.head->data.x+30 && 
    f1->x+30 >= this->body.head->data.x+30 &&
    f1->y <= this->body.head->data.y+30 &&
    f1->y+30 >= this->body.head->data.y+30)
    {
      return true;
    }
    return false;

}

void Snake::snakeGrown()
{
  SDL_Rect temp{body.head->data.x+velocityX*30,body.head->data.y+velocityY*30,w,h};
  this->body.addNode(temp);
}


bool Snake::isDead()
{
  for(int i = 3 ; i < body.size ; i++)
  {
    if(this->body.getNode(i)->data.x <= this->body.head->data.x && 
    this->body.getNode(i)->data.x+30 >= this->body.head->data.x &&
    this->body.getNode(i)->data.y <= this->body.head->data.y &&
    this->body.getNode(i)->data.y+30 >= this->body.head->data.y)
       {
        return true;
       }
  }
  return false;
}

