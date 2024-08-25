#include <libprcpp/modules/system_module.h>
#include <libprcpp/modules/network_module.h>

struct TSMTPConf
{
    std::string server;
    std::string server_port;
    std::string sender_name;
    std::string sender_address;
    std::string sender_password;
};

using namespace libprcpp;

int main(int argc, char *argv[])
{
    // NOTE:
    // - copy config.debug.json to config.json
    // - replace with your smtp data variables

    CNetworkModule NETWORK;

    const Json::Value CONFIG = utilityFunctions::json::fromFile("../../../test/test_smtps/config.json");

    const std::string TEMPLATE_HTML = "../../../template/html/hello.html";
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

    NETWORK.CurlCmd.smtpsSendByTemplate(
        TEMPLATE_HTML, TEMPLATE_TITLE,
        TEMPLATE_RECIPIENT, lookAndReplace,
        smtpsConf.server, smtpsConf.server_port, smtpsConf.sender_address, smtpsConf.sender_name, smtpsConf.sender_password
    );
}
