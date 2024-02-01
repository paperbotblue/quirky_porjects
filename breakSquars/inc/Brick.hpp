#ifndef BRICK_HPP_
#define BRICK_HPP_

#include <stdio.h>
#include <SDL2/SDL.h>
#include "line.hpp"

class Brick
{
    private:
    Brick* bri;
    int speedX = 1;
    rectangleLine rectL;
    Uint8 R{},G{},B{},A{};
    SDL_Renderer* gRenderer{};
    public:

    SDL_Rect brick;
    int speedY = 1;
    Brick(SDL_Renderer* Renderer,int x, int y,int w, int h, int r,int g,int b,int a);
    void renderBrick();
    void moveB(int x,int y);
    Brick* createBrick(SDL_Renderer* Renderer,int x, int y,int w, int h, int r,int g,int b,int a);
    void move(int i);
    void moveB();
    bool collisionCheck(Brick* R1,Brick* R2);
    void collisionCheckBoard(Brick* R1,Brick* R2);
    ~Brick();
};

#endif 