#ifndef PRGENT_PRGENT_LOG_FUNCS_HH
#define PRGENT_PRGENT_LOG_FUNCS_HH
#include <string>

namespace prgent
{
namespace log
{

void okBase();

//////////////////////////////////////////////////////

void errorBase();

//////////////////////////////////////////////////////

void noticeBase();

//////////////////////////////////////////////////////

void warningBase();

//////////////////////////////////////////////////////

void showHelpBaseHint();

void showHelpConfigurations(const std::string &helpHint);

} // namespace log
} // namespace prgent

#endif // PRGENT_PRGENT_LOG_FUNCS_HH
