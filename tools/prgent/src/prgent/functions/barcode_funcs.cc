#include "barcode_funcs.hh"

#include <iostream>

#if LIBPRCPP_PROJECT_USING_ZXING

#if LIBPRCPP_PROJECT_USING_STB

using namespace libprcpp;
#include <string>
#include <sstream>
#include <fstream>

namespace internal
{

bool generateSVG(const char *output, const BitMatrix &matrix, const i32 &width, const i32 &height, const i32 &margin)
{
    i32 svgWidth = width + 2 * margin;
    i32 svgHeight = height + 2 * margin;
    
    std::stringstream ss;
    ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    ss << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"" << svgWidth << "\" height=\"" << svgHeight << "\">\n";
    
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
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

} // namespace internal

namespace prgent
{
namespace barcode
{
    bool encodeImage(const std::string &content, const std::string &output, const i32 &width, const i32 &height, const i32 &margin)
    {
        try
        {
            i32 _width = width, _height = height, _margin = margin;

            BitMatrix matrix;
            MultiFormatWriter writer(BarcodeFormat::Code128);
            WriterOptions writerOption;

            writer.setMargin(_margin);

            matrix = writer.encode(content, _width, _height);

            // vector to hold pixel data for the image (RGBA format) 4 channels
            std::vector<unsigned char> imageData(_width * _height * 4);

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

            if (inputEndsWith(output, std::string(FILE_EXTENSION_IS_PNG_HINT))) // is .png
            {
                return stbi_write_png(output.c_str(), _width, _height, 4, imageData.data(), _width * 4);
            }
            else if (inputEndsWith(output, std::string(FILE_EXTENSION_IS_JPG_HINT))) // is .jpg
            {
                return stbi_write_jpg(output.c_str(), _width, _height, 4, imageData.data(), _width * 4);
            }
            else if (inputEndsWith(output, std::string(FILE_EXTENSION_IS_JPEG_HINT))) // is .jpeg
            {
                return stbi_write_jpg(output.c_str(), _width, _height, 4, imageData.data(), _width * 4);
            }
            else if (inputEndsWith(output, std::string(FILE_EXTENSION_IS_SVG_HINT))) // is .svg
            {
                return internal::generateSVG(output.c_str(), matrix, _width, _height, _margin);
            }
            else
            {
                return stbi_write_png(output.c_str(), _width, _height, 4, imageData.data(), _width * 4); // default return .png
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "prgent::barcode::encode: ERROR:\n" << e.what() << '\n';

            return false;
        }
    }
} // namespace barcode
} // namespace prgent

#endif // LIBPRCPP_PROJECT_USING_STB

#endif // LIBPRCPP_PROJECT_USING_ZXING
