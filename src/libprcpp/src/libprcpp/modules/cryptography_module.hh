#ifndef LIBPRCPP_CRYPTOGRAPHY_MODULE_HH
#define LIBPRCPP_CRYPTOGRAPHY_MODULE_HH
#include <libprcpp/base/config.hh>

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
#include <cryptopp/ec2n.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/secblock.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/words.h>

#include <cryptopp/blake2.h>
#include <cryptopp/scrypt.h>
#include <cryptopp/sha.h>
#include <cryptopp/gcm.h>
#include <cryptopp/aes.h>
#include <cryptopp/chacha.h>
#include <cryptopp/rc6.h>
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

#if LIBPRCPP_PROJECT_USING_OPENSSL
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_ARGON2
#include <argon2.h>
#endif // LIBPRCPP_PROJECT_USING_ARGON2

#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <vector>

namespace libprcpp
{
} // namespace libprcpp

#endif // LIBPRCPP_CRYPTOGRAPHY_MODULE_HH
