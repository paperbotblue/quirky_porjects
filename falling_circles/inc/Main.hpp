#include <raylib.h>
#include "./Circle.hpp"

class Main 
{
  private: 
    bool running;
    unsigned int window_width,window_height;    
    Circle_Pool* cp;      
    int mouseX, mouseY;
  public:
    Main();

    void run();
    void main_loop();
    void event_loop();

    ~Main();
};
