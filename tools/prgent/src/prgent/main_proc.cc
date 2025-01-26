#include "main_proc.hh"

#include <thread>
#include <future>
#include <fstream>

#include <libprcpp/constants/string_const.hh>
#include <libprcpp/modules/date_and_time_module.hh>

#include <prgent/types/batch_types.hh>

namespace prgent
{

int mainProcess(int argc, char *argv[])
{
    bool argHelpInUse = false;
    bool argBatchInUse = false;
    bool supportsImageSizeAndMargin = false;

    // default value for size in pixel/px
    i32 sizeWidth = 256, sizeHeight = 256, sizeMargin = 0;

    i32 batchIter = 0;

    EGenerateMode generateMode = GENERATE_MODE_UNDEFINED;

    std::string helpStr;

    std::string generateModeStr;

    std::string inputStr;

    std::string outputStr, outputDirStr, outputExtStr, outputDecodedStr;

    std::string imageSizeStr, imageSizeWidthStr, imageSizeHeightStr, imageSizeMarginStr;

    std::string batchIterStr, batchOutCsv, batchOutJson;

    for (i32 i = 1; i < argc; i++)
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

                if (isNumeric(imageSizeMarginStr))
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

            if (isNumeric(batchIterStr))
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
        else if (arg == ARG_IS_BATCH_OUT_CSV) // this arg is "--batch-out-csv", only accept "true" & "false", default is "false"
        {
            if (i + 1 < argc)
            {
                batchOutCsv = argv[i + 1];
                i++;
            }
        }
        else if (arg == ARG_IS_BATCH_OUT_JSON) // this arg is "--batch-out-json", only accept "true" & "false", default is "false"
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

    bool batchModeFail = false; // double check

    std::vector<std::string> batchIds;

    // future object storage for batch id & save csv/json
    std::vector<std::future<std::string>> futureBatchCsv, futureBatchJson;

    // only used for encode
    auto generateBatchEncode = [&](i32 batchNum, std::string timestampObject) -> std::string
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

                barcode::encodeImage(std::string(outputStr + "-" + timestampObject + std::to_string(batchNum)), result, sizeWidth, sizeHeight, sizeMargin);
            }
            break;

