#include <libprcpp/functions/network_funcs.hh>
#include <libprcpp/functions/utility_funcs.hh>

namespace libprcpp
{
namespace networkFunctions
{


#if LIBPRCPP_FOUND_CURL
namespace curlCmd
{
    EResult smtpsSendByTemplate(const std::string &templateHtml, const std::string &templateTitle, const std::string &templateRecipient, const std::vector<TLookAndReplace> &templateLookAndReplace, const std::string &smtpServer, const std::string &smtpServerPort, const std::string &smtpSenderAddress, const std::string &smtpSenderName, const std::string &smtpSenderPassword)
    {
        EResult result = EResult::RESULT_ERROR;

        std::promise<EResult> responsePromise;
        std::future<EResult> responseFuture = responsePromise.get_future();

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
                #if LIBPRCPP_IS_DEBUG
                std::cout << "smtpsSendByTemplate: system has multiple threads\n";
                #endif // LIBPRCPP_IS_DEBUG

                auto status = std::async(std::launch::async, system, CMD.c_str());

                if (status.get() == 0)
                {
                    result = EResult::RESULT_OK;
                    responsePromise.set_value(result);
                }
            }
            else
            {
                #if LIBPRCPP_IS_DEBUG == 1
                std::cout << "smtpsSendByTemplate: system has single thread\n";
                #endif // LIBPRCPP_IS_DEBUG

                auto status = system(CMD.c_str());

                if (status == 0)
                {
                    result = EResult::RESULT_OK;
                    responsePromise.set_value(result);
                }
            }
        }
        else
        {
            std::cerr << "smtpsSendByTemplate: can't find the template html\n";
            abort();
        }
        f.close();

        auto statusAndResult = responseFuture.get();

        #if LIBPRCPP_IS_DEBUG
        if (statusAndResult == EResult::RESULT_OK)
        {
            std::cout << "DEBUG smtpsSendByTemplate: result ok\n";
        }
        else
        {
            std::cout << "smtpsSendByTemplate: result error\n";
        }
        #endif // LIBPRCPP_IS_DEBUG

        return statusAndResult;
    }

    std::future<EResult> smtpsSendByTemplateFuture(const std::string &templateHtml, const std::string &templateTitle, const std::string &templateRecipient, const std::vector<TLookAndReplace> &templateLookAndReplace, const std::string &smtpServer, const std::string &smtpServerPort, const std::string &smtpSenderAddress, const std::string &smtpSenderName, const std::string &smtpSenderPassword)
    {
        std::promise<EResult> responsePromise;
        std::future<EResult> responseFuture = responsePromise.get_future();

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
                #if LIBPRCPP_IS_DEBUG
                std::cout << "smtpsSendByTemplateFuture: system has multiple threads\n";
                #endif // LIBPRCPP_IS_DEBUG

                auto status = std::async(std::launch::async, system, CMD.c_str());

                if (status.get() == 0)
                {
                    responsePromise.set_value(EResult::RESULT_OK);
                }
                else
                {
                    responsePromise.set_value(EResult::RESULT_ERROR);
                }
            }
            else
            {
                #if LIBPRCPP_IS_DEBUG == 1
                std::cout << "smtpsSendByTemplateFuture: system has single thread\n";
                #endif // LIBPRCPP_IS_DEBUG

                auto status = system(CMD.c_str());

                if (status == 0)
                {
                    responsePromise.set_value(EResult::RESULT_OK);
                }
                else
                {
                    responsePromise.set_value(EResult::RESULT_ERROR);
                }
            }
        }
        else
        {
            std::cerr << "smtpsSendByTemplateFuture: can't find the template html\n";
            responsePromise.set_value(EResult::RESULT_ERROR);
        }
        f.close();

        return responseFuture;
    }
} // namespace curlCmd
#endif // LIBPRCPP_FOUND_CURL


#if LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK
namespace drogonImpl
{
    EResult sendMailByTemplate(const std::string &templateHtml, const std::string &templateTitle, const std::string &templateRecipient, const std::vector<TLookAndReplace> &templateLookAndReplace, const std::string &sparkpostApiKey, const std::string &sparkpostSenderName, const std::string &sparkpostUrl, const std::string &sparkpostEndpoint, const std::string &senderUserAgent, const bool &enableTracking)
    {
        std::promise<EResult> responsePromise;
        std::future<EResult> responseFuture = responsePromise.get_future();

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
            EResult tmpVal1 = EResult::RESULT_ERROR;

            if (result == ReqResult::Ok && pResp->getStatusCode() == k200OK)
            {
                #if LIBPRCPP_IS_DEBUG
                std::cout << "sendMailByTemplate: sparkpost reponse ok\n";
                #endif // LIBPRCPP_IS_DEBUG
                tmpVal1 = EResult::RESULT_OK;

                responsePromise.set_value(tmpVal1);
            }
            else
            {
                #if LIBPRCPP_IS_DEBUG
                std::cout << "sendMailByTemplate: sparkpost status code is " << pResp->getStatusCode() << "\n";
                #endif // LIBPRCPP_IS_DEBUG
                responsePromise.set_value(tmpVal1);
            }
        });

        f.close();

        return responseFuture.get();
    }

    std::future<EResult> sendMailByTemplateFuture(const std::string &templateHtml, const std::string &templateTitle, const std::string &templateRecipient, const std::vector<TLookAndReplace> &templateLookAndReplace, const std::string &sparkpostApiKey, const std::string &sparkpostSenderName, const std::string &sparkpostUrl, const std::string &sparkpostEndpoint, const std::string &senderUserAgent, const bool &enableTracking)
    {
        std::promise<EResult> responsePromise;
        std::future<EResult> responseFuture = responsePromise.get_future();

        std::stringstream ss;
        std::ifstream f(templateHtml);

        if (!f)
        {
            std::cerr << "sendMailByTemplateFuture: can't find the template html\n";
            responsePromise.set_value(EResult::RESULT_ERROR);
            return responseFuture;
        }

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
            EResult tmpVal1 = EResult::RESULT_ERROR;

            if (result == ReqResult::Ok && pResp->getStatusCode() == k200OK)
            {
                #if LIBPRCPP_IS_DEBUG
                std::cout << "sendMailByTemplateFuture: sparkpost reponse ok\n";
                #endif // LIBPRCPP_IS_DEBUG
                tmpVal1 = EResult::RESULT_OK;

                responsePromise.set_value(tmpVal1);
            }
            else
            {
                #if LIBPRCPP_IS_DEBUG
                std::cout << "sendMailByTemplateFuture: sparkpost status code is " << pResp->getStatusCode() << "\n";
                #endif // LIBPRCPP_IS_DEBUG
                responsePromise.set_value(tmpVal1);
            }
        });

        f.close();

        return responseFuture;
    }
}
// namespace drogonImpl
#endif // LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK


} // namespace networkFunctions
} // namespace libprcpp
