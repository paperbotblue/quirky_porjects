#include <iostream>
#include <SDL2/SDL.h>
#include "../inc/Window.h"
#include "../../../Includes/linkedList.hpp"

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

struct Coord
{
    int x,y;
};
struct Line
{
    Coord a,b;
};
struct Circle
{
    int32_t x,y;
    int32_t radius;
};
Coord PreviousMousePos{};

void DrawCircle(SDL_Renderer * renderer, int32_t centreX,int32_t  centreY, int32_t radius)
{
    int32_t iPx = 0;
    int32_t iPy = radius;

    double dP = 1-radius;
    while(iPx < iPy)
    {
        SDL_RenderDrawPoint(renderer, iPx + centreX, iPy + centreY);
        SDL_RenderDrawPoint(renderer, -iPx + centreX, iPy + centreY);
        SDL_RenderDrawPoint(renderer, iPx + centreX, -iPy + centreY);
        SDL_RenderDrawPoint(renderer, -iPx + centreX, -iPy + centreY);
        SDL_RenderDrawPoint(renderer, iPy + centreX, (iPx + centreY));
        SDL_RenderDrawPoint(renderer, iPy + centreX, (-iPx + centreY));
        SDL_RenderDrawPoint(renderer, -iPy + centreX, (-iPx + centreY));
        SDL_RenderDrawPoint(renderer, -iPy + centreX, (iPx + centreY));
        if (dP < 0) {
            iPx = iPx + 1;
            dP = dP + (iPx << 1) + 5;
        } else if (dP >= 0) {
            iPx = iPx + 1;
            iPy = iPy - 1;
            dP = dP + ((iPx - iPy) << 1) + 5;
        }
    }

}

int main() {
    Window *gameWindow = new Window(WINDOW_WIDTH, WINDOW_HEIGHT);
    linkedList<Coord> points;
    linkedList<Line> Lines;
    linkedList<SDL_Rect> Rectangles;
    linkedList<SDL_Rect> FRects;
    linkedList<Circle> Circles;
    Coord mousePos;
    int colorCode = 0;
    Line L1{};
    SDL_Rect R1{};
    Circle C1{};
    bool pressed = false;
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) > 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                SDL_GetMouseState(&mousePos.x,&mousePos.y);
                switch (e.key.keysym.sym) {
                    case SDLK_0:
                        points.addNode(mousePos);
                        break;
                }
                if(!pressed)
                {
                    PreviousMousePos = mousePos;
                    pressed = true;
                }
            }
            else if(e.type == SDL_KEYUP)
            {
                SDL_GetMouseState(&mousePos.x,&mousePos.y);
                switch (e.key.keysym.sym)
                {
                    case SDLK_1:
                        L1.a = PreviousMousePos;
                        L1.b = mousePos;
                        Lines.addNode(L1);
                        break;
                    case SDLK_2:
                        R1.x = PreviousMousePos.x;
                        R1.y = PreviousMousePos.y;
                        R1.w = mousePos.x-PreviousMousePos.x;
                        R1.h = mousePos.y-PreviousMousePos.y;
                        Rectangles.addNode(R1);
                        break;
                    case SDLK_3:
                        R1.x = PreviousMousePos.x;
                        R1.y = PreviousMousePos.y;
                        R1.w = mousePos.x-PreviousMousePos.x;
                        R1.h = mousePos.y-PreviousMousePos.y;
                        FRects.addNode(R1);
                        break;
                    case SDLK_4:
                        C1.x = PreviousMousePos.x;
                        C1.y = PreviousMousePos.y;
                        C1.radius = sqrt((mousePos.x-PreviousMousePos.x)*(mousePos.x-PreviousMousePos.x)+(mousePos.y-PreviousMousePos.y)*(mousePos.y-PreviousMousePos.y));
                        Circles.addNode(C1);
                        break;
                    case SDLK_5:
                        C1.x = PreviousMousePos.x;
                        C1.y = PreviousMousePos.y;
                        C1.radius = sqrt((mousePos.x-PreviousMousePos.x)*(mousePos.x-PreviousMousePos.x)+(mousePos.y-PreviousMousePos.y)*(mousePos.y-PreviousMousePos.y));
                        while(C1.radius > 0)
                        {
                            Circles.addNode(C1);
                            C1.radius--;
                        }
                        break;
                    case SDLK_w:
                        colorCode = 0;
                        break;
                    case SDLK_r:
                        colorCode = 1;
                        break;
                    case SDLK_g:
                        colorCode = 2;
                        break;
                    case SDLK_b:
                        colorCode = 3;
                        break;

                }
                pressed = false;

            }
            gameWindow->windowRender();
            switch (colorCode) {
                case 0:
                    SDL_SetRenderDrawColor(gameWindow->getRenderer(),0xFF,0xFF,0xFF,0xFF);
                    break;
                case 1:
                    SDL_SetRenderDrawColor(gameWindow->getRenderer(),0xFF,0x00,0x00,0xFF);
                    break;
                case 2:
                    SDL_SetRenderDrawColor(gameWindow->getRenderer(),0x00,0xFF,0x00,0xFF);
                    break;
                case 3:
                    SDL_SetRenderDrawColor(gameWindow->getRenderer(),0x00,0x00,0xFF,0xFF);
                    break;
            }
            for(int i = 0 ; i < points.size ; i++)
            {
                Coord P1 = points.getNode(i)->data;
                SDL_RenderDrawPoint(gameWindow->getRenderer(),P1.x,P1.y);
            }
            for(int i = 0 ; i < Lines.size ; i++)
            {
                Line L2 = Lines.getNode(i)->data;
                SDL_RenderDrawLine(gameWindow->getRenderer(),L2.a.x,L2.a.y,L2.b.x,L2.b.y);
            }
            for(int i = 0 ; i < Rectangles.size ; i++)
            {
                SDL_Rect R2 = Rectangles.getNode(i)->data;
                SDL_RenderDrawRect(gameWindow->getRenderer(), &R2);
            }
            for(int i = 0 ; i < FRects.size ; i++)
            {
                SDL_Rect R2 = FRects.getNode(i)->data;
                SDL_RenderFillRect(gameWindow->getRenderer(), &R2);
            }
            for(int i = 0 ; i < Circles.size ; i++)
            {
                Circle C2 = Circles.getNode(i)->data;
                DrawCircle(gameWindow->getRenderer(),C2.x,C2.y,C2.radius);
            }
            SDL_RenderPresent(gameWindow->getRenderer());

        }
    }

}