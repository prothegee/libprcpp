#ifndef LIBPRCPP_IDROGON_HHTTP_CONTROLLER_HHELPER_HH
#define LIBPRCPP_IDROGON_HHTTP_CONTROLLER_HHELPER_HH
#include <libprcpp/base/config.hh>

#if LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK
#include <drogon/drogon.h>

#include <libprcpp/constants/header_const.hh>

namespace libprcpp
{

using namespace drogon;

/**
 * @brief drogon http controller helper class interface
 * 
 */
class IDrogonHttpControllerHelper
{
private:
    /* data */

public:
    virtual ~IDrogonHttpControllerHelper();

    /**
     * @brief before callback interface structure
     * 
     */
    struct SIBeforeCallback
    {
        /**
         * @brief add strict-transport-security header
         * 
         * @param pResp 
         * @param maxAge default is 31557600 seconds or  365.25 days 
         * @param force default is false, if true, object header will be added no matter what
         */
        void addStrictTransportSecurity(HttpResponsePtr &pResp, const int &maxAge = 31557600, const bool &force = false);

        /**
         * @brief add default cross-origin-* header
         * 
         * @param pResp 
         * @param force default is false, if true, object header will be added no matter what
         */
        void addCrossOriginCommonDefault(HttpResponsePtr &pResp, const bool &force = false);

        /**
         * @brief check if origin header is on whitelist
         * 
         * @note commonly use before callback for json page
         * 
         * @param originWhitelist 
         * @param pReq 
         * @param pResp 
         * @param force 
         * @return true 
         * @return false 
         */
        bool checkOriginIsFromWhitelist(const Json::Value &originWhitelist, HttpRequestPtr &pReq, HttpResponsePtr &pResp, const bool &force = false);
        bool checkOriginIsFromWhitelist(const Json::Value &originWhitelist, const HttpRequestPtr &pReq, HttpResponsePtr &pResp, const bool &force = false);
    };
    // drogon http controller interface before callback access
    SIBeforeCallback IBeforeCallback = SIBeforeCallback();

    /**
     * @brief bundle interface structure
     * 
     */
    struct SIStartBundle
    {
        /**
         * @brief invoke javascript bundle into target keyword from bundla name
         * 
         * @param bundleName 
         * @param viewData 
         * @param scriptMode 0:no_treatment 1:module 2:module_defer 3:module_async | default is 2
         */
        void frontendJsModule(const std::string &bundleName, HttpViewData &viewData, const int &scriptMode = 2);

        /**
         * @brief invoke css bundle into target keyword from bundle name
         * 
         * @param bundleName 
         * @param viewData 
         */
        void frontendCssModule(const std::string &bundleName, HttpViewData &viewData);
    };
    // bundle interface access for frontend
    // mostly use when you working with drogon .csp
    // use it at start http controller, not before callback
    SIStartBundle IStartBundle = SIStartBundle();

    /**
     * @brief start check interface structure
     * 
     */
    struct SIStartCheck
    {
        /**
         * @brief check request where `/{lang}/` is exists in controller
         * 
         * @note if lang is not in supported languages, will redirect to `defaultEndpoint` param
         * 
         * @param supportedLanguages array string of supported languages
         * @param pReq 
         * @param pResp 
         * @param fCallback 
         * @param languageEndpoint 
         * @param defaulEndpoint 
         * @param viewData 
         */
        void acceptedLanguage(const Json::Value &supportedLanguages, HttpRequestPtr &pReq, HttpResponsePtr &pResp, std::function<void(const HttpResponsePtr &)> &fCallback, const std::string &languageEndpoint, const std::string &defaulEndpoint, HttpViewData &viewData);
        void acceptedLanguage(const Json::Value &supportedLanguages, const HttpRequestPtr &pReq, HttpResponsePtr &pResp, std::function<void(const HttpResponsePtr &)> &fCallback, const std::string &languageEndpoint, const std::string &defaulEndpoint, HttpViewData &viewData);
    };
    // invoke interface start and check for frontend
    // use it at start http controller, not before callback
    SIStartCheck IStartCheck = SIStartCheck();

    /**
     * @brief start invoke interface structure
     * 
     */
    struct SIStartInvokeMeta
    {
        // language meta
        void language(const std::string &input, HttpViewData &viewData);
        
        // robot.txt meta
        void robot(const std::string &input, HttpViewData &viewData);
        
        // title meta
        void title(const std::string &input, HttpViewData &viewData);
        
        // keywords meta
        void keywords(const std::string &input, HttpViewData &viewData);
        
        // about meta
        void about(const std::string &input, HttpViewData &viewData);
        
        // description meta
        void description(const std::string &input, HttpViewData &viewData);
        
        // url meta
        void url(const std::string &input, HttpViewData &viewData);
        
        // copyright meta
        void copyright(const std::string &input, HttpViewData &viewData);
        
        // image meta
        void image(const std::string &input, HttpViewData &viewData);
        
        // video meta
        void video(const std::string &input, HttpViewData &viewData);

        // custom parameter
        void customParameter(const std::string &param, const std::string &input, HttpViewData &viewData);
    };
    // invoke interface access for frontend
    // mostly use when you working with drogon .csp
    // use it at start http controller, not before callback
    // invoke this after acceptedLanguage since some meta data need to overwrite
    SIStartInvokeMeta IStartInvokeMeta = SIStartInvokeMeta();
};

} // namespace libprcpp

#endif // LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK

#endif // LIBPRCPP_IDROGON_HHTTP_CONTROLLER_HHELPER_HH
