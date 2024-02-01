#include "Brick.hpp"

Brick::Brick(SDL_Renderer* Renderer,int x, int y,int w, int h,int r,int g,int b,int a)
{
    this->gRenderer = Renderer;
    this->brick = {x,y,w,h};

    rectL.lTop.x = x;
    rectL.lTop.y = y;
    rectL.lTop.x1 = x+w;
    rectL.lTop.y1 = y;

    rectL.lDown.x = x;
    rectL.lDown.y = y+h;
    rectL.lDown.x1 = x+w;
    rectL.lDown.y1 = y+h;

    rectL.lLeft.x = x;
    rectL.lLeft.y = y;
    rectL.lLeft.x1 = x;
    rectL.lLeft.y1 = y+h;

    rectL.lRight.x = x+w;
    rectL.lRight.y = y;
    rectL.lRight.x1 = x+w;
    rectL.lRight.y1 = y+h;

    this->R = r;
    this->G = g;
    this->B = b;
    this->A = a;

}

Brick* Brick::createBrick(SDL_Renderer* Renderer,int x, int y,int w, int h, int r,int g,int b,int a)
{
    this->bri = new Brick(Renderer,x,y,w,h,r,g,b,a);
    return bri;
}

void Brick::move(int i)
{
    this->brick.x+=i;

    rectL.lTop.x = this->brick.x;
    rectL.lTop.y = this->brick.y;
    rectL.lTop.x1 = this->brick.x+brick.w;
    rectL.lTop.y1 = this->brick.y;



}
void Brick::moveB(int x,int y)
{
    this->brick.x+=x;
    this->brick.y+=y;

    rectL.lTop.x = this->brick.x;
    rectL.lTop.y = this->brick.y;
    rectL.lTop.x1 = this->brick.x+brick.w;
    rectL.lTop.y1 = this->brick.y;

    rectL.lDown.x = this->brick.x;
    rectL.lDown.y = this->brick.y+brick.h;
    rectL.lDown.x1 = this->brick.x+brick.w;
    rectL.lDown.y1 = this->brick.y+brick.h;

    rectL.lLeft.x = this->brick.x;
    rectL.lLeft.y = this->brick.y;
    rectL.lLeft.x1 = this->brick.x;
    rectL.lLeft.y1 = this->brick.y+brick.h;

    rectL.lRight.x = this->brick.x+brick.w;
    rectL.lRight.y = this->brick.y;
    rectL.lRight.x1 = this->brick.x+brick.w;
    rectL.lRight.y1 = this->brick.y+brick.h;

}

void Brick::moveB()
{

    moveB(speedX,speedY);

    if(brick.x < 0)
    {
        speedX*=-1;
    }
    if(brick.x > 1080)
    {
        speedX*=-1;
    }
    if(brick.y < 0)
    {
        speedY*=-1;
    }
    if(brick.y > 720)
    {
        speedY*=-1;
    }

}

bool Brick::collisionCheck(Brick* R1,Brick* R2)
{
    if(R1->rectL.lTop.inBetween(R2->rectL.lDown))
    {
        R1->speedY*=-1;
        return true;
    }
    if(R1->rectL.lRight.inBetween(R2->rectL.lLeft))
    {
        R1->speedX*=-1;
        return true;
    }
    if(R1->rectL.lLeft.inBetween(R2->rectL.lRight))
    {
        R1->speedX*=-1;
        return true;
    }
    if(R1->rectL.lDown.inBetween(R2->rectL.lTop))
    {
        R1->speedY*=-1;
        return true;
    }
    return false;
}


void Brick::collisionCheckBoard(Brick* R1,Brick* R2)
{
    if(R1->rectL.lDown.inBetween(R2->rectL.lTop))
    {
        R1->speedY*=-1;

    }
}


void Brick::renderBrick()
{
 
    SDL_SetRenderDrawColor(this->gRenderer,this->R,this->G,this->B,this->A);
    SDL_RenderFillRect(this->gRenderer,&this->brick);
}

Brick::~Brick()
{
    gRenderer = NULL;
}