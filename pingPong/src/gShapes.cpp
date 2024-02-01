#include "gShapes.hpp"

gShapes::gShapes()
{
    R1.h = 0;
    R1.w = 0;
    R1.x = 0;
    R1.y = 0;
}

gShapes::gShapes(shape S1,SDL_Renderer* gRenderer, Uint8 R,Uint8 G ,Uint8 B ,Uint8 A, int x, int y, int w,int h ) 
{
    this->R1.x = x;
    this->R1.y = y;
    this->R1.w = w;
    this->R1.h = h;
    printf("%d %d %d %d ",x,y,w,h);
    this->S1 = S1; 
    this->gRenderer = gRenderer;
    this->R = R;
    this->G = G;
    this->B = B;
    this->A = A;
    speedX = speedY = 1;
}

void gShapes::moveX(int pixel)
{
    this->R1.x+=pixel;
    borderCollisionCorrection();
}

void gShapes::moveY(int pixel)
{
    this->R1.y+=pixel;
    borderCollisionCorrection();
}

int gShapes::move(gShapes R12)
{

    if(R1.x <= R12.R1.x+R12.R1.w )
    {
        if(R1.y > R12.R1.y  && R1.y < R12.R1.y+R12.R1.h)
        {
            speedX*=(-1);
        }
    }
    this->R1.x+=speedX;
    this->R1.y+=speedY;

    speedX = R1.x > 1020-50 ? speedX*(-1) : speedX*1;
if(R1.x < 0)
{
    return -1;
}

    speedY = R1.y > 720-50 ? speedY*(-1) : speedY*1;
    speedY = R1.y < 0 ? speedY*(-1) : speedY*1;

return 0;


}

void gShapes::borderCollisionCorrection()
{
    if(R1.y < 0)
    {
        R1.y+=10;
    }
    else if(R1.y > R1.h*3)
    {
        R1.y-=10;
    }
}


void gShapes::draw()
{
    SDL_SetRenderDrawColor(this->gRenderer,this->R,this->G,this->B,this->A);
    SDL_RenderFillRect(this->gRenderer,&R1);
}