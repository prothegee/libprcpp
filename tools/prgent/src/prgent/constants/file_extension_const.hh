#ifndef PRGENT_FILE_EXTENSION_CONST_HH
#define PRGENT_FILE_EXTENSION_CONST_HH
#include <libprcpp/types/basic_types.hh>

#include <iostream>
#include <vector>

using namespace libprcpp;

namespace prgent
{

inline static cchar *FILE_EXTENSION_IS_JPEG_HINT = ".jpeg"; // .jpeg
inline static cchar *FILE_EXTENSION_IS_JPG_HINT  = ".jpg"; // .jpg
inline static cchar *FILE_EXTENSION_IS_PDF_HINT  = ".pdf"; // .pdf
inline static cchar *FILE_EXTENSION_IS_PNG_HINT  = ".png"; // .png
inline static cchar *FILE_EXTENSION_IS_SVG_HINT  = ".svg"; // .svg

/**
 * @brief validate allowed image file extension from fileExtension param
 * 
 * @param fileExtension 
 * @param argKey 
 * @return std::string 
 */
inline static std::string validateAllowedImageFileExtension(const std::string &fileExtension, const char *argKey = "")
{
    const std::vector<std::string> allowed = {
        "jpeg",
        "jpg",
        "png",
        "svg",
    };

    bool found = false;
    std::string result;

    for (auto &extension : allowed)
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
            std::cout << argKey << " file extension not supported, use .png instead\n";
        }
        result = FILE_EXTENSION_IS_PNG_HINT;
    }

    return result;
}

} // namespace prgent

#endif // PRGENT_FILE_EXTENSION_CONST_HH
