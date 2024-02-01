#ifndef PAINT_V0_2_SHAPES_H
#define PAINT_V0_2_SHAPES_H

int roundUpToMultipleOfEight( int v )
{
    return (v + (8 - 1)) & -8;
}

void DrawCircle(SDL_Renderer * renderer, int32_t centreX,int32_t  centreY, int32_t radius)
{
    // 35 / 49 is a slightly biased approximation of 1/sqrt(2)
    SDL_Point center = {centreX, centreY};
    const int arrSize = roundUpToMultipleOfEight(radius * 5.714285712857);
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



struct vector2
{
    SDL_Point a;
    SDL_Point b;
};

class Shapes{
public:
    static void ghostShapes(SDL_Renderer* renderer, int key, vector2* a);
    static void drawPoints(SDL_Renderer* renderer, std::vector<SDL_Point>* a);
    static void drawLine(SDL_Renderer* renderer, std::vector<vector2>* a);
    static void drawRect(SDL_Renderer* renderer, std::vector<vector2>* a);
    static void drawCircle(SDL_Renderer* renderer, std::vector<vector2>* a);
};

void Shapes::ghostShapes(SDL_Renderer* renderer, int key, vector2* a)
{
    switch (key)
    {
        case 1:
            SDL_RenderDrawLine(renderer,a->a.x,a->a.y,a->b.x,a->b.y);
            break;
        case 2:
            SDL_Rect r;
            r.x = a->a.x;
            r.y = a->a.y;
            r.w = a->b.x - a->a.x;
            r.h = a->b.y - a->a.y;
            SDL_RenderDrawRect(renderer, &r);
            break;
        case 3:
            int radius;
            radius = a->b.x - a->a.x;
            radius = radius < 0 ? radius*=-1 : radius;
            DrawCircle(renderer,a->a.x,a->a.y,radius);
            break;
    }
}

void Shapes::drawPoints(SDL_Renderer* renderer,std::vector<SDL_Point>* a)
{
    for(auto& point : *a)
    {
        SDL_RenderDrawPoint(renderer,point.x,point.y);
        SDL_RenderDrawPoint(renderer,point.x+1,point.y);
        SDL_RenderDrawPoint(renderer,point.x-1,point.y);
        SDL_RenderDrawPoint(renderer,point.x,point.y+1);
        SDL_RenderDrawPoint(renderer,point.x,point.y-1);
    }
}

void Shapes::drawLine(SDL_Renderer* renderer,std::vector<vector2>* a)
{
    for(auto& Line: *a)
    {
        SDL_RenderDrawLine(renderer,Line.a.x,Line.a.y,Line.b.x,Line.b.y);
    }
}

void Shapes::drawRect(SDL_Renderer *renderer, std::vector<vector2> *a)
{
    SDL_Rect r = {};
    for(auto& Rect: *a)
    {
        r.x = Rect.a.x;
        r.y = Rect.a.y;
        r.w = Rect.b.x-Rect.a.x;
        r.h = Rect.b.y-Rect.a.y;
        SDL_RenderDrawRect(renderer,&r);
    }
}


void Shapes::drawCircle(SDL_Renderer *renderer, std::vector<vector2> *a)
{
    int r;
    for(auto& Circle: *a)
    {
        r = Circle.b.x - Circle.a.x;
        r = r < 0 ? r*=-1 : r;
        DrawCircle(renderer,Circle.a.x,Circle.a.y,r);
    }
}

#endif //PAINT_V0_2_SHAPES_H
