#include "Config.h"
#include "Image.h"

#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QString path = app.applicationDirPath();
    QStringList args = app.arguments();

    //  hardcode parameters
    QString inputLine = "TT_Remaster.exe -i SA.rgb -iw 720 -ih 1080 -ic RGB24 -o sa.yuv -ow 720 -oh 1080 -oc AYUV";
    args = inputLine.split(' ');
    argc = 17;
    //  end of the hardcode

    Config config(argc, args, path);

    if (!config.isValid())
        return 1;

    Image inputImage(config.inputWidth(), config.inputHeight(), config.inputColorSpace());
    inputImage.imageImport(config.inputFileName());
    inputImage.transform(config.inputColorSpace(), config.outputColorSpace());
    inputImage.imageExport(config.outputFileName());

    qInfo() << "\nDone.\n";

    return 0;
}
