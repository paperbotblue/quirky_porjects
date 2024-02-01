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
        SDL_Window* window;
        SDL_Surface* surface;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        
    public:

        gWindow(int height,int width,const char* windowTitle);
        void setSurfaceBg(Uint8 R, Uint8 G, Uint8 B);
        void loadMedia(const char* file);
        void loadMedia(const char* file,int x, int y, int h, int w);
        void loadTexture(const char* file);
        SDL_Renderer* getRenderer();
        int getWindowH();
        int getWindowW();
        void render();
        void rr();
        ~gWindow();


};

#endif