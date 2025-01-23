#ifndef LIBPRCPP_IPOSTGRESQL_CORE_INTERFACE_HH
#define LIBPRCPP_IPOSTGRESQL_CORE_INTERFACE_HH
#include <libprcpp/base/config.hh>

#if LIBPRCPP_PROJECT_USING_POSTGRESQL
#if LIBPRCPP_PROJECT_USING_POSTGRESQL_HAS_PARENT_DIR
#include <postgresql/libpq-fe.h>
#else
#include <libpq-fe.h>
#endif

#include <libprcpp/types/postgresql_types.hh>

#include <iostream>

namespace libprcpp
{

/**
 * @brief libprcpp postgresql interface class
 * 
 * @note meant to use on drogon-framework project
 * @note still don't have test & not much functionalities
 */
class IPostgreSQLCoreInterface
{
private:
    inline static TPostgreSQLConnection m_connectionData;

protected:
    /* data */

public:
    virtual ~IPostgreSQLCoreInterface();

    /**
     * @brief initialize table implementation
     * 
     */
    virtual void initializeTable() = 0;

    /**
     * @brief initialized indexe table implementation
     * 
     * @note considering index on table is just 1
     */
    virtual void initializeIndex() = 0;

    /**
     * @brief alterize current table implementation
     * 
     */
    virtual void alterizeCurrentTable() = 0;

    /**
     * @brief alterize current table with materialized view implementation
     * 
     */
    virtual void alterizeMaterializedView() = 0;

    /**
     * @brief postgresql interface structure
     * 
     */
    struct SIPostgreSQL
    {
        virtual ~SIPostgreSQL();

        /**
         * @brief initialize database
         * 
         * @note this function meant to be use inside drogon plugin at first
         * @note by default 'createDb' is false, when it true, it will create database at initialize
         * 
         * @param connectionData 
         * @param createDb 
         */
        void initializeDb(const TPostgreSQLConnection &connectionData, const bool &createDb = false);

        std::string generateUuidV1AsString();
        std::string generateUuidV4AsString();

    private:
        PGconn *m_pPgConn = nullptr;
    };
    // postgresql interface access
    SIPostgreSQL IPostgreSQL = SIPostgreSQL();
};

} // namespace libprcpp

#endif // LIBPRCPP_PROJECT_USING_POSTGRESQL

#endif // LIBPRCPP_IPOSTGRESQL_CORE_INTERFACE_HH
