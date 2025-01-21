/**
 * @file main_proc.hh
 * @author P.R. (pr@prothegee.com)
 * @note do not include to any header
 */
#ifndef PRGENT_MAIN_PROC_FUNCS_HH
#define PRGENT_MAIN_PROC_FUNCS_HH
#include <iostream>
#include <filesystem>

#include <libprcpp/modules/utility_module.hh>

#include <prgent/constants/args_const.hh>
#include <prgent/constants/file_extension_const.hh>
#include <prgent/constants/generate_const.hh>
#include <prgent/functions/barcode_funcs.hh>
#include <prgent/functions/prgent_log_funcs.hh>
#include <prgent/enums/generate_enums.hh>
#include <prgent/enums/return_enums.hh>

using namespace libprcpp;

namespace prgent
{

/**
 * @brief prgent main process function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int mainProcess(int argc, char *argv[]);

} // namespace prgent

#endif // PRGENT_MAIN_PROC_FUNCS_HH
