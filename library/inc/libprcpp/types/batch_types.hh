#ifndef PRGENT_BATCH_TYPES_HH
#define PRGENT_BATCH_TYPES_HH
#include <libprcpp/types/base_types.hh>

namespace prgent
{

using namespace libprcpp;

/**
 * @brief type structure for prgent batch out record
 * 
 * @note currently for .csv & .json output record internally
 */
struct TBatchOutRecordDefault
{
    std::string id;
    std::string batch_id;
    std::string batch_origin;
    std::string batch_result;
    std::string timestamp_created;
    bool        owned;
    std::string owner;
    std::string claimed_date_and_time;
    ui64        claimed_date_and_time_num;
};
// record hint for TBatchOutRecordDefault
struct TBatchOutRecordDefault_HINT
{
    inline static cchar *id = "id";
    inline static cchar *batch_id = "batch_id";
    inline static cchar *batch_origin = "batch_origin";
    inline static cchar *batch_result = "batch_result";
    inline static cchar *timestamp_created = "timestamp_created";
    inline static cchar *owned = "owned";
    inline static cchar *owner = "owner";
    inline static cchar *claimed_date_and_time = "claimed_date_and_time";
    inline static cchar *claimed_date_and_time_num = "claimed_date_and_time_num";
};

} // namespace prgent

#endif // PRGENT_BATCH_TYPES_HH
