#include "barcode_funcs.hh"

#include "image_gen_funcs.hh"

#if LIBPRCPP_PROJECT_USING_ZXING

#if LIBPRCPP_PROJECT_USING_STB
#if LIBPRCPP_PROJECT_USING_STB_HAS_PARENT_DIR
#include <stb/stb_image_write.h>
#else
#include <stb_image_write.h>
#endif // LIBPRCPP_PROJECT_USING_STB_HAS_PARENT_DIR

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
            return generateSVG(output.c_str(), matrix, _width, _height, _margin);
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
