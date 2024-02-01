struct line
{
    int x,y;
    int x1,y1;

    bool inBetween(line L2)
    {
        if(this->x >= L2.x && this->x1 <= L2.x1)
        {
            if(this->y >= L2.y && this->y1 <= L2.y1)

            {return true;}
        }

        return false;
    }
};


struct rectangleLine
{
    line lTop;
    line lDown;
    line lLeft;
    line lRight;
};
