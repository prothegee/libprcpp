#include "main_proc.hh"

#include <thread>
#include <future>

#include <libprcpp/modules/date_and_time_module.hh>

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
        // RESERVED --batch-out-csv
        // RESERVED --batch-out-json
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

    // future object storage for batch save csv/json
    std::vector<std::future<std::string>> futureBatchCsv, futureBatchJson;

    // only used for encode
    auto generateBatchEncode = [&](i32 batchNum) -> std::string
    {
        i32 localTime = 0;
        std::string result, timestampStr;

        localTime = dateAndTimeFunctions::localTimeZone();
        timestampStr = dateAndTimeFunctions::UTC::YYYYMMDDhhmmssms::toString(localTime);

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

        std::cout << "timestampStr: " << timestampStr << '\n';

        switch (generateMode)
        {
            case GENERATE_MODE_BARCODE_ENCODE:
            {
                result = outputDirStr + "/" + outputStr + "-" + timestampStr + "-" + std::to_string(batchNum) + "." + outputExtStr;

                barcode::encodeImage(std::string(outputStr + "-" + timestampStr + std::to_string(batchNum)), result, sizeWidth, sizeHeight, sizeMargin);
            }
            break;

            case GENERATE_MODE_QRCODE_ENCODE:
            {
                result = outputDirStr + "/" + outputStr + "-" + timestampStr + "-" + std::to_string(batchNum) + "." + outputExtStr;

                qrcode::encodeImage(std::string(outputStr + "-" + timestampStr + std::to_string(batchNum)), result, sizeWidth, sizeHeight, sizeMargin);
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
                for (i32 i = 1; i <= batchIter; i++)
                {
                    auto iterRes = std::async(std::launch::async, generateBatchEncode, i);

                    if (batchOutCsv == "true")
                    {
                        futureBatchCsv.push_back(std::move(iterRes));
                    }

                    if (batchOutJson == "true")
                    {
                        futureBatchJson.push_back(std::move(iterRes));
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
                for (i32 i = 1; i <= batchIter; i++)
                {
                    auto iterRes = std::async(std::launch::async, generateBatchEncode, i);

                    if (batchOutCsv == "true")
                    {
                        futureBatchCsv.push_back(std::move(iterRes));
                    }

                    if (batchOutJson == "true")
                    {
                        futureBatchJson.push_back(std::move(iterRes));
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
                std::printf("decode result:\n`````` START BARCODE DECODE ``````\n%s\n``````  END BARCODE DECODE  ``````\n", outputDecodedStr.c_str());
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
                std::printf("decode result:\n`````` START QRCODE DECODE ``````\n%s\n``````  END QRCODE DECODE  ``````\n", outputDecodedStr.c_str());
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

    // TODO: process --batch-out-csv

    // TODO: process --batch-out-json

    //////////////////////////////////////////////////////

    return RETURN_MAIN_RESULT_OK;
}

} // namespace prgent
