//cspaceedit.exe -i angel.rgb -iw 720 -ih 1080 -ic RGB24 -o argb.rgb -ow 720 -oh 1080 -oc ARGB
#include "Config.h"
#include "Image.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{

    Config config(argc, argv);
    if (!config.isValid())
        return 1;

//    Image inputImage(config.inputWidth(), config.inputHeight(), config.inputColorSpace());
//    inputImage.imageImport(config.inputFileName());
//    inputImage.transform(config.inputColorSpace(), config.outputColorSpace());
//    inputImage.imageExport(config.outputFileName());

    cout << "Done.\n";
    return 0;
}
