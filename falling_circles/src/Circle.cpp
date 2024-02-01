#include "./../inc/Circle.hpp"
#include <cmath>
#include <raylib.h>

Circle_Pool::Circle_Pool(unsigned int window_width, unsigned int window_height, float r)
{
  this->window_width = window_width;
  this->window_height = window_height;
  screen_center_x = window_width/2;
  screen_center_y = window_height/2;
  screen_center_radius = r;
    
}

void Circle_Pool::create_circle(float x, float y, float r, Color color)
{
  circle_pool.push_back({x, y, r, color, 0.0f, 0.0f, 0.0f});
}

void Circle_Pool::render_circles()
{
  for(int i = 0 ; i < circle_pool.size(); ++i)
  {
    DrawCircle(circle_pool[i].x, circle_pool[i].y, circle_pool[i].r, circle_pool[i].color);

    circle_pool[i].acceleration += GRAVITY * GetFrameTime();
    circle_pool[i].Vy += circle_pool[i].acceleration * GetFrameTime();
    circle_pool[i].y += circle_pool[i].Vy * GetFrameTime();

    float d = sqrt((screen_center_x - circle_pool[i].x)*(screen_center_x -circle_pool[i] .x) + 
        (screen_center_y - circle_pool[i].y)*(screen_center_y - circle_pool[i].y)); 

    if(d+circle_pool[i].r> screen_center_radius)
    {
      circle_pool[i].x -= circle_pool[i].Vx ;
      circle_pool[i].y -= circle_pool[i].Vy ;
      circle_pool[i].Vx = -circle_pool[i].Vx * 0.02f;
      circle_pool[i].Vy = -circle_pool[i].Vy * 0.02f;
    } 
  }
}
