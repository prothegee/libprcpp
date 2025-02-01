#include <libprcpp/functions/images_funcs.hh>
#include <libprcpp/functions/utility_funcs.hh>

using namespace libprcpp;

int main()
{
    std::string barcodeOut1 = "n/a";

    imagesFunctions::barcode::encode("my barcode 1 in", "my barcode 1 out.svg", 256, 256, 0);
    imagesFunctions::barcode::decode("my barcode 1 out.svg", barcodeOut1);

    std::printf("barcodeOut1: %s\n", barcodeOut1.c_str());


    std::string qrcodeOut1 = "n/a";

    imagesFunctions::qrcode::encode("my qrcode 1 in", "my qrcode 1 out.svg", 256, 256, 0);
    imagesFunctions::qrcode::decode("my qrcode 1 out.svg", qrcodeOut1);

    std::printf("qrcodeOut1: %s\n", qrcodeOut1.c_str());


    std::printf("attempt 100 batch svg\n");

    std::vector<std::string> batchOutRes = {};
    int errorBatchBarcode = 0, errorBatchQrcode = 0;

    for (int i = 0; i < 100; i++)
    {
        std::string barcodeBatchIn    = "batch barcode " + std::to_string(i+1);
        std::string barcodeBatchOut   = barcodeBatchIn + ".svg";
        std::string barcodeBatchCheck = barcodeBatchIn;

        std::string qrcodeBatchIn    = "batch qrcode " + std::to_string(i+1);
        std::string qrcodeBatchOut   = qrcodeBatchIn + ".svg";
        std::string qrcodeBatchCheck = qrcodeBatchIn;

        imagesFunctions::barcode::encode(barcodeBatchIn, barcodeBatchOut, 256, 256, 0);
        imagesFunctions::barcode::decode(barcodeBatchOut, barcodeBatchCheck);

        imagesFunctions::barcode::encode(qrcodeBatchIn, qrcodeBatchOut, 256, 256, 0);
        imagesFunctions::barcode::decode(qrcodeBatchOut, qrcodeBatchCheck);

        if (barcodeBatchIn != barcodeBatchCheck)
        {
            errorBatchBarcode++;
        }
        else
        {
            batchOutRes.emplace_back(barcodeBatchOut);
        }

        if (qrcodeBatchIn != qrcodeBatchCheck)
        {
            errorBatchQrcode++;
        }
        else
        {
            batchOutRes.emplace_back(qrcodeBatchOut);
        }

        std::cout << "\r    \r";
        std::cout << "current iter #" << i+1 << std::flush;
    }

    if (errorBatchBarcode != 0)
    {
        std::printf("found %d error for barcode batch\n", errorBatchBarcode);
    }

    if (errorBatchQrcode != 0)
    {
        std::printf("found %d error for qrcode batch\n", errorBatchQrcode);
    }

    // cleanup batchs
    for (auto delFile : batchOutRes)
    {
        std::filesystem::remove(delFile);
    }

    // cleanup thresholds_new.pnm
    if (std::filesystem::exists("thresholds_new.pnm"))
    {
        std::filesystem::remove("thresholds_new.pnm");
    }

    std::cout << "\nfinished\n";

    return 0;
}
