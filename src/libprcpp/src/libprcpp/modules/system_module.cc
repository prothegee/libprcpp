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

#if LIBPRCPP_PROJECT_USING_LIBHARU
bool CSystemModule::SFilePDF::generateTable(const std::vector<std::vector<std::string>> &tableData, const std::string &filePathName, const TPdfConfig &pdfConfig)
{
    bool result = false;

    HPDF_Doc pdf = HPDF_New(filePDFerrorHandler, NULL);
    if (!pdf)
    {
        std::cerr << "ERROR FilePDF: cannot create PDF object on \"CSystemModule::SFilePDF::generateTable\"\n";
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
    #endif // PROJECT_BUILD_STATUS

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_LIBHARU

#if LIBPRCPP_PROJECT_USING_JSONCPP
std::string CSystemModule::SFileJSON::toString(const Json::Value &input, const int &indent, const int &precision)
{
    int _indent, _precision;

    if (indent >= 4) { _indent = 4; }
    if (indent <= 3) { _indent = 0; }
    if (precision >= 16) { _precision = 16; }
    if (precision <= 2) { _precision = 2; }

    Json::StreamWriterBuilder writter;
    
    std::string _indentString = "";
    for (auto i = 0; i < indent; i++)
    {
        _indentString += " ";
    }

    writter.settings_["indentation"] = _indentString;
    writter.settings_["precision"] = _precision;

    return std::string(Json::writeString(writter, input));
}

Json::Value CSystemModule::SFileJSON::fromFile(const std::string &input)
{
    Json::Value result;

    std::ifstream f(input);

    if (f.is_open())
    {
        f >> result;
        f.close();
    }
    else
    {
        std::cerr << "ERROR FileJSON: can't find json file from \"" << input << "\" in \"CSystemModule::SFileJSON::fromFile\"\n";
    }

    return result;
}

Json::Value CSystemModule::SFileJSON::fromString(const std::string &input, const int &indent, const int &precision)
{
    Json::Value result;

    int _indent, _precision;

    if (indent >= 4) { _indent = 4; }
    if (indent <= 3) { _indent = 0; }
    if (precision >= 16) { _precision = 16; }
    if (precision <= 2) { _precision = 2; }

    std::string _indentString = "";
    for (auto i = 0; i < indent; i++)
    {
        _indentString += " ";
    }

    JSONCPP_STRING err;
    Json::CharReaderBuilder builder;

    builder["indentation"] = _indentString;
    builder["precision"] = _precision;

    const int inputLength = static_cast<int>(input.length());

    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    reader->parse(input.c_str(), input.c_str() + inputLength, &result, &err);

    return result;
}

Json::Value CSystemModule::SFileJSON::fromCSV(const std::string &input)
{
    Json::Value result;

    std::ifstream file(input);
    std::string line;
    std::vector<std::string> headers;

    if (file.is_open())
    {
        if (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string header;
            while (std::getline(ss, header, ','))
            {
                header.erase(header.find_last_not_of(" \t\r\n") + 1);
                header.erase(0, header.find_first_not_of(" \t\r\n"));
                headers.push_back(header);
            }
        }

        Json::Value jsonArray(Json::arrayValue);
        while (std::getline(file, line))
        {
            line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
            
            std::stringstream ss(line);
            std::string cell;
            Json::Value jsonObject(Json::objectValue);
            size_t headerIndex = 0;
            
            while (std::getline(ss, cell, ','))
            {
                cell.erase(cell.find_last_not_of(" \t\n") + 1);
                cell.erase(0, cell.find_first_not_of(" \t\n"));
                
                if (headerIndex < headers.size())
                {
                    if (internal::isNumber(cell))
                    {
                        try
                        {
                            size_t pos;
                            int intValue = std::stoi(cell, &pos);
                            if (pos == cell.size())
                            {
                                jsonObject[headers[headerIndex]] = intValue;
                            }
                            else
                            {
                                jsonObject[headers[headerIndex]] = std::stod(cell);
                            }
                        }
                        catch (...)
                        {
                            jsonObject[headers[headerIndex]] = cell;
                        }
                    }
                    else
                    {
                        jsonObject[headers[headerIndex]] = cell;
                    }
                }
                headerIndex++;
            }
            jsonArray.append(jsonObject);
        }

        result = jsonArray;

        file.close();
    }
    else
    {
        std::cerr << "ERROR FileJSON: can't open \"" << input << "\"in \"CSystemModule::SFileJSON::fromCSV\"\n";
    }

    return result;
}

bool CSystemModule::SFileJSON::save(const Json::Value & input, const std::string & output)
{
    bool result = false;

    std::ofstream outFile(output);
    if (outFile.is_open())
    {
        Json::StreamWriterBuilder writer;

        writer["indentation"] = "    ";

        std::string jsonString = Json::writeString(writer, input);

        outFile << jsonString;
        outFile.close();

        result = true;
    }
    else
    {
        std::cerr << "ERROR FileJSON: can't save file to \"" << output << "\" in \"CSystemModule::SFileJSON::save\"\n";
    }

    return result;
}
bool CSystemModule::SFileJSON::saveToCSV(const std::string &input, const std::string &output)
{
    bool result = false;

    std::ifstream jsonFile(input);
    if (!jsonFile.is_open())
    {
        std::cerr << "ERROR FileJSON: can't open JSON file \"" << input << "\" in \"CSystemModule::SFileJSON::saveToCSV\"\n";
        return result;
    }

    Json::CharReaderBuilder readerBuilder;
    Json::Value jsonData;
    std::string errs;

    if (!Json::parseFromStream(readerBuilder, jsonFile, &jsonData, &errs))
    {
        std::cerr << "ERROR FileJSON: failed to parse json: \"" << errs << "\" in \"CSystemModule::SFileJSON::saveToCSV(\"\n";
        return result;
    }
    jsonFile.close();

    // Open CSV file for writing
    std::ofstream csvFile(output);
    if (!csvFile.is_open())
    {
        std::cerr << "ERROR FileJSON: can't open CSV file " << output << "\" in \"CSystemModule::SFileJSON::saveToCSV\"\n";
        return result;
    }

    if (jsonData.isArray() && !jsonData.empty())
    {
        // Write CSV header
        const Json::Value& firstObject = jsonData[0];
        for (auto it = firstObject.begin(); it != firstObject.end(); ++it)
        {
            if (it != firstObject.begin())
            {
                csvFile << ",";
            }
            csvFile << it.key().asString();
        }
        csvFile << "\n";

        // Write CSV rows
        for (const auto& obj : jsonData)
        {
            for (auto it = firstObject.begin(); it != firstObject.end(); ++it)
            {
                if (it != firstObject.begin())
                {
                    csvFile << ",";
                }
                csvFile << obj[it.key().asString()].asString();
            }
            csvFile << "\n";
        }

        result = true;
    }
    else
    {
        std::cerr << "ERROR FileJSON: json data is not an array or is empty" << " in \"CSystemModule::SFileJSON::saveToCSV\"\n";
    }
    csvFile.close();

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_JSONCPP

namespace utilityFunction
{

    namespace directory
    {
        bool createDirectory(const std::string &path)
        {
            CSystemModule SYSTEM;
            return SYSTEM.Directory.createDirectory(path);
        }

        bool deleteDirectory(const std::string &path)
        {
            CSystemModule SYSTEM;
            return SYSTEM.Directory.deleteDirectory(path);
        }

        std::string getCurrentDir()
        {
            CSystemModule SYSTEM;
            return SYSTEM.Directory.getCurrentDir();
        }
    } // namespace directory

    #if LIBPRCPP_PROJECT_USING_LIBHARU
    namespace filePdf
    {
        bool generateTable(const std::vector<std::vector<std::string>> &tableData, const std::string &filePathName, const TPdfConfig &pdfConfig)
        {
            CSystemModule SYSTEM;
            return SYSTEM.FilePDF.generateTable(tableData, filePathName, pdfConfig);
        }
    } // namespace filePdf
    #endif // LIBPRCPP_PROJECT_USING_LIBHARU

    #if LIBPRCPP_PROJECT_USING_JSONCPP
    namespace json
    {
        std::string toString(const Json::Value &input, const int &indent, const int &precision)
        {
            CSystemModule SYSTEM;
            return SYSTEM.FileJSON.toString(input, indent, precision);
        }

        Json::Value fromFile(const std::string &input)
        {
            CSystemModule SYSTEM;
            return SYSTEM.FileJSON.fromFile(input);
        }

        Json::Value fromString(const std::string &input, const int &indent, const int &precision)
        {
            CSystemModule SYSTEM;
            return SYSTEM.FileJSON.fromString(input, indent, precision);
        }

        Json::Value fromCSV(const std::string &input)
        {
            CSystemModule SYSTEM;
            return SYSTEM.FileJSON.fromCSV(input);
        }

        bool save(const Json::Value &input, const std::string &output)
        {
            CSystemModule SYSTEM;
            return SYSTEM.FileJSON.save(input, output);
        }

        bool saveToCSV(const std::string &input, const std::string &output)
        {
            CSystemModule SYSTEM;
            return SYSTEM.FileJSON.saveToCSV(input, output);
        }
    } // namespace json
#endif // LIBPRCPP_PROJECT_USING_JSONCPP

} // namespace utilityFunction

} // namespace libprcpp
