#include <libprcpp/interfaces/iscylladb_core_interface.hh>

#include <libprcpp/types/auth_types.hh>

#include <cstring>

#if LIBPRCPP_COMPILER_GNU
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif // LIBPRCPP_COMPILER_GNU
#if LIBPRCPP_COMPILER_MSVC
#endif // LIBPRCPP_COMPILER_MSVC
#if LIBPRCPP_COMPILER_CLANG
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif // LIBPRCPP_COMPILER_CLANG

namespace libprcpp
{

#if LIBPRCPP_USING_SCYLLADB

IScyllaDbCoreInterface::~IScyllaDbCoreInterface()
{
}

void IScyllaDbCoreInterface::OnAuth::initialize(CassAuthenticator *pCassAuth, void *pVoidData)
{
    const TAuthBasic *pCredential = (const TAuthBasic*)new TAuthBasic({
        IScyllaDbCoreInterface::m_connectionData.username.c_str(),
        IScyllaDbCoreInterface::m_connectionData.password.c_str()
    });

    size_t username_size = strlen(pCredential->username);
    size_t password_size = strlen(pCredential->password);
    size_t size = username_size + password_size + 2;

    char *response = cass_authenticator_response(pCassAuth, size);

    response[0] = '\0';
    memcpy(response + 1, pCredential->username, username_size);

    response[username_size + 1] = '\0';
    memcpy(response + username_size + 2, pCredential->password, password_size);

    delete pCredential;
}

void IScyllaDbCoreInterface::OnAuth::challenge(CassAuthenticator *pCassAuth, void *pVoidData, const char *pToken, size_t tokenSize)
{
    /**
     * not used for plain text authentication, but this is to be used for handling an authentication challenge initiated by the server
    */
}

void IScyllaDbCoreInterface::OnAuth::success(CassAuthenticator *pCassAuth, void *pVoidData, const char *pToken, size_t tokenSize)
{
    /**
     * not used for plain text authentication, but this is to be used for handling the success phase of an exchange
    */
}

void IScyllaDbCoreInterface::OnAuth::cleanup(CassAuthenticator *pCassAuth, void *pVoidData)
{
    /**
     * no resources cleanup is necessary for plain text authentication, but this is used to cleanup resources acquired during the authentication exchange
    */
}

IScyllaDbCoreInterface::SIScyllaDb::~SIScyllaDb()
{
    cass_future_free(m_pCassFuture);
    cass_cluster_free(m_pCassCluster);
    cass_session_free(m_pCassSession);
}

void IScyllaDbCoreInterface::SIScyllaDb::printError(CassFuture *pCassFuture, const char *info)
{
    const char* message;
    size_t messageSize;

    cass_future_error_message(pCassFuture, &message, &messageSize);

    fprintf(stderr, "ERROR \"%s\":\n%.*s\n", info, (int)messageSize, message);
}

void IScyllaDbCoreInterface::SIScyllaDb::initializeConstructor(const TScyllaDbConnection &connectionData, const char *extraInfo)
{
    IScyllaDbCoreInterface::m_connectionData.host = connectionData.host;
    IScyllaDbCoreInterface::m_connectionData.username = connectionData.username;
    IScyllaDbCoreInterface::m_connectionData.password = connectionData.password;

    IScyllaDbCoreInterface::m_connectionData.keyspace = connectionData.keyspace;
    IScyllaDbCoreInterface::m_connectionData.strategy = connectionData.strategy;

    IScyllaDbCoreInterface::m_connectionData.multiple_datacenters = connectionData.multiple_datacenters;

    IScyllaDbCoreInterface::m_connectionData.factors_configs = connectionData.factors_configs;
    IScyllaDbCoreInterface::m_connectionData.factors_configs_extra = connectionData.factors_configs_extra;

    if (m_pCassCluster == nullptr) { m_pCassCluster = cass_cluster_new(); }
    if (m_pCassSession == nullptr) { m_pCassSession = cass_session_new(); }

    TAuthBasic *pAuth = new TAuthBasic({
        IScyllaDbCoreInterface::m_connectionData.username.c_str(),
        IScyllaDbCoreInterface::m_connectionData.password.c_str()
    });

    CassAuthenticatorCallbacks authCallbacks = {
        IScyllaDbCoreInterface::OnAuth::initialize,
        IScyllaDbCoreInterface::OnAuth::challenge,
        IScyllaDbCoreInterface::OnAuth::success,
        IScyllaDbCoreInterface::OnAuth::cleanup
    };

    IScyllaDbCoreInterface::m_connectionData.auth_mode = connectionData.auth_mode;

    switch (IScyllaDbCoreInterface::m_connectionData.auth_mode)
    {
        case EScyllaDbAuthMode::SCYLLADB_AUTH_MODE_ALLOW_ALL_AUTHENTICATOR:
        {
            cass_cluster_set_contact_points(m_pCassCluster, IScyllaDbCoreInterface::m_connectionData.host.c_str());

            cass_cluster_set_authenticator_callbacks(m_pCassCluster, &authCallbacks, nullptr, pAuth);
        }
        break;

        case EScyllaDbAuthMode::SCYLLADB_AUTH_MODE_PASSWORD_AUTHENTICATOR:
        {
            cass_cluster_set_contact_points(m_pCassCluster, IScyllaDbCoreInterface::m_connectionData.host.c_str());

            cass_cluster_set_authenticator_callbacks(m_pCassCluster, &authCallbacks, nullptr, pAuth);

            m_pCassFuture = cass_session_connect(m_pCassSession, m_pCassCluster);
        }
        break;

        default:
        {
            std::cerr << "ERROR: core interface for scylladb auth mode is default, it's not implemented\n";
            exit(-1);
        }
        break;
    }

    if (cass_future_error_code(m_pCassFuture) != CASS_OK)
    {
        std::cerr << "ERROR: \"IScyllaDbCoreInterface::SIScyllaDb::initializeConstructor\" fail to make connection on: \"" << extraInfo << "\"\n";
        exit(-1);
    }
    else
    {
        #if LIBPRCPP_BUILD_STATUS == 1
        std::cout << "DEBUG: \"IScyllaDbCoreInterface::SIScyllaDb::initializeConstructor\" connected (" << extraInfo << ")\n";
        #endif 
    }
}

std::string IScyllaDbCoreInterface::SIScyllaDb::generateUuidV1AsString()
{
    CassUuid uuid;

    CassUuidGen *pUuid_gen = cass_uuid_gen_new();

    cass_uuid_gen_time(pUuid_gen, &uuid);

    cass_uuid_gen_free(pUuid_gen);

    char uuidStr[CASS_UUID_STRING_LENGTH];
    cass_uuid_string(uuid, uuidStr);

    return std::string(uuidStr);
}

std::string IScyllaDbCoreInterface::SIScyllaDb::generateUuidV4AsString()
{
    CassUuid uuid;

    CassUuidGen *pUuid_gen = cass_uuid_gen_new();

    cass_uuid_gen_random(pUuid_gen, &uuid);

    cass_uuid_gen_free(pUuid_gen);

    char uuidStr[CASS_UUID_STRING_LENGTH];
    cass_uuid_string(uuid, uuidStr);

    return std::string(uuidStr);
}

std::string IScyllaDbCoreInterface::SIScyllaDb::cassUuidToString(const CassUuid &uuidCass)
{
    std::string result;
    CassUuid _uuidCass = uuidCass;

    char uuid[CASS_UUID_STRING_LENGTH];

    cass_uuid_string(_uuidCass, uuid);

    result = std::string(uuid);

    cass_uuid_from_string(std::string(uuid).c_str(), &_uuidCass);

    return result;
}

CassError IScyllaDbCoreInterface::SIScyllaDb::executeQuery(CassSession *pCassSession, const char *pQuery)
{
    auto pStatement = cass_statement_new(pQuery, 0);

    auto pFuture = cass_session_execute(pCassSession, pStatement);
    cass_future_wait(pFuture);

    auto status = cass_future_error_code(pFuture);

    if (status != CASS_OK)
    {
        printError(pFuture, "");
    }

    cass_future_free(pFuture);
    cass_statement_free(pStatement);

    return status;
}

CassUuid IScyllaDbCoreInterface::SIScyllaDb::generateUuidV1()
{
    CassUuid uuid;

    CassUuidGen *pUuid_gen = cass_uuid_gen_new();

    cass_uuid_gen_time(pUuid_gen, &uuid);

    cass_uuid_gen_free(pUuid_gen);

    return uuid;
}

CassUuid IScyllaDbCoreInterface::SIScyllaDb::generateUuidV4()
{
    CassUuid uuid;

    CassUuidGen *pUuid_gen = cass_uuid_gen_new();

    cass_uuid_gen_random(pUuid_gen, &uuid);

    cass_uuid_gen_free(pUuid_gen);

    return uuid;
}

CassUuid IScyllaDbCoreInterface::SIScyllaDb::stringToCassUuid(const std::string &uuidStr)
{
    CassUuid result;

    char uuid[CASS_UUID_STRING_LENGTH];

    std::string _uuidStr = uuidStr;

    cass_uuid_from_string(_uuidStr.c_str(), &result);

    cass_uuid_string(result, uuid);

    return result;
}

#endif // LIBPRCPP_USING_SCYLLADB

} // namespace libprcpp

#if LIBPRCPP_COMPILER_GNU
#pragma GCC diagnostic pop
#endif // LIBPRCPP_COMPILER_GNU
#if LIBPRCPP_COMPILER_MSVC
#endif // LIBPRCPP_COMPILER_MSVC
#if LIBPRCPP_COMPILER_CLANG
#pragma clang diagnostic pop
#endif // LIBPRCPP_COMPILER_CLANG
