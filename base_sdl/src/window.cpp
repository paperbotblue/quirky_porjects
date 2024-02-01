#include "./../inc/window.hpp"

Window::Window(char* window_title, unsigned int window_height, unsigned int window_width, SDL_Color bg_color)
{
  if(SDL_Init(SDL_INIT_VIDEO) != 0){PRINT("SDL FAILED TO INIT"); return;}
  this->window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN);
  if(window == nullptr){PRINT("SDL failed to create window"); return;}
  this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(renderer == nullptr){PRINT("SDL failed to create renderer"); return;}
  this->bg_color = bg_color;
  SDL_SetRenderDrawColor(this->renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
  SDL_RenderPresent(renderer);
}

void Window::render()
{
  SDL_RenderPresent(this->renderer);
  SDL_SetRenderDrawColor(this->renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
  SDL_RenderClear(this->renderer);
}