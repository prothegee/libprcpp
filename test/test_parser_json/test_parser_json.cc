#include <libprcpp/modules/system_module.hh>

using namespace libprcpp;

int main()
{
    CSystemModule SYSTEM;

    Json::Value input1, input2;
    Json::StreamWriterBuilder writer1, writer2;

    std::string string1, string2;

    writer1.settings_["indentation"] = "    ";
    writer1.settings_["precision"] = 16;

    writer2.settings_["indentation"] = "";
    writer2.settings_["precision"] = 16;

    input1["string"] = "value string some";
    input1["number"] = 41.3;
    input1["boolean"] = true;

    input2["string"] = "value string some";
    input2["number"] = 41.3;
    input2["boolean"] = true;

    std::ofstream f1("../../../test/test_parser_json/file_out.json");
    std::ofstream f2("../../../test/test_parser_json/file_out_compact.json");

    if (f1.is_open())
    {
        string1 = Json::writeString(writer1, input1);

        f1 << string1;
    }
    else
    {
        std::cerr << "ERROR: #1";
    }
    f1.close();

    if (f2.is_open())
    {
        string2 = Json::writeString(writer2, input2);

        f2 << string2;
    }
    else
    {
        std::cerr << "ERROR: #1";
    }
    f2.close();

    return 0;
}
