#include "Image.h"

#include <QFile>
#include <QSet>
#include <QString>

#include <QDebug>

Image::Image(const int32_t width, const int32_t height, const QString &colorspace)
    : m_width(width)
    , m_height(height)
{
    if (colorspace == "RGB24")
        m_channelsNumber = 3;
    else
        m_channelsNumber = 4;
    /*
	else if (_colorspace == "AYUV") channelsNumber = 4;
	else if (_colorspace == "VUYA") channelsNumber = 4;
	else if (_colorspace == "ARGB") channelsNumber = 4;
	else if (_colorspace == "BGRA") channelsNumber = 4;
	*/

    m_dots = new Pixel[m_width * m_height];
}

Image::~Image()
{
    delete m_dots;
}

void Image::imageImport(const QString &path)
{
    QFile image(path);
    if(!image.open(QIODevice::ReadOnly))
    {
        qCritical() << "Unable to open input file";
        exit(1);
    }

    QByteArray blob = image.readAll();

    for(int i = 0; i < m_width * m_height; ++i)
    {
        for(int j = 0; j < m_channelsNumber; ++j)
            m_dots[i].channels[j] = blob[i * m_channelsNumber + j];
    }
}

void Image::imageExport(const QString &path)
{
    QFile image(path);
    if(!image.open(QIODevice::WriteOnly))
    {
        qCritical() << "Unable to open input file";
        exit(1);
    }

    QByteArray blob(m_width * m_height * m_channelsNumber, 0);
    for(int i = 0; i < m_width * m_height; ++i)
    {
        for(int j = 0; j < m_channelsNumber; ++j)
            blob[i * m_channelsNumber + j] = m_dots[i].channels[j];
    }

    image.write(blob);
}

void Image::transform(const QString &inputColorset, const QString &outputColorset)
{
    if (outputColorset == "RGB24")
        m_channelsNumber = 3;
    else
        m_channelsNumber = 4;

    // both of RGB class
    QSet<QString> RGB = { "RGB24", "ARGB", "BGRA" };
    QSet<QString> YUV = { "AYUV", "VUYA" };
    //	Let's make some swappers.
    //	Swappers will define channels' order
    //	RGBA is 0123, it's ok. But ABGR is 3210.
    //	So we have RGBA and YUVA patterns, which are 0123 for self classes
    if (RGB.contains(inputColorset))
    {
        //Input rgb swapper
        int swapper_In[4] = { 0, 1, 2, 3 };
        if (inputColorset == "ARGB")
        {
            swapper_In[0] = 3;
            swapper_In[1] = 0;
            swapper_In[2] = 1;
            swapper_In[3] = 2;
        }
        else if (inputColorset == "BGRA")
        {
            swapper_In[0] = 2;
            swapper_In[1] = 1;
            swapper_In[2] = 0;
            swapper_In[3] = 3;
        }
        //	Output is RGB
        if (RGB.find(outputColorset) != RGB.end())
        {
            int swapper_Out[4] = { 0, 1, 2, 3 };
            if (outputColorset == "ARGB")
            {
                swapper_Out[0] = 3;
                swapper_Out[1] = 0;
                swapper_Out[2] = 1;
                swapper_Out[3] = 2;
            }
            else if (outputColorset == "BGRA")
            {
                swapper_Out[0] = 2;
                swapper_Out[1] = 1;
                swapper_Out[2] = 0;
                swapper_Out[3] = 3;
            }
            RGB2RGB(swapper_In, swapper_Out);
        }

        //	Output is YUV
        else if (YUV.find(outputColorset) != YUV.end())
        {
            int swapper_Out[4] = { 0, 1, 2, 3 };
            if (outputColorset == "AYUV")
            {
                swapper_Out[0] = 3;
                swapper_Out[1] = 0;
                swapper_Out[2] = 1;
                swapper_Out[3] = 2;
            }
            else if (outputColorset == "VUYA")
            {
                swapper_Out[0] = 2;
                swapper_Out[1] = 1;
                swapper_Out[2] = 0;
                swapper_Out[3] = 3;
            }
            RGB2YUV(swapper_In, swapper_Out);
        }
    }
    else
    {
        //	Input yuv swapper
        int swapper_In[4] = { 0, 1, 2, 3 };
        if (inputColorset == "AYUV")
        {
            swapper_In[0] = 3;
            swapper_In[1] = 0;
            swapper_In[2] = 1;
            swapper_In[3] = 2;
        }
        else if (inputColorset == "VUYA")
        {
            swapper_In[0] = 2;
            swapper_In[1] = 1;
            swapper_In[2] = 0;
            swapper_In[3] = 3;
        }
        //	Output is YUV
        if (YUV.find(outputColorset) != YUV.end())
        {
            int swapper_Out[4] = { 0, 1, 2, 3 };
            if (outputColorset == "AYUV")
            {
                swapper_Out[0] = 3;
                swapper_Out[1] = 0;
                swapper_Out[2] = 1;
                swapper_Out[3] = 2;
            }
            else if (outputColorset == "VUYA")
            {
                swapper_Out[0] = 2;
                swapper_Out[1] = 1;
                swapper_Out[2] = 0;
                swapper_Out[3] = 3;
            }
            YUV2YUV(swapper_In, swapper_Out);
        }
        //	Output is RGB
        else if (RGB.find(outputColorset) != RGB.end())
        {
            int swapper_Out[4] = { 0, 1, 2, 3 };
            if (outputColorset == "ARGB")
            {
                swapper_Out[0] = 3;
                swapper_Out[1] = 0;
                swapper_Out[2] = 1;
                swapper_Out[3] = 2;
            }
            else if (outputColorset == "BGRA")
            {
                swapper_Out[0] = 2;
                swapper_Out[1] = 1;
                swapper_Out[2] = 0;
                swapper_Out[3] = 3;
            }
            YUV2RGB(swapper_In, swapper_Out);
        }
    }
}

