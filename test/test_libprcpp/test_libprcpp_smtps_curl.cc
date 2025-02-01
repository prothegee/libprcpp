#include <libprcpp/functions/utility_funcs.hh>
#include <libprcpp/functions/network_funcs.hh>

using namespace libprcpp;

struct TSMTPConf
{
    std::string server;
    std::string server_port;
    std::string sender_name;
    std::string sender_address;
    std::string sender_password;
};

int main()
{
#if LIBPRCPP_FOUND_CURL
    const Json::Value CONFIG = utilityFunctions::json::fromFile("../../../../test/test_libprcpp/test_libprcpp_smtps_curl.json");

    const std::string TEMPLATE_HTML = "../../../../template/html/hello.html";
    const std::string TEMPLATE_TITLE = "smtps curl cmd with libprcpp";
    const std::string TEMPLATE_RECIPIENT = CONFIG["recipient"].asString();

    TSMTPConf smtpsConf;
    smtpsConf.server = CONFIG["smtp"]["server"].asString();
    smtpsConf.server_port = CONFIG["smtp"]["server_port"].asString();
    smtpsConf.sender_name = CONFIG["smtp"]["sender_name"].asString();
    smtpsConf.sender_address = CONFIG["smtp"]["sender_address"].asString();
    smtpsConf.sender_password = CONFIG["smtp"]["sender_password"].asString();

    const std::vector<TLookAndReplace> lookAndReplace = {
        {"{TITLE}", TEMPLATE_TITLE},
        {"{RECIPIENT_EMAIL}", TEMPLATE_RECIPIENT}
    };

    networkFunctions::curlCmd::smtpsSendByTemplate(
        TEMPLATE_HTML, TEMPLATE_TITLE,
        TEMPLATE_RECIPIENT, lookAndReplace,
        smtpsConf.server, smtpsConf.server_port, smtpsConf.sender_address, smtpsConf.sender_name, smtpsConf.sender_password
    );
#endif // LIBPRCPP_FOUND_CURL
    return 0;
}