            case GENERATE_MODE_QRCODE_ENCODE:
            {
                result = outputDirStr + "/" + outputStr + "-" + timestampObject + "-" + std::to_string(batchNum) + "." + outputExtStr;

                qrcode::encodeImage(std::string(outputStr + "-" + timestampObject + std::to_string(batchNum)), result, sizeWidth, sizeHeight, sizeMargin);
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

                if (barcode::encodeImage(inputStr, outputStr, sizeWidth, sizeHeight, sizeMargin)) // generate barcode
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

                // check batchOutCsv file
                if (batchOutCsv == "true" && std::filesystem::exists(batchCsv))
                {
                    log::errorBase();
                    std::printf("- \"%s\" already exists", batchCsv.c_str());
                    return RETURN_MAIN_RESULT_ERROR_BATCH_OUT_ALREADY_EXISTS_CSV;
                }

                // check batchOutJson file
                if (batchOutJson == "true" && std::filesystem::exists(batchJson))
                {
                    log::errorBase();
                    std::printf("- \"%s\" already exists", batchJson.c_str());
                    return RETURN_MAIN_RESULT_ERROR_BATCH_OUT_ALREADY_EXISTS_JSON;
                }

                for (i32 i = 1; i <= batchIter; i++)
                {
                    auto localTime = dateAndTimeFunctions::localTimeZone();
                    auto iterTimestampObject = dateAndTimeFunctions::UTC::YYYYMMDDhhmmssms::toString(localTime);

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

                if (qrcode::encodeImage(inputStr, outputStr, sizeWidth, sizeHeight, sizeMargin)) // generate qrcode
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

                // check batchOutCsv file
                if (batchOutCsv == "true" && std::filesystem::exists(batchCsv))
                {
                    log::errorBase();
                    std::printf("- \"%s\" already exists", batchCsv.c_str());
                    return RETURN_MAIN_RESULT_ERROR_BATCH_OUT_ALREADY_EXISTS_CSV;
                }

                // check batchOutJson file
                if (batchOutJson == "true" && std::filesystem::exists(batchJson))
                {
                    log::errorBase();
                    std::printf("- \"%s\" already exists", batchJson.c_str());
                    return RETURN_MAIN_RESULT_ERROR_BATCH_OUT_ALREADY_EXISTS_JSON;
                }

                for (i32 i = 1; i <= batchIter; i++)
                {
                    auto localTime = dateAndTimeFunctions::localTimeZone();
                    auto iterTimestampObject = dateAndTimeFunctions::UTC::YYYYMMDDhhmmssms::toString(localTime);

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

            if (!barcode::decodeImage(inputStr, outputDecodedStr))
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

            if (!qrcode::decodeImage(inputStr, outputDecodedStr))
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

        // output csv
        std::string fileOutput = outputStr + "-batch.csv";

        std::ofstream csvFile(fileOutput);

        if (!csvFile.is_open())
        {
            log::errorBase();
            std::printf("- unable to write to .csv for \"%s\"\n", fileOutput.c_str());
            csvFile.close();
            return RETURN_MAIN_RESULT_ERROR_BATCH_OUT_FAIL_CSV;
        }

        // csv header
        std::string csvHeader;
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

        // create rows
        for (i32 i = 1; i <= batchIter; i++)
        {
            std::string batchId = batchIds[i - 1];
            std::string fileName = futureBatchCsv[i - 1].get();

            std::string timestampCreated = dateAndTimeFunctions::UTC::YYYYMMDDhhmmss::toStringHuman(dateAndTimeFunctions::localTimeZone());

            if (!fileName.empty())
            {
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

        // output json
        std::string fileOutput = outputStr + "-batch.json";

        std::ofstream jsonFile(fileOutput);

        Json::Value jsonArray(Json::arrayValue);

        if (!jsonFile.is_open())
        {
            log::errorBase();
            std::printf("- unable to write to .json for \"%s\"\n", fileOutput.c_str());
            jsonFile.close();
            return RETURN_MAIN_RESULT_ERROR_BATCH_OUT_FAIL_CSV;
        }

        // create data
        for (i32 i = 1; i <= batchIter; i++)
        {
            std::string batchId = batchIds[i - 1];
            std::string fileName = futureBatchJson[i - 1].get();

            std::string timestampCreated = dateAndTimeFunctions::UTC::YYYYMMDDhhmmss::toStringHuman(dateAndTimeFunctions::localTimeZone());

            if (!fileName.empty())
            {
                Json::Value jsonObject;

                jsonObject[TBatchOutRecordDefault_HINT::id] = i;
                jsonObject[TBatchOutRecordDefault_HINT::batch_id] = batchId;
                jsonObject[TBatchOutRecordDefault_HINT::batch_origin] = inputStr;
                jsonObject[TBatchOutRecordDefault_HINT::batch_result] = fileName;
                jsonObject[TBatchOutRecordDefault_HINT::timestamp_created] = timestampCreated;
                jsonObject[TBatchOutRecordDefault_HINT::owned] = false;
                jsonObject[TBatchOutRecordDefault_HINT::owner] = "";
                jsonObject[TBatchOutRecordDefault_HINT::claimed_date_and_time] = "";
                jsonObject[TBatchOutRecordDefault_HINT::claimed_date_and_time_num] = 0;

                jsonArray.append(jsonObject);
            }
        }

        // finally
        jsonFile << jsonArray.toStyledString();
        jsonFile.close();

        std::printf("- using --batch-out-json save to \"%s\"\n", fileOutput.c_str());
    }

    //////////////////////////////////////////////////////

    return RETURN_MAIN_RESULT_OK;
}

} // namespace prgent
