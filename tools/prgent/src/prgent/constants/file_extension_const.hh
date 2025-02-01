#ifndef PRGENT_FILE_EXTENSION_CONST_HH
#define PRGENT_FILE_EXTENSION_CONST_HH
#include <libprcpp/types/basic_types.hh>

#include <iostream>
#include <vector>
#include <filesystem>
#include <algorithm>

using namespace libprcpp;

namespace prgent
{

inline static cchar *FILE_EXTENSION_IS_JPEG_HINT = ".jpeg"; // .jpeg
inline static cchar *FILE_EXTENSION_IS_JPG_HINT  = ".jpg"; // .jpg
inline static cchar *FILE_EXTENSION_IS_PDF_HINT  = ".pdf"; // .pdf
inline static cchar *FILE_EXTENSION_IS_PNG_HINT  = ".png"; // .png
inline static cchar *FILE_EXTENSION_IS_SVG_HINT  = ".svg"; // .svg

/**
 * @brief supported: jpeg, jpg, png, svg
 * 
 */
inline static const std::vector<std::string> ALLOWED_MODE_IMAGE_EXTENSIONS = {
    "jpeg",
    "jpg",
    "png",
    "svg",
};

/**
 * @brief validate allowed image file extension from fileExtension param
 * 
 * @note will return .svg as default if not supported
 * 
 * @param fileExtension 
 * @param argKey 
 * @return std::string 
 */
inline static std::string validateAllowedImageFileExtension(const std::string &fileExtension, const char *argKey = "")
{
    bool found = false;
    std::string result;

    for (auto &extension : ALLOWED_MODE_IMAGE_EXTENSIONS)
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
            std::cout << argKey << " file extension not supported, use .svg instead\n";
        }
        result = FILE_EXTENSION_IS_SVG_HINT;
    }

    return result;
}

inline static std::string getFileExtension(const std::string &filePath)
{
    std::filesystem::path path(filePath);
    std::string extension = path.extension().string();

    // remove the leading dot (e.g., ".jpg" -> "jpg")
    if (!extension.empty() && extension[0] == '.')
    {
        extension.erase(0, 1);
    }

    return extension;
}

inline static bool isExtensionAllowed(const std::string &filePath, const std::vector<std::string> &allowedExtensions)
{
    std::string extension = getFileExtension(filePath);

    // force convert extension to lowercase for case-insensitive comparison
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    // check if the extension is in the allowed list
    return std::find(allowedExtensions.begin(), allowedExtensions.end(), extension) != allowedExtensions.end();
}

} // namespace prgent

#endif // PRGENT_FILE_EXTENSION_CONST_HH
