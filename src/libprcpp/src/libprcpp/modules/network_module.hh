#ifndef LIBPRCPP_NETWORK_MODULE_HH
#define LIBPRCPP_NETWORK_MODULE_HH
#include <libprcpp/base/config.hh>

#include <libprcpp/enums/result_enums.hh>

#include <libprcpp/types/look_types.hh>

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <future>
#include <thread>

#if LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK
#include <drogon/drogon.h>
#include <json/json.h>

using namespace drogon;
#endif // LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK

namespace libprcpp
{

/**
 * @brief libprcpp network module class
 * 
 */
class CNetworkModule
{
private:
    /* data */

public:
    CNetworkModule(/* args */);
    ~CNetworkModule();

    /**
     * @brief curl cmd structure
     * 
     */
    struct SCurlCmd
    {
        SCurlCmd();
        ~SCurlCmd();

        /**
         * @brief secure smtp send by template
         * 
         * @note this is using promise & future and automatically get
         * 
         * @param templateHtml template html file
         * @param templateTitle head title
         * @param templateRecipient email recipient
         * @param templateLookAndReplace look and replace array
         * @param smtpServer e.g. smtp.domain.tld
         * @param smtpServerPort e.g. 465
         * @param smtpSenderAddress e.g. no-reply@foo.baz
         * @param smtpSenderName e.g. no-reply
         * @param smtpSenderPassword your_smtp_user_password
         * @return EResult::Enum 
         */
        EResult::Enum smtpsSendByTemplate(const std::string &templateHtml, const std::string &templateTitle, const std::string &templateRecipient, const std::vector<TLookAndReplace> &templateLookAndReplace, const std::string &smtpServer, const std::string &smtpServerPort, const std::string &smtpSenderAddress, const std::string &smtpSenderName, const std::string &smtpSenderPassword);
    };
    // curl cmd object access
    SCurlCmd CurlCmd = SCurlCmd();

#if LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK
    // RESERVED: SSparkpostDrogon
    /**
     * @brief sparkpost drogon structure
     * 
     */
    struct SSparkpostDrogon
    {
        SSparkpostDrogon();
        ~SSparkpostDrogon();

        /**
         * @brief send mail by template
         * 
         * @note this is using promise & future and automatically get
         * 
         * @param templateHtml template html file
         * @param templateTitle head title
         * @param templateRecipient email recipient
         * @param templateLookAndReplace look and replace array
         * @param sparkpostApiKey your_sparkpost_api_key
         * @param sparkpostSenderName e.g. no-reply@domain.tld
         * @param sparkpostUrl e.g. https://api.sparkpost.com
         * @param sparkpostEndpoint e.g. /api/v1/transmissions
         * @param senderUserAgent your sender user agent, default is "org.drogon-sparkpost"
         * @param enableTracking if true, some url will change to click not as original data pass from templateLookAndReplace
         * @return EResult::Enum 
         */
        EResult::Enum sendMailByTemplate(const std::string &templateHtml, const std::string &templateTitle, const std::string &templateRecipient, const std::vector<TLookAndReplace> &templateLookAndReplace, const std::string &sparkpostApiKey, const std::string &sparkpostSenderName, const std::string &sparkpostUrl, const std::string &sparkpostEndpoint, const std::string &senderUserAgent = "org.drogon-sparkpost", const bool &enableTracking = false);
    };
    // sparkpost drogon object access
    SSparkpostDrogon SparkpostDrogon = SSparkpostDrogon();
#endif // LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK
};

} // namespace libprcpp

#endif // LIBPRCPP_NETWORK_MODULE_HH
