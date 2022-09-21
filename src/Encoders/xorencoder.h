#ifndef _XORENCODER_H
#define _XORENCODER_H

#define KEY_LENGTH BUFSIZ

extern inline int encrypt_file(const char* srcFilePath, const char* trgFilePath, const char* key);
extern inline int decrypt_file(const char* srcFilePath, const char* trgFilePath, const char* key);
char* generate_key(char* str, int size);

#endif // _XORENCODER_H
