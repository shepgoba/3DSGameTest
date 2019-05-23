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

void CollideBlockY(Block *b, Player *p)
{
    if (p->x + p->width > b->x && p->x < b->x + b->width && p->y + p->height > b->y && p->y < b->y + b->height)
    {
        if (p->yvel > 0)
        {
            p->jumping = false;
            p->yvel = 0;
            p->y = b->y - p->height;
        }

        if (p->yvel < 0)
        {
            p->jumping = true;
            p->yvel = 0;
            p->y = b->y + b->height;
        }
    }
}

void CollideBlockX(Block *b, Player *p)
{
    if (p->x + p->width > b->x && p->x < b->x + b->width && p->y + p->height > b->y && p->y < b->y + b->height)
    {
        /*if (p->xvel > 0)
        {
            p->jumping = false;
            p->yvel = 0;
            p->y = b->y - p->height;
        }
        if (p->xvel < 0) {
            p->jumping = true;
            yvel = 0;
            p->y = b->y + b->height;
        }*/
    }
}
