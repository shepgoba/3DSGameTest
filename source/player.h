
typedef struct Player
{
    float x;
    float y;
    float width;
    float height;

    float xvel;
    float yvel;
    float xvelMin;
    float yvelMin;
    float xvelMax;
    float yvelMax;

    u32 color;
} Player;

Player CreatePlayer(float x, float y, float width, float height, u32 clr)
{
    Player tmp;
    tmp.x = x;
    tmp.y = y;
    tmp.width = width;
    tmp.height = height;

    tmp.xvel = 0;
    tmp.yvel = 0;
    tmp.xvelMin = -1;
    tmp.xvelMax = 1;
    tmp.yvelMin = -6;
    tmp.yvelMax = 6;

    tmp.color = clr;
    return tmp;
}

void DrawPlayer(Player *p)
{
    C2D_DrawRectSolid(p->x, p->y, 1, p->width, p->height, p->color);
}
void UpdatePlayer(Player *p)
{
    p->yvel += gravity;
    p->x += p->xvel;
    p->y += p->yvel;

    p->xvel = clamp(p->xvel, p->xvelMin, p->xvelMax);
    if (keys[29])
    {
        p->xvel -= 0.1;
    }
    if (keys[28])
    {
        p->xvel += 0.1;
    }

    if (!keys[29] && !keys[28])
    {
        p->xvel = 0;
    }
}
