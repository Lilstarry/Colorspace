#include "Config.h"

#include <QDebug>

const int ATTR_AMOUNT = 8;
const int32_t ARGS_AMOUNT = ATTR_AMOUNT * 2 + 1;
const QVector<QString> ATTRIBUTES = { "-i", "-iw", "-ih", "-ic", "-o", "-ow", "-oh", "-oc" };
const QSet<QString> COLORSPACES = { "AYUV", "VUYA", "ARGB", "BGRA", "RGB24" };
const QString IMG_DIR = "/images/";

bool Config::isValid()
{
    bool valid = true;

    if (m_inputArgs["-iw"] != m_inputArgs["-ow"])
    {
        qCritical() << "Invalid resolution. Input and output widths does not match\n";
        valid = false;
    }

    const QRegExp regNumber("\\d*");
    if (!regNumber.exactMatch(m_inputArgs["-iw"]))
    {
        qCritical() << "Error: input width is not a number\n";
        valid = false;
    }
    if (!regNumber.exactMatch(m_inputArgs["-ih"]))
    {
        qCritical() << "Error: input height is not a number\n";
        valid = false;
    }
    if (!regNumber.exactMatch(m_inputArgs["-ow"]))
    {
        qCritical() << "Error: output width is not a number\n";
        valid = false;
    }
    if (!regNumber.exactMatch(m_inputArgs["-oh"]))
    {
        qCritical() << "Error: output height is not a number\n";
        valid = false;
    }

    if (m_inputArgs["-ih"] != m_inputArgs["-oh"])
    {
        qCritical() << "Invalid resolution. Input and output heights does not match\n";
        valid = false;
    }
    if (COLORSPACES.find(m_inputArgs["-ic"]) == COLORSPACES.end())
    {
        qCritical() << "Invalid input colorspace\n";
        valid = false;
    }
    if (COLORSPACES.find(m_inputArgs["-oc"]) == COLORSPACES.end())
    {
        qCritical() << "Invalid output colorspace\n";
        valid = false;
    }
    if (m_inputArgs["-ic"] == m_inputArgs["-oc"])
    {
        qCritical() << "Colorspaces are the same\n";
        valid = false;
    }
    return valid;
}

Config::Config(int32_t argc, QStringList &args, QString &path)
    : m_inputArgCount(argc)
{
    //	Input data validation
    if (m_inputArgCount != ARGS_AMOUNT)
    {
        qCritical() << "Wrong number of arguments\n";
        exit(1);
    }

    for (int i = 0; i < ATTR_AMOUNT; ++i)
        m_inputArgs[ATTRIBUTES[i]] = "";

    if (m_inputArgs.size() != ATTR_AMOUNT)
    {
        qCritical() << "Wrong arguments.\nOnly this attributes are allowed:\n";
        for (int i = 0; i < ATTR_AMOUNT; ++i)
            qInfo() << ATTRIBUTES[i] << '\n';
        exit(1);
    }

    for (int i = 0; i < ATTR_AMOUNT; ++i)
    {
        QString key = args[1 + i * 2];
        QString value = args[1 + i * 2 + 1];
        m_inputArgs[key] = value;
    }

    bool ok;
    m_inputPath = path + IMG_DIR + m_inputArgs["-i"];
    m_inputWidth = m_inputArgs["-iw"].toInt(&ok, 10);
    m_inputHeight = m_inputArgs["-ih"].toInt(&ok, 10);
    m_inputColorspace = m_inputArgs["-ic"];
    m_outputPath = path + IMG_DIR + m_inputArgs["-o"];
    m_outputWidth = m_inputArgs["-ow"].toInt(&ok, 10);
    m_outputHeight = m_inputArgs["-oh"].toInt(&ok, 10);
    m_outputColorspace = m_inputArgs["-oc"];
}
