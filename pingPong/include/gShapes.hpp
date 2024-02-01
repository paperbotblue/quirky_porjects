#ifndef GSHAPES_HPP_
#define GSHAPES_HPP_

#include <SDL2/SDL.h>
enum shape
{
    rectangle,
    square,
    circle,
    triangle
};

class gShapes
{
    private:
    shape S1;
    SDL_Renderer* gRenderer;
    Uint8 R;
    Uint8 G;
    Uint8 B;
    Uint8 A;
    int l,b;
    int x,y;

    public:
    int speedX, speedY;
    SDL_Rect R1 = {};
    gShapes();
    gShapes(shape S1,SDL_Renderer* gRenderer, Uint8 R,Uint8 G ,Uint8 B ,Uint8 A, int x, int y, int w , int h);
    void moveX(int pixel);
    void moveY(int pixel);
    void borderCollisionCorrection();
    int move(gShapes R1);
    void draw();
    //only for circle this move function

};

#endif