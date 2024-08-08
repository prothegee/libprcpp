#ifndef LIBPRCPP_OK_TYPES_H
#define LIBPRCPP_OK_TYPES_H
#include <libprcpp/base/config.h>

#include <string>
#include <any>

#if PROJECT_USING_JSONCPP
#include <jsoncpp/json/json.h>
#endif // PROJECT_USING_JSONCPP

namespace libprcpp
{

/**
 * @brief type ok with message structure
 * 
 */
struct TOkMessage
{
    bool ok = false;
    std::string message = "";
};

#if PROJECT_USING_JSONCPP
/**
 * @brief type ok with message and data structure
 * 
 */
struct TOkMessageData
{
    bool ok = false;
    std::string message = "";
    Json::Value data;
};
#endif // PROJECT_USING_JSONCPP

/**
 * @brief type ok with any structure
 * 
 */
struct TOkAny
{
    bool ok = false;
    std::any any;
};

} // namespace libprcpp

#endif // LIBPRCPP_OK_TYPES_H
