
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
