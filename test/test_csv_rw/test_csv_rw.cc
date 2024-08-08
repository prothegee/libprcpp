#include <libprcpp/modules/system_module.h>

using namespace libprcpp;

int main(int argc, char *argv[])
{
    CSystemModule System;

    const std::string fileCsv = "../../../test/test_csv_rw/file_in.csv";

    auto json1 = System.FileJSON.fromCSV(fileCsv);

    System.FileJSON.save(json1, "../../../test/test_csv_rw/file_out.json");
    System.FileJSON.saveToCSV("../../../test/test_csv_rw/file_out.json", "../../../test/test_csv_rw/file_out.csv");
}
