#ifndef LIBPRCPP_ISCYLLADB_CORE_INTERFACE_H
#define LIBPRCPP_ISCYLLADB_CORE_INTERFACE_H
#include <libprcpp/base/config.h>

#include <string>
#include <iostream>

#if LIBPRCPP_PROJECT_USING_SCYLLADB
#include <libprcpp/enums/scylla_enums.h>

#include <libprcpp/types/auth_types.h>
#include <libprcpp/types/scylla_types.h>

#include <cassandra.h>

namespace libprcpp
{

class IScyllaDbCoreInterface
{
private:
    inline static TScyllaDbConnection m_connectionData;

public:
    virtual ~IScyllaDbCoreInterface();

    /**
     * @brief initialize type implementation
     * 
     */
    virtual void initializeType() = 0;

    /**
     * @brief initialize table implementation
     * 
     */
    virtual void initializeTable() = 0;

    /**
     * @brief alterize current table implementation
     * 
     */
    virtual void alterizeCurrentTable() = 0;

    /**
     * @brief static on auth scylladb structure
     * 
     */
    struct OnAuth
    {
        static void initialize(CassAuthenticator *pCassAuth, void *pVoidData);

        static void challenge(CassAuthenticator *pCassAuth, void *pVoidData, const char *pToken, size_t tokenSize);

        static void success(CassAuthenticator *pCassAuth, void *pVoidData, const char *pToken, size_t tokenSize);

        static void cleanup(CassAuthenticator *pCassAuth, void *pVoidData);
    };

    /**
     * @brief scylladb interface structure
     * 
     */
    struct SIScyllaDb
    {
        virtual ~SIScyllaDb();

        /**
         * @brief scylladb print error
         * 
         * @param pCassFuture 
         * @param info 
         */
        void printError(CassFuture *pCassFuture, const char *info = "");

        /**
         * @brief immediately initialize pointer/s for session & cluster
         * 
         * @note should be call in constructor before any usage
         * 
         * @param connectionData 
         */
        void initializeConstructor(const TScyllaDbConnection &connectionData);

        /**
         * @brief get this keyspace project
         * 
         * @return std::string 
         */
        std::string getKeyspace() { return IScyllaDbCoreInterface::m_connectionData.keyspace; }

        std::string generateUuidV1AsString();
        std::string generateUuidV4AsString();
        std::string cassUuidToString(const CassUuid &uuidCass);

        /**
         * @brief get this project topology strategy
         * 
         * @note 0:undefined 1:SimpleStrategy 2:NetworkTopologyStrategy 3:LocalStrategy 4:EverywhereStrategy
         * 
         * @return EScyllaDbTopologyStrat::Enum 
         */
        EScyllaDbTopologyStrat::Enum getStrategy() { return IScyllaDbCoreInterface::m_connectionData.strategy; };

        /**
         * @brief get this project auth mode
         * 
         * @note 0:undefined 1:AllowAllAuthenticator 2:PasswordAuthenticator 3:com.scylladb.auth.TransitionalAuthenticator
         * 
         * @return EScyllaDbAuthMode::Enum 
         */
        EScyllaDbAuthMode::Enum getAuthMode() { return IScyllaDbCoreInterface::m_connectionData.auth_mode; }

        /**
         * @brief execute cqlsh command
         * 
         * @param pCassSession 
         * @param pQuery 
         * @return CassError 
         */
        CassError executeQuery(CassSession *pCassSession, const char *pQuery);

        /**
         * @brief get CassFuture pointer
         * 
         * @return CassFuture* 
         */
        CassFuture *getCassFuturePtr() { return m_pCassFuture; }

        /**
         * @brief get CassCluster pointer
         * 
         * @return CassCluster* 
         */
        CassCluster *getCassClusterPtr() { return m_pCassCluster; }

        /**
         * @brief get CassSession pointer
         * 
         * @return CassSession* 
         */
        CassSession *getCassSessionPtr() { return m_pCassSession; }

        CassUuid generateUuidV1();
        CassUuid generateUuidV4();
        CassUuid stringToCassUuid(const std::string &uuidStr);

    private:
        CassFuture *m_pCassFuture = nullptr;

        CassCluster *m_pCassCluster = nullptr;

        CassSession *m_pCassSession = nullptr;
    };
    // scylladb interface access
    SIScyllaDb IScyllaDb = SIScyllaDb();
};

} // namespace libprcpp

#endif // LIBPRCPP_PROJECT_USING_SCYLLADB

#endif // LIBPRCPP_ISCYLLADB_CORE_INTERFACE_H
