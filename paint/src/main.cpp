#include <iostream>
#include "../inc/Window.h"
#include "../../../Includes/linkedList.hpp"

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

struct Rect
{
    SDL_Rect b;
    bool operator==(Rect &a) const
    {
        if(a.b.x == this->b.x &&a.b.y == this->b.y &&a.b.w == this->b.w &&a.b.h == this->b.h )
        {
            return true;
        }return false;
    }
    bool operator!=(Rect &a) const
    {
        if(a.b.x == this->b.x &&a.b.y == this->b.y &&a.b.w == this->b.w &&a.b.h == this->b.h )
        {
            return false;
        }return true;
    }
    void print(){}
};
int main() {
    Window *gameWindow = new Window(WINDOW_WIDTH, WINDOW_HEIGHT);
    linkedList<Rect> grid;
    int total_grid = 72*108;
    for(int i = 0 ; i < 72 ; i++)
    {
        for(int j = 0 ; j < 108 ; j++)
        {
            Rect a = {j*10,i*10,10,10};
            grid.addNode(a);
        }
    }
    bool quit = false;
    SDL_Event e;
    int Mx,My;
    while (!quit) {
        while (SDL_PollEvent(&e) > 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_0)
                {
                    SDL_GetMouseState(&Mx,&My);
                    Mx/=10;Mx*=10;
                    My/=10;My*=10;
                    Rect a{}; a.b = {Mx,My,10,10};
                    if(grid.deleteNode(a))
                    {
                        total_grid--;
                    }
                }
            }}

            gameWindow->windowRender();

        for(int i = 0 ; i < total_grid ; i++)
        {
            SDL_SetRenderDrawColor(gameWindow->getRenderer(),0x00,0x00,0x00,0xFF);
            SDL_RenderFillRect(gameWindow->getRenderer(),&grid.getNode(i)->data.b);
        }

            SDL_RenderPresent(gameWindow->getRenderer());

        }


}