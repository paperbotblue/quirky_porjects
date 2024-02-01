#include "./../inc/Main.hpp"
#include <raylib.h>

Main::Main()
{
  this->window_width = 1980;
  this->window_height = 1080;

  cp = new Circle_Pool(window_width, window_height, 400);

  this->running = true;
  InitWindow(window_width, window_height, "Falling Circles");
  SetTargetFPS(60);
}

void Main::main_loop()
{
  BeginDrawing();
  // the constraint circle
  DrawCircle(window_width/2, window_height/2, 400, WHITE); 
  
  cp->render_circles();

  ClearBackground(BLACK); 
  EndDrawing();
}

void Main::event_loop()
{
  if(IsKeyPressed(KEY_A))
  {
    cp->create_circle((float)mouseX , (float)mouseY, 30, PINK);
  }
}

void Main::run()
{
  while(!WindowShouldClose())
  {
    mouseX = GetMouseX();
    mouseY = GetMouseY();

    event_loop();
    main_loop();
  }
}

Main::~Main()
{
  CloseWindow();
}
