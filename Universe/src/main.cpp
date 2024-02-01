#include <iostream>
#include <vector>
#include "../inc/Window.h"


int roundUpToMultipleOfEight( int v )
{
    return (v + (8 - 1)) & -8;
}
void DrawCircle(SDL_Renderer * renderer,SDL_Color colour, int32_t centreX,int32_t  centreY, int32_t radius)
{
    // 35 / 49 is a slightly biased approximation of 1/sqrt(2)
        SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
        SDL_Point center = {centreX, centreY};
        const int arrSize = roundUpToMultipleOfEight(radius * 8 * 35 / 49);
        SDL_Point points[arrSize];
        int drawCount = 0;

        const int32_t diameter = (radius * 2);

        int32_t x = (radius - 1);
        int32_t y = 0;
        int32_t tx = 1;
        int32_t ty = 1;
        int32_t error = (tx - diameter);

        while (x >= y) {
            // Each of the following renders an octant of the circle
            points[drawCount + 0] = {center.x + x, center.y - y};
            points[drawCount + 1] = {center.x + x, center.y + y};
            points[drawCount + 2] = {center.x - x, center.y - y};
            points[drawCount + 3] = {center.x - x, center.y + y};
            points[drawCount + 4] = {center.x + y, center.y - x};
            points[drawCount + 5] = {center.x + y, center.y + x};
            points[drawCount + 6] = {center.x - y, center.y - x};
            points[drawCount + 7] = {center.x - y, center.y + x};

            drawCount += 8;

            if (error <= 0) {
                ++y;
                error += ty;
                ty += 2;
            }

            if (error > 0) {
                --x;
                tx += 2;
                error += (tx - diameter);
            }
        }

        SDL_RenderDrawPoints(renderer, points, drawCount);
}



void DrawCircleF(SDL_Renderer * renderer,SDL_Color colour, int32_t centreX,int32_t  centreY, int32_t radius)
{
    // 35 / 49 is a slightly biased approximation of 1/sqrt(2)
    while(radius > 0)
    {
        SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
        SDL_Point center = {centreX, centreY};
        const int arrSize = roundUpToMultipleOfEight(radius * 8 * 35 / 49);
        SDL_Point points[arrSize];
        int drawCount = 0;

        const int32_t diameter = (radius * 2);

        int32_t x = (radius - 1);
        int32_t y = 0;
        int32_t tx = 1;
        int32_t ty = 1;
        int32_t error = (tx - diameter);

        while (x >= y) {
            // Each of the following renders an octant of the circle
            points[drawCount + 0] = {center.x + x, center.y - y};
            points[drawCount + 1] = {center.x + x, center.y + y};
            points[drawCount + 2] = {center.x - x, center.y - y};
            points[drawCount + 3] = {center.x - x, center.y + y};
            points[drawCount + 4] = {center.x + y, center.y - x};
            points[drawCount + 5] = {center.x + y, center.y + x};
            points[drawCount + 6] = {center.x - y, center.y - x};
            points[drawCount + 7] = {center.x - y, center.y + x};

            drawCount += 8;

            if (error <= 0) {
                ++y;
                error += ty;
                ty += 2;
            }

            if (error > 0) {
                --x;
                tx += 2;
                error += (tx - diameter);
            }
        }

        SDL_RenderDrawPoints(renderer, points, drawCount);
        radius--;
    }
}


struct Vector
{
    int x,y;
    Vector operator+(Vector &v) const
    {
        Vector c{};
        c.x = this->x+v.x;
        c.y = this->y+v.y;
        return c;
    }

};

constexpr SDL_Color starColours[8] =
        {
                {0xFF,0xFF,0xFF,0xFF},
                {0xFF,0xD9,0xFF,0xFF},
                {0xFF,0xA3,0xFF,0xFF},
                {0xFF,0xFF,0xC8,0xC8},
                {0xFF,0xFF,0xCB,0x9D},
                {0xFF,0x9F,0x9F,0xFF},
                {0xFF,0x41,0x5E,0xFF},
                {0xFF,0x28,0x19,0x9D}
        };

struct sPlanet
{
    double distance = 0.0;
    SDL_Color colour = {0xFF,0xFF,0xFF,0xFF};
    double radius = 0.0;
    double foliage = 0.0;
    double minerals = 0.0;
    double water = 0.0;
    double gases = 0.0;
    double temperature = 0.0;
    double population = 0.0;
    bool ring = false;
    std::vector<double> vMoons;
};

class starSystem {
public:
    uint32_t nLehmer = 0;
    bool starExists = false;
    SDL_Color starColour;
    std::vector<sPlanet> vPlanets;
    double starDiameter = 0.0f;
    SDL_Color White = {0xFF, 0xFF, 0xFF, 0xFF};

    starSystem(uint32_t x, uint32_t y, bool bGenerateFullSystem = false) {
        nLehmer = (x & 0xFFFF) << 16 | (y & 0xFFFF);

        starExists = (randInt(0, 30) == 1);
        if (!starExists) return;

        starDiameter = randDouble(10.0f, 40.0f);
        starColour = starColours[randInt(0, 7)];
        if(!bGenerateFullSystem) return;

        double dDistanceFromStar = randDouble(60.0,200.0);
        int nPlanets = randInt(0,10);
        for(int i = 0 ; i < nPlanets ;i++)
        {
            sPlanet p;
            p.distance = dDistanceFromStar;
            dDistanceFromStar += randDouble(20.0,200.0);
            p.radius = randDouble(2.0,10.0);
            p.temperature = randDouble(-200.0,300.0);
            p.ring = randInt(0,10) == 1;
            int nMoons = std::max(randInt(-5,5),0);
            for(int j = 0 ; j<  nMoons ; j++)
            {
                p.vMoons.push_back(randDouble(1.0,5.0));
            }
            vPlanets.push_back(p);
        }
    }

private:

