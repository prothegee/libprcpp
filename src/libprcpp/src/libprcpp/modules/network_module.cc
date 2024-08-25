#include "network_module.h"

#include "utility_module.h"

namespace libprcpp
{

CNetworkModule::CNetworkModule()
{
}

CNetworkModule::~CNetworkModule()
{
}

CNetworkModule::SCurlCmd::SCurlCmd()
{
}

CNetworkModule::SCurlCmd::~SCurlCmd()
{
}

EResult::Enum CNetworkModule::SCurlCmd::smtpsSendByTemplate(const std::string &templateHtml, const std::string &templateTitle, const std::string &templateRecipient, const std::vector<TLookAndReplace> &templateLookAndReplace, const std::string &smtpServer, const std::string &smtpServerPort, const std::string &smtpSenderAddress, const std::string &smtpSenderName, const std::string &smtpSenderPassword)
{
    EResult::Enum result = EResult::Enum::RESULT_ERROR;

    std::promise<EResult::Enum> responsePromise;
    std::future<EResult::Enum> responseFuture = responsePromise.get_future();

    std::ifstream f(templateHtml);
    std::stringstream ss;

    std::string RECIPIENT_ADDRESS, RECIPIENT_SUBJECT, RECIPIENT_CONTENT, RECIPIENT_CONTENT_HTML, RECIPIENT_PASSCODE, CMD;

    CMD = R"(curl --ssl-reqd --url "smtps://{SMTP_SERVER}:{SMTP_PORT}" \
    --silent \
    --user "{SMTP_USER}:{SMTP_PASSWD}" \
    --mail-from "{SMTP_USER}" \
    --mail-rcpt "{RECIPIENT_ADDRESS}" \
    --upload-file - << EOF
From: {SMTP_SENDER} <{SMTP_USER}>
To: {RECIPIENT_ADDRESS}
Subject: {RECIPIENT_SUBJECT}
Content-Type: text/html; charset="UTF-8"

{RECIPIENT_CONTENT}
)";

    if (f)
    {
        ss << f.rdbuf();
        RECIPIENT_CONTENT_HTML = ss.str();

        for (auto &data : templateLookAndReplace)
        {
            utilityFunctions::findAndReplaceAll(RECIPIENT_CONTENT_HTML, data.to_look, data.to_replace);
        }

        RECIPIENT_ADDRESS = templateRecipient;
        RECIPIENT_SUBJECT = templateTitle;
        RECIPIENT_CONTENT = RECIPIENT_CONTENT_HTML;

        utilityFunctions::findAndReplaceAll(CMD, "{SMTP_SERVER}", smtpServer);
        utilityFunctions::findAndReplaceAll(CMD, "{SMTP_PORT}", smtpServerPort);
        utilityFunctions::findAndReplaceAll(CMD, "{SMTP_USER}", smtpSenderAddress);
        utilityFunctions::findAndReplaceAll(CMD, "{SMTP_PASSWD}", smtpSenderPassword);
        utilityFunctions::findAndReplaceAll(CMD, "{SMTP_SENDER}", smtpSenderName);
        utilityFunctions::findAndReplaceAll(CMD, "{RECIPIENT_ADDRESS}", RECIPIENT_ADDRESS);
        utilityFunctions::findAndReplaceAll(CMD, "{RECIPIENT_SUBJECT}", RECIPIENT_SUBJECT);
        utilityFunctions::findAndReplaceAll(CMD, "{RECIPIENT_CONTENT}", RECIPIENT_CONTENT);

        if (std::thread::hardware_concurrency() >= 2)
        {
            #if PROJECT_BUILD_STATUS == 1
            std::cout << "DEBUG CNetworkModule::SCurlCmd::smtpsSendByTemplate: system has multiple threads\n";
            #endif // PROJECT_BUILD_STATUS

            auto status = std::async(std::launch::async, system, CMD.c_str());

            if (status.get() == 0)
            {
                result = EResult::Enum::RESULT_OK;
                responsePromise.set_value(result);
            }
        }
        else
        {
            #if PROJECT_BUILD_STATUS == 1
            std::cout << "DEBUG CNetworkModule::SCurlCmd::smtpsSendByTemplate: system has single thread\n";
            #endif // PROJECT_BUILD_STATUS

            auto status = system(CMD.c_str());

            if (status == 0)
            {
                result = EResult::Enum::RESULT_OK;
                responsePromise.set_value(result);
            }
        }
    }
    else
    {
        std::cerr << "ERROR CNetworkModule::SCurlCmd::smtpsSendByTemplate: can't find the template html\n";
        abort();
    }
    f.close();

    auto statusAndResult = responseFuture.get();

    #if PROJECT_BUILD_STATUS == 1
    if (statusAndResult == EResult::Enum::RESULT_OK)
    {
        std::cout << "DEBUG CNetworkModule::SCurlCmd::smtpsSendByTemplate: result ok\n";
    }
    else
    {
        std::cout << "DEBUG CNetworkModule::SCurlCmd::smtpsSendByTemplate: result error\n";
    }
    #endif // PROJECT_BUILD_STATUS
    return statusAndResult;
}

} // namespace libprcpp
