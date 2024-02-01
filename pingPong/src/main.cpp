#include <stdio.h>
#include <SDL2/SDL.h>
#include "gWindow.hpp"
#include "gShapes.hpp"

int main(int,char**)
{
    gWindow window(720,1020,"Game window");

    gShapes R1(rectangle,window.getRenderer(),Uint8(0xFF),Uint8(0xFF),Uint8(0xFF),Uint8(0xFF),50,(1020/2-1020/4)-25,25,720/3);

    gShapes R2(rectangle,window.getRenderer(),Uint8(0xFF),Uint8(0xFF),Uint8(0xFF),Uint8(0xFF),1020-25-50,(1020/2-1020/4)-25,25,720/3);


//using rect for ball because circle is not yet implemented
    gShapes C1(circle,window.getRenderer(),Uint8(0xFF),Uint8(0xFF),Uint8(0xFF),Uint8(0xFF),1080/2-50,720/2-25,50,50);


    int counter = 0;
    SDL_Event e;
    bool quit = false;
    while(quit == false)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_w)
                {
                    R1.moveY(-10);
                }
                else if(e.key.keysym.sym == SDLK_s)
                {
                    R1.moveY(10);
                }
            }
        }   counter ++;
            if(counter == 20)
            {
                R2.R1.y = C1.R1.y-C1.R1.h/2-C1.R1.h-25;
                if(C1.R1.x+50 >= R2.R1.x)
                {
                    C1.speedX*=(-1);
                }
                if (C1.move(R1) == -1)
                {
                    quit = true;
                }
                counter = 0;
            }
            window.render();
            R1.draw();
            R2.draw();
            C1.draw();
            SDL_RenderPresent(window.getRenderer());

    }

    return 0;
}
