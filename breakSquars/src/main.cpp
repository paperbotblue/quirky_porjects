#include <stdio.h>

#include "gWindow.hpp"
#include "Brick.hpp"

int main(int,char**)
{
    gWindow gameWindow(720,1080,"Break Bad Squares");
    Brick B1(gameWindow.getRenderer(),gameWindow.WindowW()/2-225/2,gameWindow.WindowH()-50,225,25,0x90,0xd2,0xd8,0xFF);

    Brick Ball(gameWindow.getRenderer(),gameWindow.WindowW()/2-225/2,gameWindow.WindowH()-100,15,15,0x90,0xd2,0xd8,0xFF);

    Brick* brickArr[5][10] = {};

    int x = 10;
    int y = 10;
    Uint8 p,q,r;
    p = 0;q = 5; r = 10; 
    for(int i = 0 ; i < 5 ; i ++)
    {
        for(int j = 0 ; j < 10 ; j++)
        {
            brickArr[i][j] = B1.createBrick(gameWindow.getRenderer(),x,y,106,50,p,q,r,0xFF);
            x+=106;
            p+=5;q+=5,r+=5;
        }
        x = 10;
        y += 50;
    }

    bool quit = false;
    SDL_Event e;

    int clock = 0;

    while(quit == false)
    {
        while(SDL_PollEvent(&e))
        if(e.type == SDL_QUIT)
        {
            quit = true;
        }
        else if(e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_a:
                B1.move(-15);
                break;
            case SDLK_d:
                B1.move(15);
                break;
            }
            
        }
        SDL_RenderClear(gameWindow.getRenderer());
        SDL_SetRenderDrawColor(gameWindow.getRenderer(),0xFF,0xFF,0xFF,0xFF);

        SDL_RenderClear(gameWindow.getRenderer());

        B1.renderBrick();
        Ball.renderBrick();

        if(clock == 10)
        {
            Ball.moveB();
            clock = 0;
            for(int i = 0; i < 5 ; i++)
            {
            Ball.collisionCheckBoard(&Ball,&B1);
                for (int j = 0 ; j < 10 ; j++)
                {
                if(brickArr[i][j] == NULL)
                {
                    continue;
                }
                if(Ball.collisionCheck(&Ball,brickArr[i][j]))
                {
                    free(brickArr[i][j]);
                    brickArr[i][j] = NULL;

                }
                }
            }
        }
        clock++;

        for(int i = 0; i < 5 ; i++)
        {
            for (int j = 0 ; j < 10 ; j++)
            {
                if(brickArr[i][j] == NULL)
                {
                    continue;
                }
                brickArr[i][j]->renderBrick();

            }
        }
        if(Ball.brick.y >= 720)
        {
            quit = true;
        }


        SDL_RenderPresent(gameWindow.getRenderer());
    }

    SDL_Quit();
    return 0;
}