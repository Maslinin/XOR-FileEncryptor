#ifndef _XORENCRYPTER_H
#define _XORENCRYPTER_H

extern inline int encrypt_file(const char* srcFilePath, const char* trgFilePath, const char* key);
extern inline int decrypt_file(const char* srcFilePath, const char* trgFilePath, const char* key);
char* generate_key(char* str, int size);

#endif // _XORENCRYPTER_H
