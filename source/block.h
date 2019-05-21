typedef struct Block {
    float x;
    float y;
    float width;
    float height;

    u32 color;
    int type;
} Block;
Block CreateBlock(float x, float y, float width, float height, int type)
{
    Block tmp;

    if (type == 1)
    {
        tmp.color = BLUE;
    } else {
        tmp.color = BLACK;
    }

    tmp.x = x;
    tmp.y = y;
    tmp.width = width;
    tmp.height = height;

    return tmp;
}

void DrawBlock(Block *b)
{
    C2D_DrawRectSolid(b->x, b->y, 1, b->width, b->height, b->color);
}

void CollideBlock(Block *b, Player *p)
{
    if (p->x + p->width > b->x && p->x < b->x + b->width && p->y + p->height > b->y && p->y < b->y + b->height)
    {
        if (p->yvel > 0)
        {
            p->yvel = 0;
            p->y = b->y - p->height;
            //printf("\x1b[2;1HCollision & player is falling\x1b[K", C3D_GetProcessingTime()*6.0f);
        }
    }
}
