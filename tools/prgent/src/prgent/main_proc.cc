#include "main_proc.hh"

namespace prgent
{

int mainProcess(int argc, char *argv[])
{
    bool argHelpInUse = false;
    bool argSizeInUse = false;

    // default value for size in pixel/px
    i32 sizeWidth = 127, sizeHeight = 127, sizeMargin = 0;

    EGenerateMode generateMode = GENERATE_MODE_UNDEFINED;

    std::string helpStr;

    std::string generateModeStr;

    std::string inputStr;

    std::string outputStr, outputDirStr, outputExtStr;

    std::string imageSizeStr, imageSizeWidthStr, imageSizeHeightStr, imageSizeMarginStr;

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
        // this arg is "--image-size" format NNNxNNN & N is numeric value
        // this arg is "--image-width"
        // this arg is "--image-height"
        // this arg is "--image-margin"
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

            // replace all empty space with -
            utilityFunctions::find::andReplaceAll(inputStr, " ", "-");

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
                std::printf("--output-dir arg is not supplied, using default output ext as .png\n");
                outputStr += FILE_EXTENSION_IS_PNG_HINT; // use .png
            }
            else
            {
                outputStr += validateAllowedImageFileExtension(outputExtStr, ARG_IS_OUTPUT_EXT); // default will return .png
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

            // replace all empty space with -
            utilityFunctions::find::andReplaceAll(inputStr, " ", "-");

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
                std::printf("--output-dir arg is not supplied, using default output ext as .png\n");
                outputStr += FILE_EXTENSION_IS_PNG_HINT; // use .png
            }
            else
            {
                outputStr += validateAllowedImageFileExtension(outputExtStr, ARG_IS_OUTPUT_EXT); // default will return .png
            }

            if (qrcode::encodeImage(inputStr, outputStr, sizeWidth, sizeHeight, sizeMargin)) // generate qrcode
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
        break;

        case GENERATE_MODE_BARCODE_DECODE:
        {
            std::printf("TODO: case GENERATE_MODE_BARCODE_DECODE\n");
        }
        break;

        case GENERATE_MODE_QRCODE_DECODE:
        {
            std::printf("TODO: case GENERATE_MODE_QRCODE_DECODE\n");
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

    // process --batch-out-json

    //////////////////////////////////////////////////////

    return RETURN_MAIN_RESULT_OK;
}

} // namespace prgent
