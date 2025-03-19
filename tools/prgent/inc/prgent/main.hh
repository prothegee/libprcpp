#ifndef PRGENT_MAIN_HH
#define PRGENT_MAIN_HH
#include <libprcpp/config.hh>
#include <libprcpp/constants/files_const.hh>
#include <libprcpp/functions/utility_funcs.hh>
#include <libprcpp/functions/date_and_times_funcs.hh>
#include <libprcpp/functions/images_funcs.hh>
#include <libprcpp/types/base_types.hh>
#include <libprcpp/types/batch_types.hh>

#include <string>

using namespace libprcpp;

namespace prgent
{

#pragma region internal
namespace log
{

void okBase()
{
    std::printf("# prgent ok:\n");
}

void errorBase()
{
    std::printf("# prgent error:\n");
}

void noticeBase()
{
    std::printf("# prgent notice:\n");
}

void warningBase()
{
    std::printf("# prgent warning:\n");
}

void showHelpBaseHint()
{
    std::printf("###### prgent usage:\n");
    std::printf("--help: show this help message\n\n");
    // std::printf("--help: show this help message\n    - to show supported mode usage use \"--help mode\"\n\n");
    std::printf("--mode: specify the mode use number or string\n    - e.g.: 1:barcode-encode 3:qrcode-encode\n\n");
    std::printf("--input: input file path\n\n");
    std::printf("--output: output file path\n\n");
    std::printf("--output-dir: output directory/folder\n\n");
    std::printf("--output-ext: output extension name\n   - encode barcode & qrcode, only supported .svg, .png, .jpg, .jpeg, use .svg by default if not supply\n\n");
    std::printf("--image-size: specify image size in NNNxNNN format, where N is must numeric as pixel/px\n   - 256x256 px is default size\n   - .svg will ignore size\n\n");
    std::printf("--image-margin: specify margin of image\n   - only support for barcode & qrcode encode\n\n");
    std::printf("--batch-iter: create batch iteration from value of number\n   - only allowed number\n   - can't be less/equal to 0\n   - only support for barcode & qrcode encode\n\n");
    std::printf("--batch-out-csv: create output of batch record to csv file\n   - only apply if true\n\n");
    std::printf("--batch-out-json: create output of batch record to json file\n   - only apply if true\n\n");
    std::printf("###### end of prgent usage\n");
}

void showHelpConfigurations(const std::string &helpHint)
{
    std::printf("TODO: help is using arg of %s", helpHint.c_str());
}

} // namespace log


/**
 * @brief prgent generate mode enum
 */
enum EGenerateMode : TI32
{
    GENERATE_MODE_UNDEFINED,
    GENERATE_MODE_BARCODE_ENCODE,
    GENERATE_MODE_BARCODE_DECODE,
    GENERATE_MODE_QRCODE_ENCODE,
    GENERATE_MODE_QRCODE_DECODE,
};


/**
 * @brief prgent return main result enum
 */
enum EReturnMainResult : TI32
{
    RETURN_MAIN_RESULT_OK,
    RETURN_MAIN_RESULT_SHOW_HELP,
    RETURN_MAIN_RESULT_GENERATE_MODE_IS_UNDEFINED,
    RETURN_MAIN_RESULT_GENERATE_MODE_NOT_SUPPORTED,
    RETURN_MAIN_RESULT_ERROR_INPUT_IS_REQUIRED,
    RETURN_MAIN_RESULT_ERROR_FILE_ALREADY_EXISTS,
    RETURN_MAIN_RESULT_ERROR_ENCODE_IMAGE,
    RETURN_MAIN_RESULT_ERROR_INVALID_IMAGE_SIZE,
    RETURN_MAIN_RESULT_ERROR_INPUT_EXTENSION_IS_NOT_ALLOWED,
    RETURN_MAIN_RESULT_ERROR_DECODE_FAIL,
    RETURN_MAIN_RESULT_ERROR_BATCH_ITER_FAIL_DUE_MODE,
    RETURN_MAIN_RESULT_ERROR_BATCH_ITER_CANT_ZERO_VALUE,
    RETURN_MAIN_RESULT_ERROR_BATCH_ITER_NOT_NUMERIC,
    RETURN_MAIN_RESULT_ERROR_BATCH_OUT_FAIL_CSV,
    RETURN_MAIN_RESULT_ERROR_BATCH_OUT_FAIL_JSON,
    RETURN_MAIN_RESULT_ERROR_BATCH_OUT_ALREADY_EXISTS_CSV,
    RETURN_MAIN_RESULT_ERROR_BATCH_OUT_ALREADY_EXISTS_JSON,
    RETURN_MAIN_RESULT_ERROR_DEFAULT, // last option/position
};


inline static const TChr *ARG_IS_HELP = "--help"; // arg for `--help`
inline static const TChr *ARG_IS_MODE = "--mode"; // arg for `--mode`
inline static const TChr *ARG_IS_INPUT = "--input"; // arg for `--input`
inline static const TChr *ARG_IS_OUTPUT = "--output"; // arg for `--output`
inline static const TChr *ARG_IS_OUTPUT_DIR = "--output-dir"; // arg for `--output-dir`
inline static const TChr *ARG_IS_OUTPUT_EXT = "--output-ext"; // arg for `--output-ext`
inline static const TChr *ARG_IS_IMAGE_SIZE = "--image-size"; // arg for `--image-size` apply NNNxNNN where N is numeric value
inline static const TChr *ARG_IS_IMAGE_MARGIN = "--image-margin"; // arg for `--image-margin`
inline static const TChr *ARG_IS_BATCH_ITER = "--batch-iter"; // arg for `--image-margin`
inline static const TChr *ARG_IS_BATCH_OUT_CSV = "--batch-out-csv"; // arg for `--batch-out-csv`
inline static const TChr *ARG_IS_BATCH_OUT_JSON = "--batch-out-json"; // arg for `--batch-out-json`


inline static const TChr *GENERATE_MODE_BARCODE_ENCODE_ARG_AS_NUM = "1"; // "1"
inline static const TChr *GENERATE_MODE_BARCODE_ENCODE_ARG_AS_STR = "barcode-encode"; // "barcode-encode"

inline static const TChr *GENERATE_MODE_BARCODE_DECODE_AS_NUM = "2"; // "2"
inline static const TChr *GENERATE_MODE_BARCODE_DECODE_AS_STR = "barcode-decode"; // "barcode-decode"

inline static const TChr *GENERATE_MODE_QRCODE_ENCODE_ARG_AS_NUM = "3"; // "3"
inline static const TChr *GENERATE_MODE_QRCODE_ENCODE_ARG_AS_STR = "qrcode-encode"; // "qrcode-encode"

inline static const TChr *GENERATE_MODE_QRCODE_DECODE_AS_NUM = "4"; // "4"
inline static const TChr *GENERATE_MODE_QRCODE_DECODE_AS_STR = "qrcode-decode"; // "qrcode-decode"


const std::vector<std::string> ALLOWED_MODE_IMAGE_EXTENSIONS = {
    "jpeg",
    "jpg",
    "png",
    "svg",
};


bool parseSizeArg(const std::string &sizeStr, TI32 &width, TI32 &height)
{
    // check if the string contains exactly one 'x'
    size_t xPos = sizeStr.find('x');
    if (xPos == std::string::npos || xPos == 0 || xPos == sizeStr.length() - 1)
    {
        return false; // no 'x' found, or 'x' is at the beginning/end
    }

    // split the string into width and height parts
    std::string widthStr = sizeStr.substr(0, xPos);
    std::string heightStr = sizeStr.substr(xPos + 1);

    // check if both parts are numeric
    for (char c : widthStr)
    {
        if (!isdigit(c))
        {
            return false; // non-numeric character in width
        }
    }
    for (char c : heightStr)
    {
        if (!isdigit(c))
        {
            return false; // non-numeric character in height
        }
    }

    // convert the strings to integers
    width = std::stoi(widthStr);
    height = std::stoi(heightStr);

    return true;
}

std::string getFileExtension(const std::string &filePath)
{
    std::filesystem::path path(filePath);
    std::string extension = path.extension().string();

    // remove the leading dot (e.g., ".jpg" -> "jpg")
    if (!extension.empty() && extension[0] == '.')
    {
        extension.erase(0, 1);
    }

    return extension;
}

std::string validateAllowedImageFileExtension(const std::string &fileExtension, const char *argKey = "")
{
    bool found = false;
    std::string result;

    for (auto &extension : ALLOWED_MODE_IMAGE_EXTENSIONS)
    {
        if (fileExtension == extension)
        {
            found = true;
            result = "." + fileExtension;
            break;
        }
    }

    if (!found)
    {
        if (!std::string(argKey).empty())
        {
            std::cout << argKey << " file extension not supported, use .svg instead\n";
        }
        result = FILE_EXTENSION_IS_SVG_HINT;
    }

    return result;
}


bool isExtensionAllowed(const std::string &filePath, const std::vector<std::string> &allowedExtensions)
{
    std::string extension = getFileExtension(filePath);

    // force convert extension to lowercase for case-insensitive comparison
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    // check if the extension is in the allowed list
    return std::find(allowedExtensions.begin(), allowedExtensions.end(), extension) != allowedExtensions.end();
}


TI32 countCsvRows(const std::string &filePath)
{
    int rowCount = 0;
    std::string line;
    std::ifstream file(filePath);

    while (std::getline(file, line))
    {
        rowCount++;
    }
    file.close();

    return rowCount - 1;
}

TI32 countJsonEntries(const std::string &filePath)
{
    std::string errs;
    Json::Value jsonData;
    std::ifstream file(filePath);
    Json::CharReaderBuilder reader;

    if (!parseFromStream(reader, file, &jsonData, &errs))
    {
        log::errorBase();
        std::printf("- failed to parse JSON file: %s\n", errs.c_str());
        return 0;
    }
    file.close();

    return jsonData.size();
}
#pragma endregion


int mainProcess(int argc, char *argv[])
{
    bool argHelpInUse = false;
    bool argBatchInUse = false;
    bool supportsImageSizeAndMargin = false;

    // default value for size in pixel/px
    TI32 sizeWidth = 256, sizeHeight = 256, sizeMargin = 0;

    TI32 batchIter = 0;

    EGenerateMode generateMode = GENERATE_MODE_UNDEFINED;

    std::string helpStr;

    std::string generateModeStr;

    std::string inputStr;

    std::string outputStr, outputDirStr, outputExtStr, outputDecodedStr;

    std::string imageSizeStr, imageSizeWidthStr, imageSizeHeightStr, imageSizeMarginStr;

    std::string batchIterStr, batchOutCsv, batchOutJson;

    for (TI32 i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        if (arg == ARG_IS_HELP) // this arg is "--help"
        {
            argHelpInUse = true;

            if (i + 1 < argc)
            {
                helpStr = argv[i + 1];
                i++;
            }
            break;

        }
        else if (arg == ARG_IS_MODE) // this arg is "--mode"
        {
            if
            (
                i + 1 < argc && std::string(argv[i + 1]) == GENERATE_MODE_BARCODE_ENCODE_ARG_AS_NUM // 1
                ||
                i + 1 < argc && std::string(argv[i + 1]) == GENERATE_MODE_BARCODE_ENCODE_ARG_AS_STR // barcode-encode
            )
            {
                generateMode = GENERATE_MODE_BARCODE_ENCODE;
                generateModeStr = GENERATE_MODE_BARCODE_ENCODE_ARG_AS_STR;
                i++;
            }
            else if
            (
                i + 1 < argc && std::string(argv[i + 1]) == GENERATE_MODE_BARCODE_DECODE_AS_NUM // 2
                ||
                i + 1 < argc && std::string(argv[i + 1]) == GENERATE_MODE_BARCODE_DECODE_AS_STR // barcode-decode
            )
            {
                generateMode = GENERATE_MODE_BARCODE_DECODE;
                generateModeStr = GENERATE_MODE_BARCODE_DECODE_AS_STR;
                i++;
            }
            else if
            (
                i + 1 < argc && std::string(argv[i + 1]) == GENERATE_MODE_QRCODE_ENCODE_ARG_AS_NUM // 3
                ||
                i + 1 < argc && std::string(argv[i + 1]) == GENERATE_MODE_QRCODE_ENCODE_ARG_AS_STR // qrcode-encode
            )
            {
                generateMode = GENERATE_MODE_QRCODE_ENCODE;
                generateModeStr = GENERATE_MODE_QRCODE_ENCODE_ARG_AS_STR;
                i++;
            }
            else if
            (
                i + 1 < argc && std::string(argv[i + 1]) == GENERATE_MODE_QRCODE_DECODE_AS_NUM // 4
                ||
                i + 1 < argc && std::string(argv[i + 1]) == GENERATE_MODE_QRCODE_DECODE_AS_STR // qrcode-encode
            )
            {
                generateMode = GENERATE_MODE_QRCODE_DECODE;
                generateModeStr = GENERATE_MODE_QRCODE_DECODE_AS_STR;
                i++;
            }

            if (generateMode == GENERATE_MODE_BARCODE_ENCODE || generateMode == GENERATE_MODE_QRCODE_ENCODE) // image size & margin validation
            {
                supportsImageSizeAndMargin = true;
            }
        }
        else if (arg == ARG_IS_INPUT) // this arg is "--input"
        {
            if (i + 1 < argc)
            {
                inputStr = argv[i + 1];
                i++;
            }
        }
        else if (arg == ARG_IS_OUTPUT) // this arg is "--output"
        {
            if (i + 1 < argc)
            {
                outputStr = argv[i + 1];
                i++;
            }
        }
        else if (arg == ARG_IS_OUTPUT_DIR) // this arg is "--output-dir"
        {
            if (i + 1 < argc)
            {
                outputDirStr = argv[i + 1];
                i++;
            }
        }
        else if (arg == ARG_IS_OUTPUT_EXT) // this arg is "--output-ext"
        {
            if (i + 1 < argc)
            {
                outputExtStr = argv[i + 1];
                i++;
            }
        }
        else if (arg == ARG_IS_IMAGE_SIZE) // this arg is "--image-size" format NNNxNNN where N is numeric value
        {
            if (supportsImageSizeAndMargin && i + 1 < argc)
            {
                imageSizeStr = argv[i + 1]; // also ignore if --output-ext is svg

                if (parseSizeArg(imageSizeStr, sizeWidth, sizeHeight))
                {
                    i++;
                }
                else
                {
                    log::errorBase();
                    std::printf("Invalid --image-size format. Expected format: NNNxNNN (e.g. 128x64)\n");
                    return RETURN_MAIN_RESULT_ERROR_INVALID_IMAGE_SIZE;
                }
            }
            else if (!supportsImageSizeAndMargin)
            {
                log::noticeBase();
                std::printf("--image-size is ignored for mode: %s\n", generateModeStr.c_str());
                i++;
            }
        }
        else if (arg == ARG_IS_IMAGE_MARGIN) // this arg is "--image-margin" only numeric value
        {
            if (supportsImageSizeAndMargin && i + 1 < argc)
            {
                imageSizeMarginStr = argv[i + 1];

                if (utilityFunctions::isNumeric(imageSizeMarginStr))
                {
                    sizeMargin = std::stoi(imageSizeMarginStr);
                    i++;
                }
            }
            else if (!supportsImageSizeAndMargin)
            {
                log::noticeBase();
                std::printf("--image-margin is ignored for mode: %s\n", generateModeStr.c_str());
                i++;
            }
        }
        else if (arg == ARG_IS_BATCH_ITER) // this arg is "--batch-iter" only numeric 
        {
            batchIterStr = argv[i + 1];

            if (utilityFunctions::isNumeric(batchIterStr))
            {
                batchIter = std::stoi(batchIterStr);

                if (batchIter >= 1)
                {
                    argBatchInUse = true;
                    i++;
                }
                else
                {
                    log::errorBase();
                    std::printf("--batch-iter can't be zero value");
                    return RETURN_MAIN_RESULT_ERROR_BATCH_ITER_CANT_ZERO_VALUE;
                }
            }
            else
            {
                log::errorBase();
                std::printf("--batch-iter must numeric value");
                return RETURN_MAIN_RESULT_ERROR_BATCH_ITER_NOT_NUMERIC;
            }
        }
        else if (arg == ARG_IS_BATCH_OUT_CSV) // this arg is "--batch-out-csv", only accept "true"
        {
            if (i + 1 < argc)
            {
                batchOutCsv = argv[i + 1];
                i++;
            }
        }
        else if (arg == ARG_IS_BATCH_OUT_JSON) // this arg is "--batch-out-json", only accept "true"
        {
            if (i + 1 < argc)
            {
                batchOutJson = argv[i + 1];
                i++;
            }
        }
    }

    //////////////////////////////////////////////////////

    if (argHelpInUse) // break if --help in use
    {
        log::noticeBase();

        if (helpStr.empty())
            log::showHelpBaseHint();
        else
            log::showHelpConfigurations(helpStr);

        return RETURN_MAIN_RESULT_SHOW_HELP;
    }

    if (sizeWidth < 256)
    {
        log::warningBase();
        std::printf("- image width is to small, force set it to 256px\n");
        sizeWidth = 256;
    }

    if (sizeHeight < 256)
    {
        log::warningBase();
        std::printf("- image height is to small, force set it to 256px\n");
        sizeHeight = 256;
    }

    if (sizeMargin < 0)
    {
        log::warningBase();
        std::printf("- margin can't be negative value, force set to 0\n");
        sizeMargin = 0;
    }

    //////////////////////////////////////////////////////

    bool batchModeFail = false; // TF64 check

    std::vector<std::string> batchIds;

    // future object storage for batch id & save csv/json
    std::vector<std::future<std::string>> futureBatchCsv, futureBatchJson;

    // only used for encode
    auto generateBatchEncode = [&](TI32 batchNum, std::string timestampObject) -> std::string
    {
        std::string result;

        // create output if empty
        if (argBatchInUse && outputStr.empty())
        {
            outputStr = inputStr;
        }

        // create dir if batch iter in use while output dir empty
        if (argBatchInUse && outputDirStr.empty())
        {
            std::filesystem::create_directories(inputStr);
            outputDirStr = inputStr; // assign output since it batch and empty from inputStr
        }

        // if output dir not empty and batch iter is in use, create it too
        if (argBatchInUse && !outputDirStr.empty())
        {
            std::filesystem::create_directories(outputDirStr);
        }

        // if output extension is mepty and batch in use, set the extension
        if (argBatchInUse && outputExtStr.empty())
        {
            outputExtStr = FILE_EXTENSION_IS_SVG_HINT;
        }

        switch (generateMode)
        {
            case GENERATE_MODE_BARCODE_ENCODE:
            {
                result = outputDirStr + "/" + outputStr + "-" + timestampObject + "-" + std::to_string(batchNum) + "." + outputExtStr;

                imagesFunctions::barcode::encode(std::string(outputStr + "-" + timestampObject + std::to_string(batchNum)), result, sizeWidth, sizeHeight, sizeMargin);
            }
            break;

            case GENERATE_MODE_QRCODE_ENCODE:
            {
                result = outputDirStr + "/" + outputStr + "-" + timestampObject + "-" + std::to_string(batchNum) + "." + outputExtStr;

                imagesFunctions::qrcode::encode(std::string(outputStr + "-" + timestampObject + std::to_string(batchNum)), result, sizeWidth, sizeHeight, sizeMargin);
            }
            break;

            default:
            {
                batchModeFail = true;
            }
            break;
        }

        return result;
    };

    if (batchModeFail)
    {
        log::errorBase();
        std::printf("- this mode (%d) batch iter not supported, only 1:barcode-encode & 3:qrcode-encode is allowed\n", (int)generateMode);
        return RETURN_MAIN_RESULT_ERROR_BATCH_ITER_FAIL_DUE_MODE;
    }

    //////////////////////////////////////////////////////

    // process what generate mode is
    switch (generateMode)
    {
        case GENERATE_MODE_BARCODE_ENCODE:
        {
            std::printf("###### prgent mode %s:%s\n", GENERATE_MODE_BARCODE_ENCODE_ARG_AS_NUM, GENERATE_MODE_BARCODE_ENCODE_ARG_AS_STR);

            if (inputStr.empty())
            {
                log::errorBase();
                std::printf("--input is requied\n");
                return RETURN_MAIN_RESULT_ERROR_INPUT_IS_REQUIRED;
            }

            // check batch or not
            if (!argBatchInUse)
            {
                if (outputStr.empty())
                {
                    std::printf("--output arg is not supplied, using default output from input\n");
                    outputStr = inputStr;
                }

                // re-evaluate outputStr
                for (auto chr : STRINGS_INTERNAL::special_character)
                {
                    std::string query(1, chr);
                    utilityFunctions::find::andReplaceAll(outputStr, query, "-");
                }

                if (outputDirStr.empty())
                {
                    std::printf("--output-dir arg is not supplied, using current path as output dir\n");
                }
                else
                {
                    if (!outputDirStr.empty() && !std::filesystem::exists(outputDirStr))
                    {
                        std::filesystem::create_directories(outputDirStr);
                    }

                    outputStr = outputDirStr + "/" + outputStr;
                }

                if (outputExtStr.empty())
                {
                    std::printf("--output-dir arg is not supplied, using default output ext as .svg\n");
                    outputStr += FILE_EXTENSION_IS_SVG_HINT; // use .svg
                }
                else
                {
                    outputStr += validateAllowedImageFileExtension(outputExtStr, ARG_IS_OUTPUT_EXT); // default will return .svg
                }

                // break if already exists
                if (std::filesystem::exists(outputStr))
                {
                    log::errorBase();
                    std::printf("- \"%s\" already exists\n", outputStr.c_str());
                    return RETURN_MAIN_RESULT_ERROR_FILE_ALREADY_EXISTS;
                }

                if (imagesFunctions::barcode::encode(inputStr, outputStr, sizeWidth, sizeHeight, sizeMargin)) // generate barcode
                {
                    std::printf("output save as: %s", outputStr.c_str());
                }
                else
                {
                    log::errorBase();
                    std::printf("fail to encode image for barcode from text");
                    return RETURN_MAIN_RESULT_ERROR_ENCODE_IMAGE;
                }
            }
            else
            {
                if (outputStr.empty())
                {
                    std::printf("--output arg is not supplied, using default output from input\n");
                    outputStr = inputStr;
                }

                // re-evaluate outputStr
                for (auto chr : STRINGS_INTERNAL::special_character)
                {
                    std::string query(1, chr);
                    utilityFunctions::find::andReplaceAll(outputStr, query, "-");
                }

                std::string batchCsv = outputStr + "-batch.csv";
                std::string batchJson = outputStr + "-batch.json";

                for (TI32 i = 1; i <= batchIter; i++)
                {

                    auto localTime = dateAndTimesFunctions::localTimeZone();
                    auto iterTimestampObject = dateAndTimesFunctions::UTC::YYYYMMDDhhmmssms::toString(localTime);

                    // NOTE: iterRes has their own purpose

                    std::string iterBatchId = inputStr + "-" + iterTimestampObject + "-" + std::to_string(i);

                    if (batchOutCsv == "true")
                    {
                        std::future<std::string> iterRes = std::async(std::launch::async, generateBatchEncode, i, iterTimestampObject);

                        futureBatchCsv.push_back(std::move(iterRes));
                        batchIds.push_back(iterBatchId);
                    }

                    if (batchOutJson == "true")
                    {
                        std::future<std::string> iterRes = std::async(std::launch::async, generateBatchEncode, i, iterTimestampObject);

                        futureBatchJson.push_back(std::move(iterRes));
                        batchIds.push_back(iterBatchId);
                    }

                    if (batchOutCsv != "true" && batchOutJson != "true")
                    {
                        std::future<std::string> iterRes = std::async(std::launch::async, generateBatchEncode, i, iterTimestampObject);
                    }
                }

                log::okBase();
                std::printf("- batch encode barcode saved in \"%s\"\n", outputDirStr.c_str());
            }
        }
        break;

        case GENERATE_MODE_QRCODE_ENCODE:
        {
            std::printf("###### prgent mode %s:%s\n", GENERATE_MODE_QRCODE_DECODE_AS_NUM, GENERATE_MODE_QRCODE_DECODE_AS_STR);

            if (inputStr.empty())
            {
                log::errorBase();
                std::printf("--input is requied\n");
                return RETURN_MAIN_RESULT_ERROR_INPUT_IS_REQUIRED;
            }

            // check batch or not
            if (!argBatchInUse)
            {
                if (outputStr.empty())
                {
                    std::printf("--output arg is not supplied, using default output from input\n");
                    outputStr = inputStr;
                }

                // re-evaluate outputStr
                for (auto chr : STRINGS_INTERNAL::special_character)
                {
                    std::string query(1, chr);
                    utilityFunctions::find::andReplaceAll(outputStr, query, "-");
                }

                if (outputDirStr.empty())
                {
                    std::printf("--output-dir arg is not supplied, using current path as output dir\n");
                }
                else
                {
                    if (!outputDirStr.empty() && !std::filesystem::exists(outputDirStr))
                    {
                        std::filesystem::create_directories(outputDirStr);
                    }

                    outputStr = outputDirStr + "/" + outputStr;
                }

                if (outputExtStr.empty())
                {
                    std::printf("--output-dir arg is not supplied, using default output ext as .svg\n");
                    outputStr += FILE_EXTENSION_IS_SVG_HINT; // use .svg
                }
                else
                {
                    outputStr += validateAllowedImageFileExtension(outputExtStr, ARG_IS_OUTPUT_EXT); // default will return .svg
                }

                // break if already exists
                if (std::filesystem::exists(outputStr))
                {
                    log::errorBase();
                    std::printf("- \"%s\" already exists\n", outputStr.c_str());
                    return RETURN_MAIN_RESULT_ERROR_FILE_ALREADY_EXISTS;
                }

                if (imagesFunctions::qrcode::encode(inputStr, outputStr, sizeWidth, sizeHeight, sizeMargin)) // generate qrcode
                {
                    std::printf("output save as: %s", outputStr.c_str());
                }
                else
                {
                    log::errorBase();
                    std::printf("fail to encode image for qrcode from text");
                    return RETURN_MAIN_RESULT_ERROR_ENCODE_IMAGE;
                }
            }
            else
            {
                if (outputStr.empty())
                {
                    std::printf("--output arg is not supplied, using default output from input\n");
                    outputStr = inputStr;
                }

                // re-evaluate outputStr
                for (auto chr : STRINGS_INTERNAL::special_character)
                {
                    std::string query(1, chr);
                    utilityFunctions::find::andReplaceAll(outputStr, query, "-");
                }

                std::string batchCsv = outputStr + "-batch.csv";
                std::string batchJson = outputStr + "-batch.json";

                for (TI32 i = 1; i <= batchIter; i++)
                {
                    auto localTime = dateAndTimesFunctions::localTimeZone();
                    auto iterTimestampObject = dateAndTimesFunctions::UTC::YYYYMMDDhhmmssms::toString(localTime);

                    // NOTE: iterRes has their own purpose

                    std::string iterBatchId = inputStr + "-" + iterTimestampObject + "-" + std::to_string(i);

                    if (batchOutCsv == "true")
                    {
                        std::future<std::string> iterRes = std::async(std::launch::async, generateBatchEncode, i, iterTimestampObject);

                        futureBatchCsv.push_back(std::move(iterRes));
                        batchIds.push_back(iterBatchId);
                    }

                    if (batchOutJson == "true")
                    {
                        std::future<std::string> iterRes = std::async(std::launch::async, generateBatchEncode, i, iterTimestampObject);

                        futureBatchJson.push_back(std::move(iterRes));
                        batchIds.push_back(iterBatchId);
                    }

                    if (batchOutCsv != "true" && batchOutJson != "true")
                    {
                        std::future<std::string> iterRes = std::async(std::launch::async, generateBatchEncode, i, iterTimestampObject);
                    }
                }

                log::okBase();
                std::printf("- batch encode qrcode saved in \"%s\"\n", outputDirStr.c_str());
            }
        }
        break;

        case GENERATE_MODE_BARCODE_DECODE:
        {
            std::printf("###### prgent mode %s:%s\n", GENERATE_MODE_BARCODE_DECODE_AS_NUM, GENERATE_MODE_BARCODE_DECODE_AS_STR);

            if (inputStr.empty())
            {
                log::errorBase();
                std::printf("--input is requied\n");
                return RETURN_MAIN_RESULT_ERROR_INPUT_IS_REQUIRED;
            }

            if (!isExtensionAllowed(inputStr, ALLOWED_MODE_IMAGE_EXTENSIONS))
            {
                log::errorBase();
                std::printf("--input file extension is not allowed, allowed file extension for this mode\n");
                for (auto &extension : ALLOWED_MODE_IMAGE_EXTENSIONS)
                {
                    std::printf("- %s\n", extension.c_str());
                }
                return RETURN_MAIN_RESULT_ERROR_INPUT_EXTENSION_IS_NOT_ALLOWED;
            }

            if (!imagesFunctions::barcode::decode(inputStr, outputDecodedStr))
            {
                log::errorBase();
                std::printf("can't decode barcode from %s\n", inputStr.c_str());
                return RETURN_MAIN_RESULT_ERROR_DECODE_FAIL;
            }
            else
            {
                log::okBase();
                std::printf("decode result:\n------ START BARCODE DECODE ------\n%s\n------  END BARCODE DECODE  ------\n", outputDecodedStr.c_str());
            }
        }
        break;

        case GENERATE_MODE_QRCODE_DECODE:
        {
            std::printf("###### prgent mode %s:%s\n", GENERATE_MODE_BARCODE_DECODE_AS_NUM, GENERATE_MODE_BARCODE_DECODE_AS_STR);

            if (inputStr.empty())
            {
                log::errorBase();
                std::printf("--input is requied\n");
                return RETURN_MAIN_RESULT_ERROR_INPUT_IS_REQUIRED;
            }

            if (!isExtensionAllowed(inputStr, ALLOWED_MODE_IMAGE_EXTENSIONS))
            {
                log::errorBase();
                std::printf("--input file extension is not allowed, allowed file extension for this mode\n");
                for (auto &extension : ALLOWED_MODE_IMAGE_EXTENSIONS)
                {
                    std::printf("- %s\n", extension.c_str());
                }
                return RETURN_MAIN_RESULT_ERROR_INPUT_EXTENSION_IS_NOT_ALLOWED;
            }

            if (!imagesFunctions::qrcode::decode(inputStr, outputDecodedStr))
            {
                log::errorBase();
                std::printf("can't decode qrcode from %s\n", inputStr.c_str());
                return RETURN_MAIN_RESULT_ERROR_DECODE_FAIL;
            }
            else
            {
                log::okBase();
                std::printf("decode result:\n------ START QRCODE DECODE ------\n%s\n------  END QRCODE DECODE  ------\n", outputDecodedStr.c_str());
            }
        }
        break;

        default:
        {
            log::errorBase();
            log::showHelpBaseHint();
            return RETURN_MAIN_RESULT_GENERATE_MODE_NOT_SUPPORTED;
        }
        break;
    }

    //////////////////////////////////////////////////////

    // process --batch-out-csv
    if (batchOutCsv == "true" && argBatchInUse)
    {
        if (outputStr.empty())
        {
            outputStr = inputStr;
        }

        std::string csvHeader; // to write csv header
        std::string fileOutput = outputStr + "-batch.csv"; // output csv
        bool extendFile = false;

        // check if the file exists
        if (std::filesystem::exists(fileOutput))
        {
            std::cout << "file \"" << fileOutput << "\" already exists with " << countCsvRows(fileOutput) << " entries.\n";
            
            // prompt the user to extend the file
            char choice;
            do
            {
                std::cout << "do you want to extend it? (y/n): ";
                std::cin >> choice;
                choice = static_cast<char>(std::tolower(choice)); // ensure lowercase for comparison

                // clear the input buffer to handle any extra characters
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } while (choice != 'y' && choice != 'n');

            if (choice == 'y')
            {
                extendFile = true;
            }
            else
            {
                log::errorBase();
                std::printf("- \"%s\" already exists\n", fileOutput.c_str());
                return RETURN_MAIN_RESULT_ERROR_BATCH_OUT_ALREADY_EXISTS_CSV;
            }
        }

        std::ofstream csvFile;
        if (extendFile)
        {
            csvFile.open(fileOutput, std::ios::app); // append mode
        }
        else
        {
            csvFile.open(fileOutput); // a new file mode

            // create csv header if creating a new file
            csvHeader += TBatchOutRecordDefault_HINT::id;
            csvHeader += ",";
            csvHeader += TBatchOutRecordDefault_HINT::batch_id;
            csvHeader += ",";
            csvHeader += TBatchOutRecordDefault_HINT::batch_origin;
            csvHeader += ",";
            csvHeader += TBatchOutRecordDefault_HINT::batch_result;
            csvHeader += ",";
            csvHeader += TBatchOutRecordDefault_HINT::timestamp_created;
            csvHeader += ",";
            csvHeader += TBatchOutRecordDefault_HINT::owned;
            csvHeader += ",";
            csvHeader += TBatchOutRecordDefault_HINT::owner;
            csvHeader += ",";
            csvHeader += TBatchOutRecordDefault_HINT::claimed_date_and_time;
            csvHeader += ",";
            csvHeader += TBatchOutRecordDefault_HINT::claimed_date_and_time_num;
            csvHeader += "\n"; // end of the csv file header

            csvFile << csvHeader;
        }

        if (!csvFile.is_open())
        {
            log::errorBase();
            std::printf("- unable to write to .csv for \"%s\"\n", fileOutput.c_str());
            csvFile.close();
            return RETURN_MAIN_RESULT_ERROR_BATCH_OUT_FAIL_CSV;
        }

        // calculate the starting ID for new rows
        TI32 startId = extendFile ? countCsvRows(fileOutput) + 1 : 1;

        // cenerate batch IDs and file names
        for (TI32 i = startId; i <= startId + batchIter - 1; i++)
        {
            auto localTime = dateAndTimesFunctions::localTimeZone();
            auto iterTimestampObject = dateAndTimesFunctions::UTC::YYYYMMDDhhmmssms::toString(localTime);

            // generate batch ID and file name
            std::string batchId = inputStr + "-" + iterTimestampObject + "-" + std::to_string(i);
            std::string fileName = outputDirStr + "/" + outputStr + "-" + iterTimestampObject + "-" + std::to_string(i) + "." + outputExtStr;

            // add batch ID to the vector
            batchIds.push_back(batchId);

            // write the row to the CSV file
            std::string timestampCreated = dateAndTimesFunctions::UTC::YYYYMMDDhhmmss::toStringHuman(localTime);

            csvFile << i << ",";
            csvFile << batchId << ",";
            csvFile << inputStr << ",";
            csvFile << fileName << ",";
            csvFile << timestampCreated << ",";
            csvFile << "false" << ",";
            csvFile << "" << ",";
            csvFile << "" << ",";
            csvFile << 0 << "\n"; // end of csv row data
        }

        // finally
        csvFile.close();

        std::printf("- using --batch-out-csv save to \"%s\"\n", fileOutput.c_str());
    }

    // process --batch-out-json
    if (batchOutJson == "true" && argBatchInUse)
    {
        if (outputStr.empty())
        {
            outputStr = inputStr;
        }

        std::string fileOutput = outputStr + "-batch.json"; // output JSON file
        bool extendFile = false;

        // check if the file exists
        if (std::filesystem::exists(fileOutput))
        {
            std::cout << "file \"" << fileOutput << "\" already exists.\n";

            // prompt the user to extend the file
            char choice;
            do
            {
                std::cout << "do you want to extend it? (y/n): ";
                std::cin >> choice;
                choice = static_cast<char>(std::tolower(choice)); // ensure lowercase for comparison

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
            } while (choice != 'y' && choice != 'n');

            if (choice == 'y')
            {
                extendFile = true;
            }
            else
            {
                log::errorBase();
                std::printf("- \"%s\" already exists\n", fileOutput.c_str());
                return RETURN_MAIN_RESULT_ERROR_BATCH_OUT_ALREADY_EXISTS_JSON;
            }
        }

        // open the JSON file
        std::ofstream jsonFile;
        Json::Value jsonArray(Json::arrayValue); // root JSON array

        if (extendFile)
        {
            // read existing JSON content
            std::ifstream existingFile(fileOutput);
            if (!existingFile.is_open())
            {
                log::errorBase();
                std::printf("- unable to read existing .json file \"%s\"\n", fileOutput.c_str());
                return RETURN_MAIN_RESULT_ERROR_BATCH_OUT_FAIL_JSON;
            }

            Json::CharReaderBuilder readerBuilder;
            std::string errs;
            if (!parseFromStream(readerBuilder, existingFile, &jsonArray, &errs))
            {
                log::errorBase();
                std::printf("- failed to parse existing .json file \"%s\": %s\n", fileOutput.c_str(), errs.c_str());
                existingFile.close();
                return RETURN_MAIN_RESULT_ERROR_BATCH_OUT_FAIL_JSON;
            }
            existingFile.close();

            jsonFile.open(fileOutput, std::ios::out | std::ios::trunc); // overwrite mode
        }
        else
        {
            jsonFile.open(fileOutput, std::ios::out); // new file mode
        }

        if (!jsonFile.is_open())
        {
            log::errorBase();
            std::printf("- unable to write to .json for \"%s\"\n", fileOutput.c_str());
            jsonFile.close();
            return RETURN_MAIN_RESULT_ERROR_BATCH_OUT_FAIL_JSON;
        }

        // calculate the starting ID for new rows
        TI32 startId = extendFile ? jsonArray.size() + 1 : 1;

        // generate batch IDs and file names
        for (TI32 i = startId; i <= startId + batchIter - 1; i++)
        {
            auto localTime = dateAndTimesFunctions::localTimeZone();
            auto iterTimestampObject = dateAndTimesFunctions::UTC::YYYYMMDDhhmmssms::toString(localTime);

            // generate batch ID and file name
            std::string batchId = inputStr + "-" + iterTimestampObject + "-" + std::to_string(i);
            std::string fileName = outputDirStr + "/" + outputStr + "-" + iterTimestampObject + "-" + std::to_string(i) + "." + outputExtStr;

            // add batch ID to the vector
            batchIds.push_back(batchId);

            // create JSON object for this record
            Json::Value jsonObject;
            jsonObject[TBatchOutRecordDefault_HINT::id] = i;
            jsonObject[TBatchOutRecordDefault_HINT::batch_id] = batchId;
            jsonObject[TBatchOutRecordDefault_HINT::batch_origin] = inputStr;
            jsonObject[TBatchOutRecordDefault_HINT::batch_result] = fileName;
            jsonObject[TBatchOutRecordDefault_HINT::timestamp_created] = dateAndTimesFunctions::UTC::YYYYMMDDhhmmss::toStringHuman(localTime);
            jsonObject[TBatchOutRecordDefault_HINT::owned] = false;
            jsonObject[TBatchOutRecordDefault_HINT::owner] = "";
            jsonObject[TBatchOutRecordDefault_HINT::claimed_date_and_time] = "";
            jsonObject[TBatchOutRecordDefault_HINT::claimed_date_and_time_num] = 0;

            // append the JSON object to the array
            jsonArray.append(jsonObject);
        }

        // write the JSON array to the file
        Json::StreamWriterBuilder writerBuilder;
        std::unique_ptr<Json::StreamWriter> writer(writerBuilder.newStreamWriter());
        writer->write(jsonArray, &jsonFile);

        // finally
        jsonFile.close();

        std::printf("- using --batch-out-json save to \"%s\"\n", fileOutput.c_str());
    }

    //////////////////////////////////////////////////////

    return RETURN_MAIN_RESULT_OK;
}

} // namespace prgent

#endif // PRGENT_MAIN_HH
