#include "xorencryptor.h"

#include "../IO/cstmio.h"
#include "../Customs/cstmstr.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

static int encrypt_or_decrypt_file(const char* srcFilePath, const char* trgFilePath, const char* key, int mode);
static int files_are_open(FILE* fs, FILE* ft);
static char encrypt_byte(char ch, const char* key);
static char decrypt_byte(char ch, const char* key);

inline int encrypt_file(const char* srcFilePath, const char* trgFilePath, const char* key)
{
    return (encrypt_or_decrypt_file(srcFilePath, trgFilePath, key, 1) == EXIT_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE;
}

inline int decrypt_file(const char* srcFilePath, const char* trgFilePath, const char* key)
{
    return (encrypt_or_decrypt_file(srcFilePath, trgFilePath, key, 0) == EXIT_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE;
}

static int encrypt_or_decrypt_file(const char* srcFilePath, const char* trgFilePath, const char* key, int mode)
{
    FILE* fs = fopen(srcFilePath, "rb");
    FILE* ft = fopen(trgFilePath, "wb");
    char ch = '\0';

    if (files_are_open(fs, ft) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }

    while (!feof(fs))
    {
        read_byte_from_file(fs, &ch);
        if (mode)
            ch = encrypt_byte(ch, key);
        else
            ch = decrypt_byte(ch, key);
        write_byte_to_file(ft, &ch);
    }

    return (fclose(fs) != EOF && fclose(ft) != EOF) ? EXIT_SUCCESS : EXIT_FAILURE;
}

static int files_are_open(FILE* fs, FILE* ft)
{
    if (fs == NULL)
    {
        return EXIT_FAILURE;
    }
    if (ft == NULL)
    {
        fclose(fs);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

static char encrypt_byte(char ch, const char* key)
{
    int i;
    int keyLength = (int)strlen(key);

    for (i = 0; i < keyLength; ++i)
    {
        ch ^= key[i];
    }

    return ch;
}

static char decrypt_byte(char ch, const char* key)
{
    int i;
    int keyLength = (int)(strlen(key) - 1);

    for (i = keyLength; i >= 0; --i)
    {
        ch ^= key[i];
    }

    return ch;
}

char* generate_key(char* str, int size)
{
    int i;

    srand((unsigned int)time(NULL));

    for (i = 0; i < size; ++i)
    {
        str[i] = rand()%95 + 33; //character range in ASCII
    }

    remove_spaces(str);
    str[size - 1] = '\0';

    return str;
}
