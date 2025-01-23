#include "common_funcs.hh"

namespace libprcpp
{

bool isNumeric(const std::string &str)
{
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

bool getArgMainValue(int argc, char *argv[], int &i, std::string &value, const std::string &defaultValue)
{
    if (i + 1 < argc && argv[i + 1][0] != '-') // check if next is not another flag
    {
        value = argv[++i];
        return true;
    }
    else if (!defaultValue.empty())
    {
        value = defaultValue;
        return true;
    }
    return false;
}

bool inputEndsWith(const std::string &input, const std::string &checkWith)
{
    if (input.length() < checkWith.length())
    {
        return false;
    }
    return input.compare(input.length() - checkWith.length(), checkWith.length(), checkWith) == 0;
}

bool parseSizeArg(const std::string &sizeStr, i32 &width, i32 &height)
{
    // check if the string contains exactly one 'x'
    size_t xPos = sizeStr.find('x');
    if (xPos == std::string::npos || xPos == 0 || xPos == sizeStr.length() - 1)
    {
        return false; // no 'x' found, or 'x' is at the beginning/end
    }

    // split the string into width and height parts
    std::string widthStr = sizeStr.substr(0, xPos);
    std::string heightStr = sizeStr.substr(xPos + 1);

    // check if both parts are numeric
    for (char c : widthStr)
    {
        if (!isdigit(c))
        {
            return false; // non-numeric character in width
        }
    }
    for (char c : heightStr)
    {
        if (!isdigit(c))
        {
            return false; // non-numeric character in height
        }
    }

    // convert the strings to integers
    width = std::stoi(widthStr);
    height = std::stoi(heightStr);

    return true;
}

} // namespace libprcpp
