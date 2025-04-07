#ifndef XORCIPHER_H
#define XORCIPHER_H

#include <stddef.h>

char *generateKey(char *buffer, size_t size);

int encryptFile(const char *srcFilePath, const char *destFilePath, const char *key);
int decryptFile(const char *srcFilePath, const char *destFilePath, const char *key);

#endif // XORCIPHER_H