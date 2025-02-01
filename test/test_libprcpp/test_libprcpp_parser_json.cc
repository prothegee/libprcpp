#include <libprcpp/functions/utility_funcs.hh>

using namespace libprcpp;

int main()
{
#if LIBPRCPP_PROJECT_USING_JSONCPP
    try
    {
        std::printf("start test for test_parser_json\n");

        Json::Value input1, input2;

        std::string string1, string2;
        std::string output1 = "test_parser_json_out.json", output2 = "test_parser_json_out_compact.json";

        input1["string"] = "value string some";
        input1["number"] = 41.3;
        input1["boolean"] = true;

        input2["string"] = "value string some";
        input2["number"] = 41.3;
        input2["boolean"] = true;

        if (utilityFunctions::json::saveToJSON(input1, output1, 4) == RESULT_OK)
        {
            std::printf("parse json ok for %s\n", output1.c_str());
        }
        else
        {
            std::printf("parse json fail for %s\n", output1.c_str());
        }
        if (utilityFunctions::json::saveToJSON(input2, output2, 0) == RESULT_OK)
        {
            std::printf("parse json ok for %s\n", output2.c_str());
        }
        else
        {
            std::printf("parse json fail for %s\n", output2.c_str());
        }

        std::printf("attempting to read input/s\n");
        std::printf("input1:\n");
        std::cout << utilityFunctions::json::toString(input1, 4) << "\n";
        std::printf("input2:\n");
        std::cout << utilityFunctions::json::toString(input2, 0) << "\n";

        // // SKIPPED, since output has no difference
        // std::printf("attempting to read output/s\n");
        // std::printf("output1:\n");
        // std::cout << utilityFunctions::json::fromFile(output1) << "\n";
        // std::printf("output2:\n");
        // std::cout << utilityFunctions::json::fromFile(output2) << "\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
#endif // LIBPRCPP_PROJECT_USING_JSONCPP
    return 0;
}