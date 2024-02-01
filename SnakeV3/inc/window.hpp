#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

class Window
{
  private:
  SDL_Window* gWindow;
  SDL_Renderer* gRenderer;
  SDL_Texture* gTexture;

  public:
  int WINDOW_HEIGHT;
  int WINDOW_WIDTH;
  Window(int WINDOW_WIDTH, int WINDOW_HEIGH);
  void windowRender();
  SDL_Window* getWindow();
  SDL_Renderer* getRenderer();
};
#endif // !WINDOW_HPP

