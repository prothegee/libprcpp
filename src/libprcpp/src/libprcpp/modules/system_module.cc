#include "system_module.h"

namespace libprcpp
{

CSystemModule::CSystemModule()
{
}

CSystemModule::~CSystemModule()
{
}

bool CSystemModule::SDirectory::createDirectory(const std::string &path)
{
    std::filesystem::path directory = path;

    return fs::create_directory(directory);
}

bool CSystemModule::SDirectory::deleteDirectory(const std::string &path)
{
    std::filesystem::path directory = path;

    return fs::remove(directory);
}

std::string CSystemModule::SDirectory::getCurrentDir()
{
    std::filesystem::path currentDir = std::filesystem::current_path();

    return currentDir.string();
}

#if PROJECT_USING_LIBHARU
bool CSystemModule::SFilePDF::generateTable(const std::vector<std::vector<std::string>> &tableData, const std::string &filePathName, const TPdfConfig &pdfConfig)
{
    bool result = false;

    HPDF_Doc pdf = HPDF_New(filePDFerrorHandler, NULL);
    if (!pdf)
    {
        #if PROJECT_BUILD_STATUS == 1
        std::cerr << "DEBUG ERROR FilePDF: Cannot create PDF object\n";
        #endif
        return result;
    }

    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, pdfConfig.page_size, pdfConfig.page_direction);

    HPDF_Font font = HPDF_GetFont(pdf, pdfConfig.font.c_str(), NULL);
    HPDF_Page_SetFontAndSize(page, font, 12);

    for (size_t i = 0; i < tableData.size(); ++i)
    {
        for (size_t j = 0; j < tableData[i].size(); ++j)
        {
            float posX = pdfConfig.table_left_x + j * pdfConfig.cell_width;
            float posY = pdfConfig.table_top_y - i * pdfConfig.cell_height;

            HPDF_Page_Rectangle(page, posX, posY - pdfConfig.cell_height, pdfConfig.cell_width, pdfConfig.cell_height);
            HPDF_Page_Stroke(page);

            HPDF_Page_BeginText(page);
            HPDF_Page_TextOut(page, posX + 2, posY - pdfConfig.cell_height + 2, tableData[i][j].c_str());
            HPDF_Page_EndText(page);
        }
    }

    HPDF_SaveToFile(pdf, filePathName.c_str());

    HPDF_Free(pdf);

    result = true;

    #if PROJECT_BUILD_STATUS == 1
    std::cout << "DEBUG FilePDF: generated successfully!\n";
    #endif

    return result;
}
#endif // PROJECT_USING_LIBHARU

} // namespace libprcpp
