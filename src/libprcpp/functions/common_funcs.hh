#ifndef LIBPRCPP_COMMON_FUNCS_HH
#define LIBPRCPP_COMMON_FUNCS_HH
#include <string>
#include <cstdint>
#include <algorithm>

namespace libprcpp
{

    /**
     * @brief cehck if str param is numeric
     * 
     * @param str 
     * @return true 
     * @return false 
     */
    bool isNumeric(const std::string &str);

    /**
     * @brief get arg of "int main" value to check/pass
     * 
     * @note mostly after check some arg of something, e.g. pass after arg is --some-arg in cmdline
     * 
     * @param argc 
     * @param argv 
     * @param i 
     * @param value 
     * @param defaultValue 
     * @return true 
     * @return false 
     */
    bool getArgMainValue(int argc, char* argv[], int& i, std::string& value, const std::string& defaultValue = "");

    /**
     * @brief check if input param find the exact checkWith param
     * 
     * @param input 
     * @param checkWith 
     * @return true 
     * @return false 
     */
    bool inputEndsWith(const std::string &input, const std::string &checkWith);
} // namespace libprcpp

#endif // LIBPRCPP_COMMON_FUNCS_HH