void Image::RGB2RGB(const int *in, const int *out)
{
    Pixel temp;
    for (int i = 0; i < m_width * m_height; ++i)
    {
        for (int j = 0; j < 4; ++j)
            temp.channels[in[j]] = m_dots[i].channels[j];
        for (int j = 0; j < 4; ++j)
            m_dots[i].channels[j] = temp.channels[out[j]];
    }
}

void Image::YUV2YUV(const int *in, const int *out)
{
    Pixel temp;
    for (int i = 0; i < m_width * m_height; ++i)
    {
        for (int j = 0; j < 4; ++j)
            temp.channels[in[j]] = m_dots[i].channels[j];
        for (int j = 0; j < 4; ++j)
            m_dots[i].channels[j] = temp.channels[out[j]];
    }
}

void Image::YUV2RGB(const int *in, const int *out)
{
    Pixel temp_RGB;
    Pixel temp_YUV;
    int r, g, b;
    for (int i = 0; i < m_width * m_height; ++i)
    {
        for (int j = 0; j < 4; ++j)
            temp_YUV.channels[in[j]] = m_dots[i].channels[j];

        r = temp_YUV.channels[0] + 1.4 * (temp_YUV.channels[2] - 128);
        if (r < 0)
        {
            r = 0;
        }
        else if (r > 255)
        {
            r = 255;
        }
        temp_RGB.channels[0] = r;

        g = temp_YUV.channels[0] - 0.343 * (temp_YUV.channels[1] - 128) - 0.711 * (temp_YUV.channels[2] - 128);
        if (g < 0)
        {
            g = 0;
        }
        else if (g > 255)
        {
            g = 255;
        }
        temp_RGB.channels[1] = g;

        b = temp_YUV.channels[0] + 1.765 * (temp_YUV.channels[1] - 128);
        if (b < 0)
        {
            b = 0;
        }
        else if (b > 255)
        {
            b = 255;
        }
        temp_RGB.channels[2] = b;

        temp_RGB.channels[3] = temp_YUV.channels[3];

        for (int j = 0; j < 4; ++j)
            m_dots[i].channels[j] = temp_RGB.channels[out[j]];
    }
}

void Image::RGB2YUV(const int *in, const int *out)
{
    Pixel temp_RGB;
    Pixel temp_YUV;
    int Y, U, V;

    for (int i = 0; i < m_width * m_height; ++i)
    {
        for (int j = 0; j < 4; ++j)
            temp_RGB.channels[in[j]] = m_dots[i].channels[j];

        Y = temp_RGB.channels[1];
        temp_YUV.channels[0] = Y;

        U = -0.169 * temp_RGB.channels[0] - 0.331 * temp_RGB.channels[1] + 0.500 * temp_RGB.channels[2] + 128;
        temp_YUV.channels[1] = U;

        V = 0.500 * temp_RGB.channels[0] - 0.419 * temp_RGB.channels[1] - 0.081 * temp_RGB.channels[2] + 128;
        temp_YUV.channels[2] = V;

        temp_YUV.channels[3] = temp_RGB.channels[3];

        for (int j = 0; j < 4; ++j)
            m_dots[i].channels[j] = temp_YUV.channels[out[j]];
    }
}
