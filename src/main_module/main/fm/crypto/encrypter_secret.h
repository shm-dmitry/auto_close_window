#ifndef MAIN_FM_CRYPTO_ENCRYPTER_SECRET_H_
#define MAIN_FM_CRYPTO_ENCRYPTER_SECRET_H_

#if __has_include("encrypter_secret.private.h")

#pragma message "OK :: Used encrypter_secret.private.h for initializing private defines"

#include "encrypter_secret.private.h"

#else

#pragma message "WARNING! Used public defines. Create 'encrypter_secret.private.h' file in this folder and put same defines with your personal values into it"

// you can use your own key size here. Max key size is a (FM_COMMAND_ARG_MAXSIZE + 2) bytes
#define ENCRYPTER_SECRET_KEY_SIZE 3
#define ENCRYPTER_SECRET_KEY { 0x01, 0x02, 0x03 }

#endif
#endif /* MAIN_FM_CRYPTO_ENCRYPTER_SECRET_H_ */
