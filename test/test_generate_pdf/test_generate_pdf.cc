#include <libprcpp/modules/system_module.hh>

using namespace libprcpp;

int main(int argc, char *argv[])
{
    CSystemModule System;

    // test 1
    {
        std::vector<std::vector<std::string>> tableData = {
            {"No.", "Name", "Age", "Occupation"},
            {"1.", "Alice", "30", "Engineer"},
            {"2.", "Bob", "25", "Designer"},
            {"3.", "Charlie", "28", "Teacher"}
        };

        TPdfConfig pdfConfig; // default

        System.File.PDF.Write.dataToTable(tableData, "file_out_generate_pdf.pdf", pdfConfig);
    }
}
