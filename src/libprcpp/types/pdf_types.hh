#ifndef LIBPRCPP_PDF_TYPES_HH
#define LIBPRCPP_PDF_TYPES_HH
#include <libprcpp/base/config.hh>

#if LIBPRCPP_PROJECT_USING_LIBHARU
#include "hpdf.h"

namespace libprcpp
{

/**
 * @brief type pdf config structure
 * 
 */
struct TPdfConfig
{
    std::string font = "Arial";
    float table_top_y = 750.0f;
    float table_left_x = 50.0f;
    float cell_width = 100.0f;
    float cell_height = 20.0f;
    HPDF_PageSizes page_size = HPDF_PageSizes::HPDF_PAGE_SIZE_A4;
    HPDF_PageDirection page_direction = HPDF_PageDirection::HPDF_PAGE_PORTRAIT;
    int font_size = 12;
};

} // namespace libprcpp

#endif // LIBPRCPP_PROJECT_USING_LIBHARU

#endif // LIBPRCPP_PDF_TYPES_HH
