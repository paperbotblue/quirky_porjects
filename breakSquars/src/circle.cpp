#include "circle.hpp"

circle::circle(SDL_Renderer* Renderer,int r,double x, double y)
{
    this->r = r;
    this->x = x;
    this->y = y;
    this->x1 = x+r;
    this->y1 = y;
    this->Renderer = Renderer;
}

void circle::drawCircle()    
{

        printf("%lf %lf %lf %lf\n",x,y-r,x1,y1);

        for( ;y1 > y-r; )
        {
            SDL_RenderDrawLine(this->Renderer,x,y,x1,y1);
            y1--;
        }


        x1 = x+r;
        y1 = y;
}