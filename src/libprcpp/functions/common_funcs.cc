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
} // namespace libprcpp
