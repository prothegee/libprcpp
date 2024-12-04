#include "network_module.hh"

#include "utility_module.hh"

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

EResult::ENUM CNetworkModule::SCurlCmd::smtpsSendByTemplate(const std::string &templateHtml, const std::string &templateTitle, const std::string &templateRecipient, const std::vector<TLookAndReplace> &templateLookAndReplace, const std::string &smtpServer, const std::string &smtpServerPort, const std::string &smtpSenderAddress, const std::string &smtpSenderName, const std::string &smtpSenderPassword)
{
    EResult::ENUM result = EResult::ENUM::RESULT_ERROR;

    std::promise<EResult::ENUM> responsePromise;
    std::future<EResult::ENUM> responseFuture = responsePromise.get_future();

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
            utilityFunctions::find::andReplaceAll(RECIPIENT_CONTENT_HTML, data.to_look, data.to_replace);
        }

        RECIPIENT_ADDRESS = templateRecipient;
        RECIPIENT_SUBJECT = templateTitle;
        RECIPIENT_CONTENT = RECIPIENT_CONTENT_HTML;

        utilityFunctions::find::andReplaceAll(CMD, "{SMTP_SERVER}", smtpServer);
        utilityFunctions::find::andReplaceAll(CMD, "{SMTP_PORT}", smtpServerPort);
        utilityFunctions::find::andReplaceAll(CMD, "{SMTP_USER}", smtpSenderAddress);
        utilityFunctions::find::andReplaceAll(CMD, "{SMTP_PASSWD}", smtpSenderPassword);
        utilityFunctions::find::andReplaceAll(CMD, "{SMTP_SENDER}", smtpSenderName);
        utilityFunctions::find::andReplaceAll(CMD, "{RECIPIENT_ADDRESS}", RECIPIENT_ADDRESS);
        utilityFunctions::find::andReplaceAll(CMD, "{RECIPIENT_SUBJECT}", RECIPIENT_SUBJECT);
        utilityFunctions::find::andReplaceAll(CMD, "{RECIPIENT_CONTENT}", RECIPIENT_CONTENT);

        if (std::thread::hardware_concurrency() >= 2)
        {
        #if PROJECT_BUILD_STATUS == 1
            std::cout << "DEBUG CNetworkModule::SCurlCmd::smtpsSendByTemplate: system has multiple threads\n";
        #endif // PROJECT_BUILD_STATUS

            auto status = std::async(std::launch::async, system, CMD.c_str());

            if (status.get() == 0)
            {
                result = EResult::ENUM::RESULT_OK;
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
                result = EResult::ENUM::RESULT_OK;
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
    if (statusAndResult == EResult::ENUM::RESULT_OK)
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

#if LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK
CNetworkModule::SSparkpostDrogon::SSparkpostDrogon()
{
}

CNetworkModule::SSparkpostDrogon::~SSparkpostDrogon()
{
}
EResult::ENUM CNetworkModule::SSparkpostDrogon::sendMailByTemplate(const std::string &templateHtml, const std::string &templateTitle, const std::string &templateRecipient, const std::vector<TLookAndReplace> &templateLookAndReplace, const std::string &sparkpostApiKey, const std::string &sparkpostSenderName, const std::string &sparkpostUrl, const std::string &sparkpostEndpoint, const std::string &senderUserAgent, const bool &enableTracking)
{
    std::promise<EResult::ENUM> responsePromise;
    std::future<EResult::ENUM> responseFuture = responsePromise.get_future();

    CUtilityModule Utility;

    std::stringstream ss;
    std::ifstream f(templateHtml);

    std::string RECIPIENT_CONTENT_HTML;

    Json::Value root, content, recipients, options;

    ss << f.rdbuf();

    RECIPIENT_CONTENT_HTML = ss.str();

    for (auto &data : templateLookAndReplace)
    {
        utilityFunctions::find::andReplaceAll(RECIPIENT_CONTENT_HTML, data.to_look, data.to_replace);
    }

    content["from"] = sparkpostSenderName;
    content["subject"] = templateTitle;
    content["text"] = RECIPIENT_CONTENT_HTML;
    content["html"] = RECIPIENT_CONTENT_HTML;

    recipients["address"] = templateRecipient;

    root["content"] = content;
    root["recipients"].append(recipients);
    root["options"]["click_tracking"] = enableTracking;

    auto pClient = HttpClient::newHttpClient(sparkpostUrl);
    auto pRequest = HttpRequest::newHttpJsonRequest(root);

    pClient->setUserAgent(senderUserAgent);

    pRequest->setPath(sparkpostEndpoint);
    pRequest->setContentTypeCode(CT_APPLICATION_JSON);
    pRequest->addHeader("accept", "*/*");
    pRequest->addHeader("authorization", sparkpostApiKey);
    pRequest->setMethod(Post);

    pClient->sendRequest(pRequest, [&responsePromise](ReqResult result, const HttpResponsePtr &pResp)
    {
        EResult::ENUM tmpVal1 = EResult::ENUM::RESULT_ERROR;

        if (result == ReqResult::Ok && pResp->getStatusCode() == k200OK)
        {
        #if PROJECT_BUILD_STATUS == 1
            std::cout << "DEBUG CNetworkModule::SSparkpostDrogon::sendMailByTemplate: sparkpost reponse ok\n";
        #endif
            tmpVal1 = EResult::ENUM::RESULT_OK;

            responsePromise.set_value(tmpVal1);
        }
        else
        {
        #if PROJECT_BUILD_STATUS == 1
            std::cout << "DEBUG CNetworkModule::SSparkpostDrogon::sendMailByTemplate: sparkpost status code is " << pResp->getStatusCode() << "\n";
        #endif
            responsePromise.set_value(tmpVal1);
        }
    });

    f.close();

    return responseFuture.get();
}
#endif // LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK

} // namespace libprcpp
