#ifndef GWINDOW_HPP_
#define GWINDOW_HPP_

#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>

class gWindow
{
    private:
        int height;
        int width;
        SDL_Window* window{};
        SDL_Surface* surface{};
        SDL_Renderer* renderer{};
        SDL_Texture* texture{};
        
    public:
        gWindow(int height,int width,const char* windowTitle);
        void loadTexture(const char* file);
        SDL_Renderer* getRenderer();
        int WindowH();
        int WindowW();
        void render();
        ~gWindow();


};

#endif