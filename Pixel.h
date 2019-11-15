struct Pixel
{
public:
    char channels[4];

    Pixel()
    {
        for (int i = 0; i < 4; ++i)
            channels[i] = 255;
    }

    void swap(char *channels)
    {
        //{ "AYUV", "VUYA", "ARGB", "BGRA", "RGB24" };
        for (int i = 0; i < 4; ++i)
            channels[i] = channels[i];
    }
};
