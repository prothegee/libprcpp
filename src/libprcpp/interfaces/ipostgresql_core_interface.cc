#include "ipostgresql_core_interface.hh"

#if LIBPRCPP_PROJECT_USING_POSTGRESQL

namespace libprcpp
{

IPostgreSQLCoreInterface::~IPostgreSQLCoreInterface()
{
}

IPostgreSQLCoreInterface::SIPostgreSQL::~SIPostgreSQL()
{
    if (m_pPgConn != nullptr) { PQfinish(m_pPgConn); }
}

void IPostgreSQLCoreInterface::SIPostgreSQL::initializeDb(const TPostgreSQLConnection &connectionData, const bool &createDb)
{
    IPostgreSQLCoreInterface::m_connectionData.dbname = connectionData.dbname;
    IPostgreSQLCoreInterface::m_connectionData.host = connectionData.host;
    IPostgreSQLCoreInterface::m_connectionData.port = connectionData.port;
    IPostgreSQLCoreInterface::m_connectionData.username = connectionData.username;
    IPostgreSQLCoreInterface::m_connectionData.password = connectionData.password;

    std::string conninfo;

    try
    {
        if (createDb)
        {
            if (connectionData.password.length() <= 0)
            {
                conninfo = "user=" + connectionData.username + " host=" + connectionData.host + " port=" + connectionData.port;
            }
            else
            {
                conninfo = "user=" + connectionData.username + " host=" + connectionData.host + " port=" + connectionData.port + " password=" + connectionData.password;
            }

            PGresult *pRes = nullptr;

            m_pPgConn = PQconnectdb(conninfo.c_str());

            if (PQstatus(m_pPgConn) != CONNECTION_OK)
            {
                std::cerr << "ERROR: postgresql connection error, check your config\n";
                abort();
            }
            else
            {
                std::string query = "create database " + connectionData.dbname + ";";

                pRes = PQexec(m_pPgConn, query.c_str());

                if (PQresultStatus(pRes) != PGRES_COMMAND_OK)
                {
                    std::cerr << PQerrorMessage(m_pPgConn) << "\n";
                }
                else
                {
                    #if LIBPRCPP_BUILD_STATUS == 1
                    std::cout << "DEBUG: database created\n";
                    #endif
                }
            }

            if (pRes != nullptr) { PQclear(pRes); }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

std::string IPostgreSQLCoreInterface::SIPostgreSQL::generateUuidV1AsString()
{
    std::string result = "";

    PGresult *pPgRes = nullptr;

    if (PQstatus(m_pPgConn) == CONNECTION_OK)
    {
        pPgRes = PQexec(m_pPgConn, "SELECT uuid_generate_v1();");
        result = PQgetvalue(pPgRes, 0, 0);
    }
    else
    {
        std::cerr << "ERROR: connection to database failed: " << PQerrorMessage(m_pPgConn) << "\n";
    }

    PQclear(pPgRes);

    return result;
}

std::string IPostgreSQLCoreInterface::SIPostgreSQL::generateUuidV4AsString()
{
    std::string result = "";

    PGresult *pPgRes = nullptr;

    if (PQstatus(m_pPgConn) == CONNECTION_OK)
    {
        pPgRes = PQexec(m_pPgConn, "SELECT uuid_generate_v4();");
        result = PQgetvalue(pPgRes, 0, 0);
    }
    else
    {
        std::cerr << "ERROR: connection to database failed: " << PQerrorMessage(m_pPgConn) << "\n";
    }

    PQclear(pPgRes);

    return result;
}

} // namespace libprcpp

#endif // LIBPRCPP_PROJECT_USING_POSTGRESQL
