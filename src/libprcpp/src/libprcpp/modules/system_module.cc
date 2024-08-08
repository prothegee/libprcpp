#include "system_module.h"

namespace libprcpp
{

CSystemModule::CSystemModule()
{
}

CSystemModule::~CSystemModule()
{
}

bool CSystemModule::SDirectory::createDirectory(const std::string &path)
{
    std::filesystem::path directory = path;

    return fs::create_directory(directory);
}

bool CSystemModule::SDirectory::deleteDirectory(const std::string &path)
{
    std::filesystem::path directory = path;

    return fs::remove(directory);
}

std::string CSystemModule::SDirectory::getCurrentDir()
{
    std::filesystem::path currentDir = std::filesystem::current_path();

    return currentDir.string();
}

} // namespace libprcpp
