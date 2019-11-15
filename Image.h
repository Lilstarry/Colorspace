#include "Pixel.h"

#include <QString>

class Image
{
public:
    Image(const int32_t width, const int32_t height, const QString &colorspace);
    ~Image();

    void imageImport(const QString &path);
    void imageExport(const QString &path);

    int32_t width() const { return m_width; }
    int32_t height() const { return m_height; }

    void transform(const QString &inputColorset, const QString &outputColorset);

    void RGB2RGB(const int *in, const int *out);
    void YUV2YUV(const int *in, const int *out);
    void YUV2RGB(const int *in, const int *out);
    void RGB2YUV(const int *in, const int *out);

private:
    Pixel *m_dots;
    int32_t m_channelsNumber;
    const int32_t m_width;
    const int32_t m_height;
};
