#include <QMap>
#include <QString>

class Config
{
public:
    Config(int32_t argc, QStringList &);

    bool isValid();

    QString inputFileName() const { return m_inputPath; }
    int32_t inputWidth() const { return m_inputWidth; }
    int32_t inputHeight() const { return m_inputHeight; }
    QString inputColorSpace() const { return m_inputColorspace; }

    QString outputFileName() const { return m_outputPath; }
    int32_t outputWidth() const { return m_outputWidth; }
    int32_t outputHeight() const { return m_outputHeight; }
    QString outputColorSpace() const { return m_outputColorspace; }

private:
    QMap<QString, QString> m_inputArgs;
    int32_t m_inputArgCount;

    QString m_inputPath;
    int32_t m_inputWidth;
    int32_t m_inputHeight;
    QString m_inputColorspace;

    QString m_outputPath;
    int32_t m_outputWidth;
    int32_t m_outputHeight;
    QString m_outputColorspace;
};
