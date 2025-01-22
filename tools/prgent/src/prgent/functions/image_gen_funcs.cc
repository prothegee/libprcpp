#include "image_gen_funcs.hh"

#if LIBPRCPP_PROJECT_USING_ZXING

#if LIBPRCPP_PROJECT_USING_STB

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

} // namespace prgent

#endif // LIBPRCPP_PROJECT_USING_ZXING

#endif // LIBPRCPP_PROJECT_USING_STB
