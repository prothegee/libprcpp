#include <libprcpp/modules/system_module.hh>

using namespace libprcpp;

int main(int argc, char *argv[])
{
    CSystemModule System;

    const std::string fileCsv = "../../../test/test_csv_rw/file_in.csv";

    Json::Value jsonData;

    System.File.JSON.Read.fromFileCSV(fileCsv, jsonData);

    System.File.JSON.Write.saveToJSON(jsonData, "../../../test/test_csv_rw/file_out.json");
    System.File.JSON.Write.saveToCSV("../../../test/test_csv_rw/file_out.json", "../../../test/test_csv_rw/file_out.csv");
}
