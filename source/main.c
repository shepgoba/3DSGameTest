#include <citro2d.h>
#include <3ds.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240
#define WORLD_WIDTH 40
#define WORLD_HEIGHT 24

#define WHITE C2D_Color32(255, 255, 255, 255)
#define GREEN C2D_Color32(36, 158, 0, 255)
#define RED C2D_Color32(230, 0, 0, 255)
#define BLUE C2D_Color32(7, 50, 119, 255)
#define YELLOW C2D_Color32(255, 255, 0, 255)
#define BLACK C2D_Color32(0, 0, 0, 255)

const float gravity = 0.4;
bool keys[32];

typedef struct
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
    tmp.xvelMin = -8;
    tmp.xvelMax = 8;
    tmp.yvelMin = -8;
    tmp.yvelMax = 8;

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

    if (keys[KEY_CPAD_LEFT])
    {
        p->xvel -= 0.1;
    }
    if (keys[KEY_CPAD_RIGHT])
    {
        p->xvel += 0.1;
    }
}

typedef struct {
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
    if (p->x + p->width > b->x && p->x > b->x + b->width && p->y + p->height > b->y && p->y < b->y + b->height)
    {
        if (p->yvel > 0)
        {
            p->yvel = 0;
            p->y = b->y - p->height;
            //printf("\x1b[2;1HCollision & player is falling\x1b[K", C3D_GetProcessingTime()*6.0f);
        }
    }
}

int world[WORLD_HEIGHT][WORLD_WIDTH] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
};

void handleKeyPresses(u32 *kDown, u32 *kUp, bool k[32])
{
    for (int i = 0; i < 32; i++)
    {
        if (*kDown & BIT(i))
        {
            k[i] = true;
        }
        if (*kUp & BIT(i))
        {
            k[i] = false;
        }
    }
}

int main(int argc, char* argv[])
{
    const u32 clrClear = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);

    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    consoleInit(GFX_BOTTOM, NULL);

    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

    Player player = CreatePlayer(20, 20, 10, 20, RED);

    int blockCount = 0;
    Block blocks[WORLD_WIDTH * WORLD_HEIGHT];
    for (int y = 0; y < WORLD_HEIGHT; y++)
    {
        for (int x = 0; x < WORLD_WIDTH; x++)
        {
            if (world[y][x] == 1)
            {
                blocks[blockCount] = CreateBlock(x * 10, y * 10, 10, 10, 1);
                blockCount++;
            }
        }
    }

    while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
        u32 kUp = hidKeysUp();

        handleKeyPresses(&kDown, &kUp, keys);

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, clrClear);
		C2D_SceneBegin(top);

        UpdatePlayer(&player);
        DrawPlayer(&player);

        for (int i = 0; i < blockCount; i++)
        {
            DrawBlock(&blocks[i]);
            CollideBlock(&blocks[i], &player);
        }
		C3D_FrameEnd(0);

        //printf("\x1b[2;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime()*6.0f);
		//printf("\x1b[3;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime()*6.0f);
		//printf("\x1b[4;1HCmdBuf:  %6.2f%%\x1b[K", C3D_GetCmdBufUsage()*100.0f);

	}

	C2D_Fini();
	C3D_Fini();
	gfxExit();

    return 0;
}
