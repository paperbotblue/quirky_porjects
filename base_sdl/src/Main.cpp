#include "./../inc/Main.hpp"

Main::Main()
{
    last_ticks = SDL_GetTicks();
    this->window_height = 720;
    this->window_width = 1080;
    this->bg_color = {0xFF, 0xFF, 0xFF, 0xFF};
    this->window = new Window("Window", this->window_height, this->window_width, this->bg_color);
}

void Main::fps_limiter()
{

}

void Main::game_loop()
{
  while (!quit) {
    if (SDL_GetTicks() - last_ticks < 1000/FPS) continue;
    
      while(SDL_PollEvent(&e) > 0)
        {
          if(e.type == SDL_QUIT) quit = true;
          else if(e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN) on_user_press();
          else if(e.type == SDL_KEYUP || e.type == SDL_MOUSEBUTTONUP) on_user_release();
        }
        main_loop();
        window->render();
      }            
    last_ticks = SDL_GetTicks();
}

void Main::main_loop()
{

}


void Main::on_user_press()
{

}

void Main::on_user_release()
{

}