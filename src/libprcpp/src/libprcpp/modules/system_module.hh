#ifndef LIBPRCPP_SYSTEM_MODULE_HH
#define LIBPRCPP_SYSTEM_MODULE_HH
#include <libprcpp/base/config.hh>

#include <libprcpp/enums/encdec_enums.hh>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <thread>
#include <sstream>
#include <cstring>

// includes os specification
#if PROJECT_BUILD_TARGET == 1
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#elif PROJECT_BUILD_TARGET == 2
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
#elif PROJECT_BUILD_TARGET == 3
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#else
// nothing to include
#endif // PROJECT_BUILD_TARGET

#if LIBPRCPP_PROJECT_USING_LIBHARU
#include "hpdf.h"
#include <libprcpp/types/pdf_types.hh>
#endif // LIBPRCPP_PROJECT_USING_LIBHARU

#if LIBPRCPP_PROJECT_USING_JSONCPP
#include <json/json.h>
#endif // LIBPRCPP_PROJECT_USING_JSONCPP

#if LIBPRCPP_PROJECT_USING_OPENSSL
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
#include <cryptopp/cryptlib.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>
#include <cryptopp/chacha.h>
#include <cryptopp/rc6.h>
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

namespace libprcpp
{
} // namespace libprcpp

#endif // LIBPRCPP_SYSTEM_MODULE_HH
