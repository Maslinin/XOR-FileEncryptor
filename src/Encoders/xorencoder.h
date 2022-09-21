#ifndef _XORENCODER_H
#define _XORENCODER_H

#define KEY_LENGTH BUFSIZ

char* generate_key(char* str, int size);
int encrypt_file(const char* srcFilePath, const char* trgFilePath, const char* key);
int decrypt_file(const char* srcFilePath, const char* trgFilePath, const char* key);

#endif // _XORENCODER_H
