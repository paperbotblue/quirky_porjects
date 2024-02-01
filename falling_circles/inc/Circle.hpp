#ifndef Circle_hpp_
#define Circle_hpp_

#include <raylib.h>
#include <raymath.h>
#include <vector>

#define GRAVITY 100.0f

struct Circle
{
  float x,y;
  float r;
  Color color;
  float Vx,Vy;
  float acceleration;
};

class Circle_Pool
{
  private:
    std::vector<Circle> circle_pool;
    unsigned int window_width,window_height;
    float screen_center_x, screen_center_y;
    float screen_center_radius;
    
  public:
    Circle_Pool(unsigned int window_width, unsigned int window_height, float r);
    void create_circle(float x, float y, float r, Color color);
    void render_circles(); 
    void collision_check();
};

#endif //
