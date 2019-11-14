#include <map>
#include <string>

using namespace std;

class Config
{
public:
    Config(int32_t argc, char **args);

    bool isValid();

    string inputFileName() const { return m_inputPath; }
    int32_t inputWidth() const { return m_inputWidth; }
    int32_t inputHeight() const { return m_inputHeight; }
    string inputColorSpace() const { return m_inputColorspace; }

    string outputFileName() const { return m_outputPath; }
    int32_t outputWidth() const { return m_outputWidth; }
    int32_t outputHeight() const { return m_outputHeight; }
    string outputColorSpace() const { return m_outputColorspace; }

private:
    bool isNumber(string s);
    int32_t toNumber(string s);

private:
    map<string, string> m_inputArgs;
    int32_t m_inputArgCount;

    string m_inputPath;
    int32_t m_inputWidth;
    int32_t m_inputHeight;
    string m_inputColorspace;

    string m_outputPath;
    int32_t m_outputWidth;
    int32_t m_outputHeight;
    string m_outputColorspace;
};
