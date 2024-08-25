#ifndef LIBPRCPP_NETWORK_MODULE_H
#define LIBPRCPP_NETWORK_MODULE_H
#include <libprcpp/base/config.h>

#include <libprcpp/enums/result_enums.h>

#include <libprcpp/types/look_types.h>

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <future>
#include <thread>

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

    // RESERVED: SSparkpostDrogon
};

} // namespace libprcpp

#endif // LIBPRCPP_NETWORK_MODULE_H
