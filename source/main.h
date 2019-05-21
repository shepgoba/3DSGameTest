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

#define CPAD_RIGHT 28
#define CPAD_LEFT 29
#define CPAD_UP 30
#define CPAD_DOWN 31

const float gravity = 0.4;
bool keys[32];


float clamp(float val, float min, float max)
{
    if (val > max)
    {
        return max;
    } else if (val < min) {
        return min;
    }

    return val;
}
