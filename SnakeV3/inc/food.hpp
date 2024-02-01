#ifndef FOOD_HPP
#define FOOD_HPP

#include <time.h>
#include <SDL2/SDL.h>


class food
{
    public:
    int x,y;
    SDL_Rect foo;
    food();
    void generateFood();
    void renderFoo(SDL_Renderer* gRenderer);


};

#endif