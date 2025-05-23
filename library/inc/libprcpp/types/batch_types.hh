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
    TU64        claimed_date_and_time_num;
};
// record hint for TBatchOutRecordDefault
struct TBatchOutRecordDefault_HINT
{
    inline static const TChr *id = "id";
    inline static const TChr *batch_id = "batch_id";
    inline static const TChr *batch_origin = "batch_origin";
    inline static const TChr *batch_result = "batch_result";
    inline static const TChr *timestamp_created = "timestamp_created";
    inline static const TChr *owned = "owned";
    inline static const TChr *owner = "owner";
    inline static const TChr *claimed_date_and_time = "claimed_date_and_time";
    inline static const TChr *claimed_date_and_time_num = "claimed_date_and_time_num";
};

} // namespace prgent

#endif // PRGENT_BATCH_TYPES_HH
