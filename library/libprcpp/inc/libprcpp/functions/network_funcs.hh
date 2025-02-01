#ifndef LIBPRCPP_NETWORK_FUNCS_HH
#define LIBPRCPP_NETWORK_FUNCS_HH
#include <libprcpp/base/config.hh>
#include <libprcpp/base/export.hh>
#include <libprcpp/enums/result_enums.hh>
#include <libprcpp/types/look_types.hh>

#if LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK
#include <drogon/drogon.h>
#include <json/json.h>

using namespace drogon;
#endif // LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <future>
#include <thread>

namespace libprcpp
{
namespace networkFunctions
{


#if LIBPRCPP_FOUND_CURL
namespace curlCmd
{
    /**
     * @brief secure smtp send by template
     * 
     * @note using system to call curl
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
     * @return EResult 
     */
    EResult smtpsSendByTemplate(const std::string &templateHtml, const std::string &templateTitle, const std::string &templateRecipient, const std::vector<TLookAndReplace> &templateLookAndReplace, const std::string &smtpServer, const std::string &smtpServerPort, const std::string &smtpSenderAddress, const std::string &smtpSenderName, const std::string &smtpSenderPassword);

    /**
     * @brief secure smtp send by template future
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
     * @return std::future<EResult> 
     */
    std::future<EResult> smtpsSendByTemplateFuture(const std::string &templateHtml, const std::string &templateTitle, const std::string &templateRecipient, const std::vector<TLookAndReplace> &templateLookAndReplace, const std::string &smtpServer, const std::string &smtpServerPort, const std::string &smtpSenderAddress, const std::string &smtpSenderName, const std::string &smtpSenderPassword);
} // namespace curlCmd
#endif // LIBPRCPP_FOUND_CURL


#if LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK
namespace drogonImpl
{
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
     * @return EResult 
     */
    EResult sendMailByTemplate(const std::string &templateHtml, const std::string &templateTitle, const std::string &templateRecipient, const std::vector<TLookAndReplace> &templateLookAndReplace, const std::string &sparkpostApiKey, const std::string &sparkpostSenderName, const std::string &sparkpostUrl, const std::string &sparkpostEndpoint, const std::string &senderUserAgent = "org.drogon-sparkpost", const bool &enableTracking = false);

    /**
     * @brief send mail by template future
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
     * @return std::future<EResult> 
     */
    std::future<EResult> sendMailByTemplateFuture(const std::string &templateHtml, const std::string &templateTitle, const std::string &templateRecipient, const std::vector<TLookAndReplace> &templateLookAndReplace, const std::string &sparkpostApiKey, const std::string &sparkpostSenderName, const std::string &sparkpostUrl, const std::string &sparkpostEndpoint, const std::string &senderUserAgent = "org.drogon-sparkpost", const bool &enableTracking = false);
} // namespace drogonImpl
#endif // LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK


} // namespace networkFunctions
} // namespace libprcpp

#endif // LIBPRCPP_NETWORK_FUNCS_HH
