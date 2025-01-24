#include "image_gen_funcs.hh"

#if LIBPRCPP_PROJECT_USING_ZXING

#if LIBPRCPP_PROJECT_USING_STB

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

#if LIBPRCPP_PROJECT_USING_STB_HAS_PARENT_DIR
#include <stb/stb_image.h>
#include <stb/stb_image_write.h>
#else
#include <stb_image.h>
#include <stb_image_write.h>
#endif // LIBPRCPP_PROJECT_USING_STB_HAS_PARENT_DIR

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

namespace prgent
{

bool generateSVG(const char *output, const BitMatrix &matrix, const i32 &width, const i32 &height, const i32 &margin)
{
    i32 svgWidth = width + 2 * margin;
    i32 svgHeight = height + 2 * margin;
    
    std::stringstream ss;
    ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    ss << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"" << svgWidth << "\" height=\"" << svgHeight << "\">\n";

    ss << "<rect id=\"background\" width=\"" << svgWidth << "\" height=\"" << svgHeight << "\" fill=\"white\" />\n";
    
    for (i32 y = 0; y < height; ++y)
    {
        for (i32 x = 0; x < width; ++x)
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

bool rasterizeFromSVG(const std::string &svgPath, std::vector<uint8_t> &output, i32 &width, i32 &height)
{
    auto document = lunasvg::Document::loadFromFile(svgPath);

    if (!document)
    {
        std::printf("Failed to load SVG file: %s\n", svgPath.c_str());
        return false;
    }

    auto svgWidth = document->width();
    auto svgHeight = document->height();

    // default output dimensions
    if (width < 256 || height < 256)
    {
        width = 256;
        height = static_cast<i32>(256 * svgHeight / svgWidth);
    }

    auto bitmap = document->renderToBitmap(width, height);
    if (!bitmap.valid())
    {
        std::printf("- failed to render svg to bitmap: %s\n", svgPath.c_str());
        return false;
    }

    // raw pixel data (RGBA format)
    const uint8_t *pixels = bitmap.data();
    output.resize(width * height);

    // convert the RGBA pixels to grayscale
    for (i32 y = 0; y < height; y++)
    {
        for (i32 x = 0; x < width; x++)
        {
            int index = (y * width + x) * 4; // 4 bytes per pixel (RGBA)
            uint8_t r = pixels[index];       // R
            uint8_t g = pixels[index + 1];   // G
            uint8_t b = pixels[index + 2];   // B

            // Convert RGB to grayscale using the luminance formula
            output[y * width + x] = static_cast<uint8_t>(
                0.2126 * r + 0.7152 * g + 0.0722 * b
            );
        }
    }

    return true;
}

} // namespace prgent

#endif // LIBPRCPP_PROJECT_USING_ZXING

#endif // LIBPRCPP_PROJECT_USING_STB
