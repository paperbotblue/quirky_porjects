#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <SDL2/SDL.h>
#include "./utils.hpp"
class Window
{
  public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Color bg_color;
    Window(char* window_title, unsigned int window_height, unsigned int window_width, SDL_Color bg_color);
    void render();
};

#endif //WINDOW_HPP_
