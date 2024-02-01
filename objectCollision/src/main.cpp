#include <stdio.h>
#include <SDL2/SDL.h>

#define PR_DEBUG 0

#if PR_DEBUG == 1
    #define LOG(x) std::cout << x << "\n" 
#else
    #define LOG(x)
#endif

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
#define CENTER_X WINDOW_WIDTH/2
#define CENTER_Y WINDOW_HEIGHT/2

int main()
{
    SDL_Window* window = SDL_CreateWindow("Object collision",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_Rect a{CENTER_X-40,CENTER_Y-20,80,40};

    int mouseX = 0;
    int mouseY = 0;
    SDL_Rect b{mouseX,mouseY,80,40};

    SDL_Event e;
    bool quit = false;
    while(!quit)
    {
        while(SDL_PollEvent(&e) > 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }


        }
    // Setting background colour
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0x00,0x14,0x84,0xFF);

    // Getting mouse location
    SDL_GetGlobalMouseState(&mouseX,&mouseY);

    // Updating rect location
    b = {mouseX-425,mouseY-210,80,40};

    SDL_RenderClear(renderer);
    // Rendering rects
    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
    SDL_RenderDrawRect(renderer,&a);

    // checking for collisions
    if((a.x < b.x+b.w && a.y < b.y+b.h) && (a.x+a.w > b.x && a.y+a.h > b.y))
    {
    SDL_SetRenderDrawColor(renderer,0xAA,0x00,0x00,0xFF);
    SDL_RenderDrawRect(renderer,&b);
    }
    else
    {
    SDL_RenderDrawRect(renderer,&b);
    }

    // Showing rendered stuff
    SDL_RenderPresent(renderer);
    }
    return 0;
}