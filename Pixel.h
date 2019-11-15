typedef unsigned char uchar;

struct Pixel
{
public:
    uchar channels[4];

    Pixel();

    void swap(char *channels);
};
