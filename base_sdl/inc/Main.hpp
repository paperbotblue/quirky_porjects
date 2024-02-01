#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <iostream>
#include <SDL2/SDL.h>
#include "./window.hpp"
#include "./utils.hpp"

#define FPS 60

class Main
{
  private:
    int last_ticks;
    unsigned int window_height, window_width;
    SDL_Color bg_color;
    Window* window;
    SDL_Event e;
    bool quit = false;

  public:
    Main();
    void main_loop();
    void game_loop();
    void fps_limiter();
    void on_user_press();
    void on_user_release();
};

#endif //MAIN_HPP_