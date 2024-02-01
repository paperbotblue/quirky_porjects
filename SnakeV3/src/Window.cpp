#include "/sharedDrive/Project/SnakeV3/inc/window.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstddef>
#include <cstdio>

Window::Window(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
  this->gWindow = NULL;
  this->gRenderer = NULL;
  this->gTexture = NULL;
  this->WINDOW_WIDTH = WINDOW_WIDTH;
  this->WINDOW_HEIGHT = WINDOW_HEIGHT;

  if(SDL_Init(SDL_INIT_VIDEO) == 0)
  {
    this->gWindow = SDL_CreateWindow("SnakeV3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(this->gWindow == NULL)
    {
      printf("Unable to create window SDL_ERROR: %s",SDL_GetError()); 
    }
    else 
    {
      printf("success");
      this->gRenderer = SDL_CreateRenderer(this->gWindow, -1, SDL_RENDERER_ACCELERATED);
      if(this->gRenderer == NULL)
      {
      printf("Unable to create renderer SDL_ERROR: %s",SDL_GetError()); 
      }
      else
      {
      SDL_SetRenderDrawColor(this->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderPresent(this->gRenderer);
      }
    }
    
  }
  else 
  {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
  }
}

SDL_Window* Window::getWindow()
{
  return this->gWindow;
}
SDL_Renderer* Window::getRenderer()
{
  return this->gRenderer;
}

void Window::windowRender()
{
  SDL_SetRenderDrawColor(this->gRenderer, 0x28, 0x28, 0x28, 0xFF);
  SDL_RenderPresent(this->gRenderer);  
  SDL_RenderClear(this->gRenderer);
}
