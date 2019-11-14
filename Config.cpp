#include "Config.h"

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

/*	8 attributes
    8 values
    1 arg is program name	*/
const int32_t ARGS_AMOUNT = 8 * 2 + 1;
const int ATTR_AMOUNT = 8;
const vector<string> ATTRIBUTES = { "-i", "-iw", "-ih", "-ic", "-o", "-ow", "-oh", "-oc" };
const set<string> COLORSPACES = { "AYUV", "VUYA", "ARGB", "BGRA", "RGB24" };
static string INPUT_PATH = "C:\\Users\\Lilstarry\\source\\repos\\cspaceedit\\Debug\\images-input\\";
static string OUTPUT_PATH = "C:\\Users\\Lilstarry\\source\\repos\\cspaceedit\\Debug\\images-output\\";

bool Config::isNumber(string s)
{
    for (size_t i = 0; i < s.length(); ++i)
        if (s[i] < '0' || s[i] > '9')
            return false;
    return true;
}

int Config::toNumber(string s)
{
    int multiplier = 1;
    int result = 0;
    for (int i = s.length() - 1; i >= 0; --i)
    {
        result += (s[i] - '0') * multiplier;
        multiplier *= 10;
    }
    return result;
}

bool Config::isValid()
{
    if (m_inputArgCount != ARGS_AMOUNT)
    {
        cout << "Wrong number of arguments\n";
        return false;
    }
    if (m_inputArgs.size() != ATTR_AMOUNT)
    {
        cout << "Wrong arguments.\nOnly this attributes are allowed:\n";
        for (int i = 0; i < ATTR_AMOUNT; ++i)
            cout << ATTRIBUTES[i] << '\n';
        return false;
    }
    bool valid = true;
    if (m_inputArgs["-iw"] != m_inputArgs["-ow"])
    {
        cout << "Invalid resolution. Input and output widths does not match\n";
        valid = false;
    }
    if (!isNumber(m_inputArgs["-iw"]))
    {
        cout << "Error: input width is not a number\n";
        valid = false;
    }
    if (!isNumber(m_inputArgs["-ih"]))
    {
        cout << "Error: input height is not a number\n";
        valid = false;
    }
    if (!isNumber(m_inputArgs["-ow"]))
    {
        cout << "Error: output width is not a number\n";
        valid = false;
    }
    if (!isNumber(m_inputArgs["-oh"]))
    {
        cout << "Error: output height is not a number\n";
        valid = false;
    }
    if (m_inputArgs["-ih"] != m_inputArgs["-oh"])
    {
        cout << "Invalid resolution. Input and output heights does not match\n";
        valid = false;
    }
    if (COLORSPACES.find(m_inputArgs["-ic"]) == COLORSPACES.end())
    {
        cout << "Invalid input colorspace\n";
        valid = false;
    }
    if (COLORSPACES.find(m_inputArgs["-oc"]) == COLORSPACES.end())
    {
        cout << "Invalid output colorspace\n";
        valid = false;
    }
    if (m_inputArgs["-ic"] == m_inputArgs["-oc"])
    {
        cout << "Colorspaces are the same\n";
        valid = false;
    }
    return valid;
}

Config::Config(int32_t argc, char **args)
    : m_inputArgCount(argc)
{
    //	Input data validation
    for (size_t i = 0; i < ATTR_AMOUNT; ++i)
        m_inputArgs[ATTRIBUTES[i]] = "";

    for (int i = 0; i < ATTR_AMOUNT; ++i)
    {
        string key = args[1 + i * 2];
        string value = args[1 + i * 2 + 1];
        m_inputArgs[key] = value;
    }
    //	builder
    m_inputPath = INPUT_PATH + m_inputArgs["-i"];
    m_inputWidth = toNumber(m_inputArgs["-iw"]);
    m_inputHeight = toNumber(m_inputArgs["-ih"]);
    m_inputColorspace = m_inputArgs["-ic"];
    m_outputPath = OUTPUT_PATH + m_inputArgs["-o"];
    m_outputWidth = toNumber(m_inputArgs["-ow"]);
    m_outputHeight = toNumber(m_inputArgs["-oh"]);
    m_outputColorspace = m_inputArgs["-oc"];
}
