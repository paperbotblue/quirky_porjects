#include <iostream>
#include <vector>
#include "../inc/button.h"
#include "../inc/Window.h"
#include "../inc/Shapes.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

Uint32 lastTick;
int desiredFPS = 60;

void drawStructure(SDL_Renderer*);
void functionButtons(Button*);


int main() {
    auto *gameWindow = new Window(WINDOW_WIDTH, WINDOW_HEIGHT);
    auto *buttons = new Button();
    functionButtons(buttons);
    std::vector<SDL_Point> Points;
    vector2 ghostShape{};
    std::vector<vector2> Rectangles;
    std::vector<vector2> Lines;
    std::vector<vector2> Circles;
    int key;
    bool keydown = false;
    bool penDown = false;
    bool penDown0 = false;
    Shapes shapes;
    SDL_Point mousePos = {0,0};
    SDL_Point previousMousePos = {0,0};
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        if (SDL_GetTicks() - lastTick < (1000/desiredFPS)) {
            continue;
        }
        lastTick = SDL_GetTicks();

        while (SDL_PollEvent(&e) > 0) {
            SDL_GetMouseState(&mousePos.x,&mousePos.y);
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN && !penDown)
            {
                if(!keydown){ SDL_GetMouseState(&previousMousePos.x, &previousMousePos.y); keydown = true;}
                SDL_GetMouseState(&mousePos.x,&mousePos.y);
                switch (e.key.keysym.sym) {
                    case SDLK_0: penDown0 = true; break;
                    case SDLK_1:
                        penDown = true;
                        break;
                    case SDLK_2:
                        key = 1;
                        break;
                    case SDLK_3:
                        key = 2;
                        break;
                    case SDLK_4:
                        key = 3;
                        break;
                    default: key = -1;
                }
                ghostShape = {{previousMousePos},{mousePos}};
            }
            else if (e.type == SDL_KEYUP) {
                keydown = false;
                switch (e.key.keysym.sym)
                {
                    case SDLK_1: penDown = false; break;
                    case SDLK_2: Lines.push_back({previousMousePos, mousePos});break;
                    case SDLK_3: Rectangles.push_back({previousMousePos, mousePos});break;
                    case SDLK_4: Circles.push_back({previousMousePos, mousePos});break;
                    case SDLK_5: ;break;
                    case SDLK_6: ;break;
                }
            }
        }
        gameWindow->windowRender();

        if(penDown)
        {
            SDL_GetMouseState(&previousMousePos.x, &previousMousePos.y);
            Points.push_back(previousMousePos);
        }

        SDL_SetRenderDrawColor(gameWindow->getRenderer(),0x00,0x00,0x00,0xFF);
        shapes.ghostShapes(gameWindow->getRenderer(),key,&ghostShape);
        shapes.drawPoints(gameWindow->getRenderer(),&Points);
        shapes.drawLine(gameWindow->getRenderer(),&Lines);
        shapes.drawRect(gameWindow->getRenderer(),&Rectangles);
        shapes.drawCircle(gameWindow->getRenderer(),&Circles);

        drawStructure(gameWindow->getRenderer());

        buttons->renderButtons(gameWindow->getRenderer(),&mousePos,penDown0);

        SDL_RenderPresent(gameWindow->getRenderer());
        lastTick = SDL_GetTicks();
    }

    delete gameWindow;
    delete buttons;
}

void drawStructure(SDL_Renderer* renderer)
{
    int menuWidth = 150;
    SDL_SetRenderDrawColor(renderer,0x7F,0xAC,0xD6,0xFF);
    SDL_Rect tempRect = {0,0,menuWidth,WINDOW_HEIGHT};
    SDL_RenderFillRect(renderer,&tempRect);

    int windowBorder = 3;
    SDL_SetRenderDrawColor(renderer,0x33,0x53,0x9E,0xFF);

    tempRect = {0,0,WINDOW_WIDTH,windowBorder};
    SDL_RenderFillRect(renderer,&tempRect);

    tempRect = {WINDOW_WIDTH-windowBorder,0,windowBorder,WINDOW_HEIGHT};
    SDL_RenderFillRect(renderer,&tempRect);

    tempRect = {0,WINDOW_HEIGHT-24-windowBorder,WINDOW_WIDTH,windowBorder};
    SDL_RenderFillRect(renderer,&tempRect);

    tempRect = {menuWidth,0,windowBorder,WINDOW_HEIGHT};
    SDL_RenderFillRect(renderer,&tempRect);

    tempRect = {0,0,windowBorder,WINDOW_WIDTH};
    SDL_RenderFillRect(renderer,&tempRect);
}

void functionButtons(Button* buttons)
{
    int offsetX = 17;
    int offsetY = 40;
    SDL_Rect a;
    for(int i = 0 ; i < 5 ; i++)
    {
        for(int j = 0; j < 6 ; j++)
        {
            a = {offsetX+j*20,offsetY+i*20,20,20};
            buttons->buttons.push_back(a);
        }
    }
    offsetY += 115;
    for(int i = 0; i < 3 ; i++)
    {
        for(int j = 0 ; j < 2 ; j++)
        {
            a = {offsetX+j*60,offsetY+i*20,60,20};
            buttons->buttons.push_back(a);
        }
    }

}




