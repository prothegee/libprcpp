#ifndef LIBPRCPP_ISCYLLADB_CORE_INTERFACE_H
#define LIBPRCPP_ISCYLLADB_CORE_INTERFACE_H
#include <libprcpp/base/config.h>

#include <string>
#include <iostream>

#if PROJECT_USING_SCYLLADB
#include <libprcpp/types/auth_types.h>

#include <cassandra.h>

namespace libprcpp
{

class IScyllaDbCoreInterface
{
private:
    static const char *m_host;
    static const char *m_username;
    static const char *m_password;

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
         * @brief get this project topology strategy
         * 
         * @note 0:undefined 1:SimpleStrategy 2:NetworkTopologyStrategy 3:LocalStrategy 4:EverywhereStrategy
         * 
         * @return int 
         */
        int getStrategy() { return m_strategy; };

        /**
         * @brief get this project auth mode
         * 
         * @return int 
         */
        int getAuthMode() { return m_authMode; }

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
         */
        void initializeConstructor(const std::string &host, const std::string &username, const std::string &password, const int &authMode, std::string &keyspace, const int &strategy, const int &replicationFactor);

        /**
         * @brief get this keyspace project
         * 
         * @return std::string 
         */
        std::string getKeyspace() { return m_keyspace; }

        std::string generateUuidV1AsString();
        std::string generateUuidV4AsString();
        std::string cassUuidToString(const CassUuid &uuidCass);

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
        int m_strategy; // 0:undefined 1:SimpleStrategy 2:NetworkTopologyStrategy 3:LocalStrategy 4:EverywhereStrategy 
        int m_authMode; // 0:undefined 1:AllowAllAuthenticator 2:PasswordAuthenticator 3:com.scylladb.auth.TransitionalAuthenticator
        int m_replicationFactor;

        std::string m_keyspace;

        CassFuture *m_pCassFuture = nullptr;

        CassCluster *m_pCassCluster = nullptr;

        CassSession *m_pCassSession = nullptr;
    };
    // scylladb interface access
    SIScyllaDb IScyllaDb = SIScyllaDb();
};

} // namespace libprcpp

#endif // PROJECT_USING_SCYLLADB

#endif // LIBPRCPP_ISCYLLADB_CORE_INTERFACE_H
