#ifndef LIBPRCPP_HOST_CONST_H
#define LIBPRCPP_HOST_CONST_H
#include <libprcpp/base/config.hh>

#ifndef HTTP_OR_HTTPS
    #if PROJECT_BUILD_STATUS == 1
        #define HTTP_OR_HTTPS "http://"
    #elif PROJECT_BUILD_STATUS == 2
        #define HTTP_OR_HTTPS "https://"
    #elif PROJECT_BUILD_STATUS == 3
        #define HTTP_OR_HTTPS "https://"
    #elif PROJECT_BUILD_STATUS == 4
        #define HTTP_OR_HTTPS "https://"
    #else
        #define HTTP_OR_HTTPS "https://"
    #endif
#endif // HTTP_OR_HTTPS

#ifndef WS_OR_WSS
    #if PROJECT_BUILD_STATUS == 1
        #define WS_OR_WSS "ws://"
    #elif PROJECT_BUILD_STATUS == 2
        #define WS_OR_WSS "wss://"
    #elif PROJECT_BUILD_STATUS == 3
        #define WS_OR_WSS "wss://"
    #elif PROJECT_BUILD_STATUS == 4
        #define WS_OR_WSS "wss://"
    #else
        #define WS_OR_WSS "wss://"
    #endif
#endif // WS_OR_WSS

namespace libprcpp
{

/**
 * @brief host address access object collection
 * 
 */
struct HOST_ADDRESS
{

struct COM_MIDTRANS
{
    struct API
    {
        struct BASE
        {
            inline static const char *SANDBOX = "https://api.sandbox.midtrans.com";
            inline static const char *PRODUCTION = "https://api.midtrans.com";
        };
    };
};

struct COM_PAYPAL
{
    struct API
    {
        struct BASE
        {
            inline static const char *SANDBOX = "https://api-m.sandbox.paypal.com";
            inline static const char *PRODUCTION = "https://api-m.paypal.com";
        };
    };
};

struct COM_SPARKPOST
{
    struct API
    {
        inline static const char *SANDBOX = "https://api.sparkpost.com";
        inline static const char *PRODUCTION = "https://api.sparkpost.com";
    };
    struct API_ENDPOINT
    {
        inline static const char *TRANSMISSIONS = "/api/v1/transmissions";
    };
};

struct CO_XENDIT
{
    struct API
    {
        struct BASE
        {
            inline static const char *SANDBOX = "https://api.xendit.co";
            inline static const char *PRODUCTION = "https://api.xendit.co";
            // NOTE: xendit api sandbox & live/production is same, but just in case
        };
    };
};

};

} // namespace libprcpp

#endif // LIBPRCPP_HOST_CONST_H