    uint32_t Lehmer32() {
        nLehmer += 0xe120fc15;
        uint64_t tmp;
        tmp = (uint64_t) nLehmer * 0x4a39b70d;
        uint32_t m1 = (tmp >> 32) ^ tmp;
        tmp = (uint64_t) m1 * 0x12fad5c9;
        uint32_t m2 = (tmp >> 32) ^ tmp;
        return m2;
    }

    int randInt(int min, int max) {
        return (Lehmer32() % (max - min)) + min;
    }

    double randDouble(double min, double max) {
        return (Lehmer32() / (double) (0x7FFFFFFFF)) * (max - min) + min;
    }
};
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
Vector vGalaxyOffSet = { 0,0 };
bool bStarSelected = false;
Vector vStarSelected{0,0};


int main() {
    Window *gameWindow = new Window(WINDOW_WIDTH, WINDOW_HEIGHT);
    int nSectorsX = WINDOW_WIDTH/16;
    int nSectorsY = WINDOW_HEIGHT/16;
    Vector galaxyMouse;
    Vector vMouse{};
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) > 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_w: vGalaxyOffSet.y -= 2; break;
                    case SDLK_s: vGalaxyOffSet.y += 2; break;
                    case SDLK_a: vGalaxyOffSet.x -= 2; break;
                    case SDLK_d: vGalaxyOffSet.x += 2; break;

                    case SDLK_0:
                        starSystem star(galaxyMouse.x,galaxyMouse.y);
                        if(star.starExists)
                        {
                            bStarSelected = true;
                            vStarSelected = galaxyMouse;
                        }
                        else
                        {
                            bStarSelected = false;
                        }
                }

            }
        }
        gameWindow->windowRender();

        SDL_GetMouseState(&vMouse.x,&vMouse.y);
        vMouse.x = vMouse.x/16;
        vMouse.y = vMouse.y/16;

        galaxyMouse = vMouse + vGalaxyOffSet;
        Vector screenSector = { 0,0 };
        for(screenSector.x = 0 ; screenSector.x < nSectorsX ; screenSector.x++ )
            for(screenSector.y = 0 ; screenSector.y < nSectorsY ; screenSector.y++)
            {
                starSystem star(screenSector.x + vGalaxyOffSet.x ,screenSector.y + vGalaxyOffSet.y);
                if(star.starExists)
                {
                    DrawCircleF( gameWindow->getRenderer(),star.starColour,screenSector.x*16 + 8,screenSector.y*16 + 8,(int)star.starDiameter/2);
                    if(vMouse.x == screenSector.x && vMouse.y == screenSector.y)
                    {
                        DrawCircle(gameWindow->getRenderer(),star.starColour,screenSector.x*16+8,screenSector.y*16+8,(int)star.starDiameter/2+10);
                    }
                }
            }
        if(bStarSelected)
        {
            SDL_SetRenderDrawColor(gameWindow->getRenderer(),0x00,0x00,0xFF,0xFF);
            SDL_Rect p = {0,WINDOW_HEIGHT/2-10,WINDOW_WIDTH,10};
            SDL_RenderFillRect(gameWindow->getRenderer(),&p);
            starSystem star(vStarSelected.x,vStarSelected.y,true);
            SDL_SetRenderDrawColor(gameWindow->getRenderer(), 0x00,0x00,0x00,0xFF);
            SDL_Rect r = {0,WINDOW_HEIGHT/2,WINDOW_WIDTH,WINDOW_HEIGHT};
            SDL_RenderFillRect(gameWindow->getRenderer(),&r);

            SDL_SetRenderDrawColor(gameWindow->getRenderer(), 0xFF,0xFF,0xFF,0xFF);
            srand(vStarSelected.x+vStarSelected.y);
            for(int i = WINDOW_HEIGHT/2 ; i < WINDOW_HEIGHT ; i++)
            {
                for(int j = 0 ; j < WINDOW_WIDTH ; j++)
                {
                    if(rand()%5000 < 5)
                    {
                        SDL_RenderDrawPoint(gameWindow->getRenderer(),j,i);
                    }
                }
            }

            DrawCircleF(gameWindow->getRenderer(),star.starColour,(int)star.starDiameter*10+20,WINDOW_HEIGHT/2+WINDOW_HEIGHT/4,(int)star.starDiameter*10);
            SDL_Color WHITE = {0xFF,0xFF,0xFF,0xFF};
            SDL_Color GRAY = {0xAA,0xAA,0xAA,0xFF};

            SDL_SetRenderDrawColor(gameWindow->getRenderer(),0xFF,0xFF,0xFF,0xFF);
            int dist = 0;
            for(int i = 0 ; i < (int)star.vPlanets.size(); i++)
            {
                DrawCircleF(gameWindow->getRenderer(),WHITE,(int)((10*(star.starDiameter)+star.vPlanets[i].distance*3+star.vPlanets[i].radius*10)+20),WINDOW_HEIGHT/2+WINDOW_HEIGHT/4,star.vPlanets[i].radius*10);
                for(int j = 0 ; j  < star.vPlanets[i].vMoons.size() ; j++)
                {
                    DrawCircleF(gameWindow->getRenderer(),GRAY,(int)((10*(star.starDiameter)+star.vPlanets[i].distance*3+star.vPlanets[i].radius*10)+20),WINDOW_HEIGHT/2+WINDOW_HEIGHT/4+star.vPlanets[i].vMoons[i]+star.vPlanets[i].radius+50+dist,star.vPlanets[i].vMoons[j]*10);
                    dist+=star.vPlanets[i].radius+50;
                }
            }

        }


        SDL_RenderPresent(gameWindow->getRenderer());
    }

}
