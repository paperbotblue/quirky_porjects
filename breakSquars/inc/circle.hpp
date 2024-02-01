#ifndef CIRCLE_HPP_
#define CIRCLE_HPP_

#include <SDL2/SDL.h>

class circle
{
    private:
    int r;
    double x,y;
    double x1,y1;
    SDL_Renderer* Renderer;

    public:
    circle(SDL_Renderer* Renderer,int r,double x, double y);
    void drawCircle();
};

#endif