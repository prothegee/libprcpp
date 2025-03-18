#include <libprcpp/functions/images_funcs.hh>
#include <libprcpp/functions/utility_funcs.hh>

#if LIBPRCPP_USING_ZXING_CPP

#if LIBPRCPP_USING_STB
#if LIBPRCPP_COMPILER_GNU
    #ifndef STB_IMAGE_WRITE_IMPLEMENTATION
    #pragma message "IMPORTANT gnu compiler: STB_IMAGE_WRITE_IMPLEMENTATION should be only here"
    #define STB_IMAGE_WRITE_IMPLEMENTATION
    #endif // STB_IMAGE_WRITE_IMPLEMENTATION
    #ifndef STB_IMAGE_IMPLEMENTATION
    #pragma message "IMPORTANT gnu compiler: STB_IMAGE_IMPLEMENTATION should be only here"
    #define STB_IMAGE_IMPLEMENTATION
    #endif // STB_IMAGE_IMPLEMENTATION
#endif // LIBPRCPP_COMPILER_GNU
#if LIBPRCPP_COMPILER_MSVC
    #pragma message("IMPORTANT msvc compiler: STB_IMAGE_WRITE_IMPLEMENTATION should be only here")
    #ifndef STB_IMAGE_WRITE_IMPLEMENTATION
    #define STB_IMAGE_WRITE_IMPLEMENTATION // should be only here
    #endif // STB_IMAGE_WRITE_IMPLEMENTATION
    #pragma message("IMPORTANT msvc compiler: STB_IMAGE_IMPLEMENTATION should be only here")
    #ifndef STB_IMAGE_IMPLEMENTATION
    #define STB_IMAGE_IMPLEMENTATION // should be only here
    #endif // STB_IMAGE_IMPLEMENTATION
#endif // LIBPRCPP_COMPILER_MSVC
#if LIBPRCPP_COMPILER_CLANG
    #ifndef STB_IMAGE_WRITE_IMPLEMENTATION
    #pragma message "IMPORTANT clang compiler: STB_IMAGE_WRITE_IMPLEMENTATION should be only here"
    #define STB_IMAGE_WRITE_IMPLEMENTATION
    #endif // STB_IMAGE_WRITE_IMPLEMENTATION
    #ifndef STB_IMAGE_IMPLEMENTATION
    #pragma message "IMPORTANT clang compiler: STB_IMAGE_IMPLEMENTATION should be only here"
    #define STB_IMAGE_IMPLEMENTATION
    #endif // STB_IMAGE_IMPLEMENTATION
#endif // LIBPRCPP_COMPILER_CLANG

#include <stb/stb_image.h>
#include <stb/stb_image_write.h>
#endif // LIBPRCPP_USING_STB

#include <thread>
#include <memory>
#include <future>
#include <chrono>

using namespace std::chrono_literals;

namespace libprcpp
{
namespace imagesFunctions
{


namespace generate
{
    bool toSVG(const std::string &output, const BitMatrix &matrix, const int32_t &width, const int32_t &height, const int32_t &margin)
    {
        int32_t svgWidth = width + 2 * margin;
        int32_t svgHeight = height + 2 * margin;
        
        std::stringstream ss;
        ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        ss << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"" << svgWidth << "\" height=\"" << svgHeight << "\">\n";

        ss << "<rect id=\"background\" width=\"" << svgWidth << "\" height=\"" << svgHeight << "\" fill=\"white\" />\n";
        
        for (int32_t y = 0; y < height; ++y)
        {
            for (int32_t x = 0; x < width; ++x)
            {
                if (matrix.get(x, y))
                {
                    ss << "<rect x=\"" << (x + margin) << "\" y=\"" << (y + margin) << "\" width=\"1\" height=\"1\" fill=\"black\" />\n";
                }
            }
        }

        ss << "</svg>\n";

        std::ofstream file(output);
        if (!file.is_open())
        {
            std::cerr << "failed to open when writing svg\n";
            return false;
        }
        else
        {
            file << ss.str();
            file.close();
            return true;
        }
    }

    bool toPNG(const std::string &output, const TBuffer &buffer, const int32_t &x, const int32_t &y, const int32_t &comp)
    {
        return stbi_write_png(output.c_str(), x, y, comp, buffer.data(), (x * 4));
    }

