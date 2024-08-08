#include "idrogon_http_controller_helper.h"

namespace libprcpp
{

IDrogonHttpControllerHelper::~IDrogonHttpControllerHelper()
{
}
void IDrogonHttpControllerHelper::SIBeforeCallback::addStrictTransportSecurity(HttpResponsePtr &pResp, const int &maxAge, const bool &force)
{
    std::string maxAgeStr = "max-age=" + std::to_string(maxAge);

    if (PROJECT_BUILD_STATUS != 1 || force)
    {
        pResp->addHeader(HEADER::HTTP_HEADER_ALIASES::STRICT_TRANSPORT_SECURITY, maxAgeStr);
    }
}

void IDrogonHttpControllerHelper::SIBeforeCallback::addCrossOriginCommonDefault(HttpResponsePtr &pResp, const bool &force)
{
    if (PROJECT_BUILD_STATUS != 1 || force)
    {
        pResp->addHeader(HEADER::HTTP_HEADER_ALIASES::CROSS_ORIGIN_OPENER_POLICY, "same-origin");
        pResp->addHeader(HEADER::HTTP_HEADER_ALIASES::CROSS_ORIGIN_EMBEDDER_POLICY, "required-corp");
        pResp->addHeader(HEADER::HTTP_HEADER_ALIASES::X_FRAME_OPTIONS, "sameorigin");
    }
}

bool IDrogonHttpControllerHelper::SIBeforeCallback::checkOriginIsFromWhitelist(const Json::Value &originWhitelist, HttpRequestPtr &pReq, HttpResponsePtr &pResp, const bool &force)
{
    bool result = false;

    for (auto list : originWhitelist)
    {
        if (pReq->getHeader(HEADER::HTTP_HEADER_ALIASES::ORIGIN) == list.asString())
        {
            result = true;
            break;
        }
    }

    if (result)
    {
        pResp->addHeader(HEADER::HTTP_HEADER_ALIASES::ACCESS_CONTROL_ALLOW_ORIGIN, pReq->getHeader(HEADER::HTTP_HEADER_ALIASES::ORIGIN));
    }

    if (force)
    {
        pResp->addHeader(HEADER::HTTP_HEADER_ALIASES::ACCESS_CONTROL_ALLOW_ORIGIN, "*");
    }

    return result;
}

bool IDrogonHttpControllerHelper::SIBeforeCallback::checkOriginIsFromWhitelist(const Json::Value &originWhitelist, const HttpRequestPtr &pReq, HttpResponsePtr &pResp, const bool &force)
{
    bool result = false;

    for (auto list : originWhitelist)
    {
        if (pReq->getHeader(HEADER::HTTP_HEADER_ALIASES::ORIGIN) == list.asString())
        {
            result = true;
            break;
        }
    }

    if (result)
    {
        pResp->addHeader(HEADER::HTTP_HEADER_ALIASES::ACCESS_CONTROL_ALLOW_ORIGIN, pReq->getHeader(HEADER::HTTP_HEADER_ALIASES::ORIGIN));
    }

    if (force)
    {
        pResp->addHeader(HEADER::HTTP_HEADER_ALIASES::ACCESS_CONTROL_ALLOW_ORIGIN, "*");
    }

    return result;
}

void IDrogonHttpControllerHelper::SIStartBundle::frontendJsModule(const std::string &bundleName, HttpViewData &viewData, const int &scriptMode)
{
    bool useBundleJs = false;

    std::string bundle;

    if (bundleName.length() > 0)
    {
        useBundleJs = true;
    }

    if (scriptMode == 0)
    {
        bundle += "<script src=\"";
    }
    else if (scriptMode == 1)
    {
        bundle += "<script type=\"module\" src=\"";
    }
    else if (scriptMode == 2)
    {
        bundle += "<script defer type=\"module\" src=\"";
    }
    else if (scriptMode == 3)
    {
        bundle += "<script async type=\"module\" src=\"";
    }
    else
    {
        bundle += "<script async type=\"module\" src=\"";
    }

    bundle += bundleName;
    bundle += ".js";
    bundle += "\"></script>";

    viewData.insert("{BUNDLE_JS}", bundle);
}

void IDrogonHttpControllerHelper::SIStartBundle::frontendCssModule(const std::string &bundleName, HttpViewData &viewData)
{
    bool useBundleCss = false;

    std::string bundle;

    if (bundleName.length() > 0)
    {
        useBundleCss = true;
    }

    bundle += "<link rel=\"stylesheet\" href=\"";
    bundle += bundleName;
    bundle += ".css";
    bundle += "\">";

    viewData.insert("{BUNDLE_CSS}", bundle);
}

void IDrogonHttpControllerHelper::SIStartCheck::acceptedLanguage(const Json::Value &supportedLanguages, HttpRequestPtr &pReq, HttpResponsePtr &pResp, std::function<void(const HttpResponsePtr &)> &fCallback, const std::string &languageEndpoint, const std::string &defaulEndpoint, HttpViewData &viewData)
{
    bool accepted = false;
    std::string origin, acceptLanguage, redirectUrl;

    origin = pReq->getHeader(HEADER::HTTP_HEADER_ALIASES::ORIGIN);
    acceptLanguage = pReq->getHeader(HEADER::HTTP_HEADER_ALIASES::ACCEPT_LANGUAGE);

    for (auto language : supportedLanguages)
    {
        if (language.asString().rfind(languageEndpoint, 0) == 0)
        {
            accepted = true;
            break;
        }
    }

    if (!accepted)
    {
        pResp = HttpResponse::newHttpResponse();
        redirectUrl = origin + defaulEndpoint;

        fCallback(pResp->newRedirectionResponse(redirectUrl, k307TemporaryRedirect));
    }

    viewData.insert("{LANGUAGE}", languageEndpoint);
}

void IDrogonHttpControllerHelper::SIStartCheck::acceptedLanguage(const Json::Value &supportedLanguages, const HttpRequestPtr &pReq, HttpResponsePtr &pResp, std::function<void(const HttpResponsePtr &)> &fCallback, const std::string &languageEndpoint, const std::string &defaulEndpoint, HttpViewData &viewData)
{
    bool accepted = false;
    std::string origin, acceptLanguage, redirectUrl;

    origin = pReq->getHeader(HEADER::HTTP_HEADER_ALIASES::ORIGIN);
    acceptLanguage = pReq->getHeader(HEADER::HTTP_HEADER_ALIASES::ACCEPT_LANGUAGE);

    for (auto language : supportedLanguages)
    {
        if (language.asString().rfind(languageEndpoint, 0) == 0)
        {
            accepted = true;
            break;
        }
    }

    if (!accepted)
    {
        pResp = HttpResponse::newHttpResponse();
        redirectUrl = origin + defaulEndpoint;

        fCallback(pResp->newRedirectionResponse(redirectUrl, k307TemporaryRedirect));
    }

    viewData.insert("{LANGUAGE}", languageEndpoint);
}

void IDrogonHttpControllerHelper::SIStartInvokeMeta::language(const std::string &input, HttpViewData &viewData)
{
    viewData.insert("{LANGUAGE}", input);
}

void IDrogonHttpControllerHelper::SIStartInvokeMeta::robot(const std::string &input, HttpViewData &viewData)
{
    viewData.insert("{ROBOTS}", input);
}

void IDrogonHttpControllerHelper::SIStartInvokeMeta::title(const std::string &input, HttpViewData &viewData)
{
    viewData.insert("{TITLE}", input);
}

void IDrogonHttpControllerHelper::SIStartInvokeMeta::keywords(const std::string &input, HttpViewData &viewData)
{
    viewData.insert("{KEYWORDS}", input);
}

void IDrogonHttpControllerHelper::SIStartInvokeMeta::about(const std::string &input, HttpViewData &viewData)
{
    viewData.insert("{ABOUT}", input);
}

void IDrogonHttpControllerHelper::SIStartInvokeMeta::description(const std::string &input, HttpViewData &viewData)
{
    viewData.insert("{DESCRIPTION}", input);
}

void IDrogonHttpControllerHelper::SIStartInvokeMeta::url(const std::string &input, HttpViewData &viewData)
{
    viewData.insert("{URL}", input);
}

void IDrogonHttpControllerHelper::SIStartInvokeMeta::copyright(const std::string &input, HttpViewData &viewData)
{
    viewData.insert("{COPYRIGHT}", input);
}

void IDrogonHttpControllerHelper::SIStartInvokeMeta::image(const std::string &input, HttpViewData &viewData)
{
    viewData.insert("{IMAGE}", input);
}

void IDrogonHttpControllerHelper::SIStartInvokeMeta::video(const std::string &input, HttpViewData &viewData)
{
    viewData.insert("{VIDEO}", input);
}

} // namespace libprcpp
