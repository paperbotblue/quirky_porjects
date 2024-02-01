#include <gWindow.hpp>

gWindow::gWindow(int height,int width,const char* windowTitle)
{
        {
            this->height = height;
            this->width = width;
            this->window = NULL;
            this->texture = NULL;
            this->renderer = NULL;

            if(SDL_Init(SDL_INIT_VIDEO) < 0)
            {
            printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
            }
            else
            {   
                this->window = SDL_CreateWindow(windowTitle,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,this->width,this->height,SDL_WINDOW_SHOWN);

                if(this->window == nullptr)
                {
                    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
                }
                else
                {
                    this->renderer = SDL_CreateRenderer(this->window,-1,SDL_RENDERER_ACCELERATED);
                    if(renderer == nullptr)
                    {
                        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                    }
                    else
                    {
                        SDL_SetRenderDrawColor(this->renderer,0xFF,0xFF,0xFF,0xFF);

                        int imgFlags = IMG_INIT_PNG;
                        if(!(IMG_Init(imgFlags)& imgFlags))
                        {
                            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                        }
                    }
                }
            }
        }
}



void gWindow::loadTexture(const char* file)
{   SDL_Texture* newTexture;
    SDL_Surface* tempSurface = IMG_Load(file);
    if(tempSurface == NULL)
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", file, IMG_GetError() );
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(this->renderer,tempSurface);
        SDL_FreeSurface(tempSurface);
        if(newTexture == NULL)
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", file, SDL_GetError() );
        }
        else
        {
            this->texture = newTexture;
            render();
        }
    }
}

void gWindow::render()
{
    SDL_SetRenderDrawColor(this->renderer,0x00,0x00,0x00,0xFF);         
    SDL_RenderClear( this->renderer );           
}

SDL_Renderer* gWindow::getRenderer()
{
    return this->renderer;
}

int gWindow::getWindowW()
{
    return this->width;
}

int gWindow::getWindowH()
{
    return this->height;
}

gWindow::~gWindow()
{
    SDL_DestroyTexture(this->texture);
    this->texture = NULL;
    SDL_DestroyWindow(this->window);
    this->window = nullptr;

    SDL_Quit();
}