    bool toJPG(const std::string &output, const TBuffer &buffer, const int32_t &x, const int32_t &y, const int32_t &comp)
    {
        return stbi_write_jpg(output.c_str(), x, y, comp, buffer.data(), (x * 4));
    }
} // namespace generate


namespace rasterize
{
    bool fromSVG(const std::string &svgPath, std::vector<uint8_t> &output, int32_t &width, int32_t &height)
    {
        auto fuImage = std::async(std::launch::async, nsvgParseFromFile, svgPath.c_str(), "px", 96.0f);

        fuImage.wait(); // well...

        NSVGimage *pImage = fuImage.get();

        if (!pImage)
        {
            std::printf("rasterize::fromSVG failed to load .svg file: %s\n", svgPath.c_str());
            return false;
        }

        // default output dimensions
        if (width < 256 || height < 256)
        {
            width = 256;
            height = static_cast<int32_t>(256 * pImage->height / pImage->width);
        }

        // rasterizer context
        NSVGrasterizer *pRast = nsvgCreateRasterizer();
        if (!pRast)
        {
            std::printf("rasterize::fromSVG  failed to create rasterizer\n");
            nsvgDelete(pImage);
            return false;
        }

        // allocate memory for the output image (RGBA format)
        std::vector<uint8_t> rgbaImage(width * height * 4);
        nsvgRasterize(pRast, pImage, 0, 0, width / pImage->width, rgbaImage.data(), width, height, width * 4);

        // convert the RGBA pixels to grayscale
        output.resize(width * height);
        for (int32_t y = 0; y < height; y++)
        {
            for (int32_t x = 0; x < width; x++)
            {
                int index = (y * width + x) * 4;  // 4 bytes per pixel (RGBA)
                uint8_t r = rgbaImage[index];     // R
                uint8_t g = rgbaImage[index + 1]; // G
                uint8_t b = rgbaImage[index + 2]; // B

                // convert RGB to grayscale using the luminance formula
                output[y * width + x] = static_cast<uint8_t>(
                    0.2126 * r + 0.7152 * g + 0.0722 * b
                );
            }
        }

        // clean up
        nsvgDeleteRasterizer(pRast);
        nsvgDelete(pImage);

        return true;
    }
} // namespace rasterize


namespace barcode
{
    bool encode(const std::string &content, const std::string &output, const int32_t &width, const int32_t &height, const int32_t &margin, const BarcodeFormat &codeFormat)
    {
        try
        {
            int32_t _width = width, _height = height, _margin = margin;

            if (_width <= 256) { _width = 256; }
            if (_height <= 256) { _height = 256; }
            if (_margin <= 0) { _margin = 0; }

            BitMatrix matrix;
            MultiFormatWriter writer(codeFormat);

            writer.setMargin(_margin);

            matrix = writer.encode(content, _width, _height);

            // vector to hold pixel data for the image (RGBA format) 4 channels
            TBuffer imageData(_width * _height * 4);

            // fill image data based on the BitMatrix (1 is black, 0 is white)
            for (int y = 0; y < _height; ++y)
            {
                for (int x = 0; x < _width; ++x)
                {
                    int pixelIndex = (y * _width + x) * 4; // RGBA
                    
                    if (matrix.get(x, y))
                    {
                        // black pixel (RGBA = 0, 0, 0, 255)
                        imageData[pixelIndex]     = 0;   // Red
                        imageData[pixelIndex + 1] = 0;   // Green
                        imageData[pixelIndex + 2] = 0;   // Blue
                        imageData[pixelIndex + 3] = 255; // Alpha (fully opaque)
                    }
                    else
                    {
                        // white pixel (RGBA = 255, 255, 255, 255)
                        imageData[pixelIndex]     = 255; // Red
                        imageData[pixelIndex + 1] = 255; // Green
                        imageData[pixelIndex + 2] = 255; // Blue
                        imageData[pixelIndex + 3] = 255; // Alpha (fully opaque)
                    }
                }
            }

            if (utilityFunctions::find::inputEndsWith(output, std::string(FILE_EXTENSION_IS_PNG_HINT))) // is .png
            {
                return generate::toPNG(output, imageData, _width, _height);
                // return generate::toPNG(output.c_str(), _width, _height, 4, imageData.data(), _width * 4);
            }
            else if (utilityFunctions::find::inputEndsWith(output, std::string(FILE_EXTENSION_IS_JPG_HINT))) // is .jpg
            {
                return generate::toJPG(output, imageData, _width, _height);
                // return generate::toJPG(output.c_str(), _width, _height, 4, imageData.data(), _width * 4);
            }
            else if (utilityFunctions::find::inputEndsWith(output, std::string(FILE_EXTENSION_IS_JPEG_HINT))) // is .jpeg
            {
                return generate::toJPG(output, imageData, _width, _height);
                // return generate::toJPG(output.c_str(), _width, _height, 4, imageData.data(), _width * 4);
            }
            else if (utilityFunctions::find::inputEndsWith(output, std::string(FILE_EXTENSION_IS_SVG_HINT))) // is .svg
            {
                return generate::toSVG(output.c_str(), matrix, _width, _height, _margin);
            }
            else
            {
                return generate::toPNG(output, imageData, _width, _height);
                // return generate::toPNG(output.c_str(), _width, _height, 4, imageData.data(), _width * 4); // default return .png
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "exception barcode::encode:\n" << e.what() << '\n';

            return false;
        }
    }

    bool decode(const std::string &content, std::string &output, const BarcodeFormat &codeFormat, const bool &tryHard)
    {
        bool isOk = false;
        TI32 width, height, channels;

        std::vector<uint8_t> luminanceData;

        if (content.size() >= 4 && content.substr(content.size() - 4) == ".svg")
        {
            if (!rasterize::fromSVG(content, luminanceData, width, height))
            {
                std::printf("barcode::decode failed to render svg: %s\n", content.c_str());
                return false;
            }
            isOk = true;
        }
        else
        {
            auto imageData = stbi_load(content.c_str(), &width, &height, &channels, 0);

            if (!imageData)
            {
                std::printf("barcode::decode image data can't be loaded from %s\n", content.c_str());
                return false;
            }

            if (channels == 3 || channels == 4) // RGB or TGBA
            {
                luminanceData.resize(width * height);

                for (int y = 0; y < height; y++)
                {
                    for (int x = 0; x < width; x++)
                    {
                        int sourceIndex = (y * width + x) * channels;
                        int destinationIndex = y * width + x;

                        luminanceData[destinationIndex] = static_cast<uint8_t>(
                            0.2126 * imageData[sourceIndex] +      // R
                            0.7152 * imageData[sourceIndex + 1] +  // G
                            0.0722 * imageData[sourceIndex + 2]    // B
                        );
                    }
                }
            }
            else if (channels == 1) // grayscale
            {
                luminanceData.assign(imageData, imageData + width * height);
            }
            else
            {
                std::printf("barcode::decode error image channel count (%d) is not supported\n", channels);
                stbi_image_free(imageData);
                return false;
            }

            stbi_image_free(imageData);

            isOk = true;
        }

        if (!isOk) { return false; }

        ZXing::ImageView imageView(luminanceData.data(), width, height, ImageFormat::Lum);

        ReaderOptions option;
        
        option.setTryHarder(tryHard);
        option.setFormats(codeFormat); // why?
        // option.setFormats(ZXing::BarcodeFormat::Any);

        auto result = ZXing::ReadBarcode(imageView, option);

        if (!result.isValid())
        {
            std::printf("barcode::decode result invalid, format is %s\n", ZXing::ToString(result.format()).c_str());
            return false;
        }

        output = result.text();

        return true;
    }
} // namespace barcode


namespace qrcode
{
    bool encode(const std::string &content, const std::string &output, const int32_t &width, const int32_t &height, const int32_t &margin, const BarcodeFormat &codeFormat)
    {
        try
        {
            int32_t _width = width, _height = height, _margin = margin;

            if (_width <= 256) { _width = 256; }
            if (_height <= 256) { _height = 256; }
            if (_margin <= 0) { _margin = 0; }

            BitMatrix matrix;
            MultiFormatWriter writer(codeFormat);

            writer.setMargin(_margin);

            matrix = writer.encode(content, _width, _height);

            // vector to hold pixel data for the image (RGBA format) 4 channels
            TBuffer imageData(_width * _height * 4);

            // fill image data based on the BitMatrix (1 is black, 0 is white)
            for (int y = 0; y < _height; ++y)
            {
                for (int x = 0; x < _width; ++x)
                {
                    int pixelIndex = (y * _width + x) * 4; // RGBA
                    
                    if (matrix.get(x, y))
                    {
                        // black pixel (RGBA = 0, 0, 0, 255)
                        imageData[pixelIndex]     = 0;   // Red
                        imageData[pixelIndex + 1] = 0;   // Green
                        imageData[pixelIndex + 2] = 0;   // Blue
                        imageData[pixelIndex + 3] = 255; // Alpha (fully opaque)
                    }
                    else
                    {
                        // white pixel (RGBA = 255, 255, 255, 255)
                        imageData[pixelIndex]     = 255; // Red
                        imageData[pixelIndex + 1] = 255; // Green
                        imageData[pixelIndex + 2] = 255; // Blue
                        imageData[pixelIndex + 3] = 255; // Alpha (fully opaque)
                    }
                }
            }

            if (utilityFunctions::find::inputEndsWith(output, std::string(FILE_EXTENSION_IS_PNG_HINT))) // is .png
            {
                return generate::toPNG(output, imageData, _width, _height);
                // return generate::toPNG(output.c_str(), _width, _height, 4, imageData.data(), _width * 4);
            }
            else if (utilityFunctions::find::inputEndsWith(output, std::string(FILE_EXTENSION_IS_JPG_HINT))) // is .jpg
            {
                return generate::toJPG(output, imageData, _width, _height);
                // return generate::toJPG(output.c_str(), _width, _height, 4, imageData.data(), _width * 4);
            }
            else if (utilityFunctions::find::inputEndsWith(output, std::string(FILE_EXTENSION_IS_JPEG_HINT))) // is .jpeg
            {
                return generate::toJPG(output, imageData, _width, _height);
                // return generate::toJPG(output.c_str(), _width, _height, 4, imageData.data(), _width * 4);
            }
            else if (utilityFunctions::find::inputEndsWith(output, std::string(FILE_EXTENSION_IS_SVG_HINT))) // is .svg
            {
                return generate::toSVG(output.c_str(), matrix, _width, _height, _margin);
            }
            else
            {
                return generate::toPNG(output, imageData, _width, _height);
                // return generate::toPNG(output.c_str(), _width, _height, 4, imageData.data(), _width * 4); // default return .png
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "exception qrcode::encode:\n" << e.what() << '\n';

            return false;
        }
    }

    bool decode(const std::string &content, std::string &output, const BarcodeFormat &codeFormat, const bool &tryHard)
    {
        bool isOk = false;
        TI32 width, height, channels;

        std::vector<uint8_t> luminanceData;

        if (content.size() >= 4 && content.substr(content.size() - 4) == ".svg")
        {
            if (!rasterize::fromSVG(content, luminanceData, width, height))
            {
                std::printf("qrcode::decode failed to render svg: %s\n", content.c_str());
                return false;
            }
            isOk = true;
        }
        else
        {
            auto imageData = stbi_load(content.c_str(), &width, &height, &channels, 0);

            if (!imageData)
            {
                std::printf("qrcode::decode image data can't be loaded from %s\n", content.c_str());
                return false;
            }

            if (channels == 3 || channels == 4) // RGB or TGBA
            {
                luminanceData.resize(width * height);

                for (int y = 0; y < height; y++)
                {
                    for (int x = 0; x < width; x++)
                    {
                        int sourceIndex = (y * width + x) * channels;
                        int destinationIndex = y * width + x;

                        luminanceData[destinationIndex] = static_cast<uint8_t>(
                            0.2126 * imageData[sourceIndex] +      // R
                            0.7152 * imageData[sourceIndex + 1] +  // G
                            0.0722 * imageData[sourceIndex + 2]    // B
                        );
                    }
                }
            }
            else if (channels == 1) // grayscale
            {
                luminanceData.assign(imageData, imageData + width * height);
            }
            else
            {
                std::printf("qrcode::decode error, image channel count (%d) is not supported\n", channels);
                stbi_image_free(imageData);
                return false;
            }

            stbi_image_free(imageData);

            isOk = true;
        }

        if (!isOk) { return false; }

        ZXing::ImageView imageView(luminanceData.data(), width, height, ImageFormat::Lum);

        ReaderOptions option;
        
        option.setTryHarder(tryHard);
        option.setFormats(codeFormat); // why?
        // option.setFormats(ZXing::BarcodeFormat::Any);

        auto result = ZXing::ReadBarcode(imageView, option);

        if (!result.isValid())
        {
            std::printf("qrcode::decode result invalid, format is %s\n", ZXing::ToString(result.format()).c_str());
            return false;
        }

        output = result.text();

        return true;
    }
} // namespace qrcode


} // namespace imagesFunctions
} // namespace libprcpp
#endif // LIBPRCPP_USING_ZXING_CPP
