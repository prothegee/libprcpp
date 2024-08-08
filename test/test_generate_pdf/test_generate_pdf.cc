#include <libprcpp/modules/system_module.h>

using namespace libprcpp;

int main(int argc, char *argv[])
{
    CSystemModule System;

    std::vector<std::vector<std::string>> tableData = {
        {"No.", "Name", "Age", "Occupation"},
        {"1.", "Alice", "30", "Engineer"},
        {"2.", "Bob", "25", "Designer"},
        {"3.", "Charlie", "28", "Teacher"}
    };

    TPdfConfig pdfConfig; // default

    System.FilePDF.generateTable(tableData, "test_generate_pdf.pdf", pdfConfig);
}
