#ifndef _ENCODER_H
#define _ENCODER_H

#include "../Custom/cstmio.h"
#include "../Custom/cstmstr.h"

//Encryption Interface:
int file_encode(const char *srcFilePath, const char *trgtFilePath, const char *key, int encryptMode, int srcFileDelFlag);
char *generate_key(char *str, int size);

#endif // _ENCODER_H
