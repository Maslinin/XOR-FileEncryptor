#include "xorencoder.h"

#include "../Customs/cstmio.h"
#include "../Customs/cstmstr.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

static int encrypt_or_decrypt_file(const char* srcFilePath, const char* trgFilePath, const char* key, int mode);
static int open_source_and_target_files(const char* srcFilePath, const char* trgFilePath, FILE* fs, FILE* ft);
static int close_source_and_target_files(FILE* fs, FILE* ft);
static char encrypt_byte(char ch, const char* key);
static char decrypt_byte(char ch, const char* key);

inline int encrypt_file(const char* srcFilePath, const char* trgFilePath, const char* key)
{
    return (encrypt_or_decrypt_file(srcFilePath, trgFilePath, key, 1) == EXIT_FAILURE) ? EXIT_FAILURE : EXIT_SUCCESS;
}

inline int decrypt_file(const char* srcFilePath, const char* trgFilePath, const char* key)
{
    return (encrypt_or_decrypt_file(srcFilePath, trgFilePath, key, 0) == EXIT_FAILURE) ? EXIT_FAILURE : EXIT_SUCCESS;
}

static int encrypt_or_decrypt_file(const char* srcFilePath, const char* trgFilePath, const char* key, int mode)
{
    FILE* fs, *ft;
    char ch = '\0';

    if (open_source_and_target_files(srcFilePath, trgFilePath, fs, ft) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }

    while (!feof(fs))
    {
        fread(&ch, sizeof(ch), 1, fs);
        if (mode)
            ch = encrypt_byte(ch, key);
        else
            ch = decrypt_byte(ch, key);
        fwrite(&ch, sizeof(ch), 1, ft);
    }
    close_source_and_target_files(fs, ft);

    return EXIT_SUCCESS;
}

static int open_source_and_target_files(const char* srcFilePath, const char* trgFilePath, FILE* outFs, FILE* outFt)
{
    outFs = fopen(srcFilePath, "rb");
    outFt = fopen(trgFilePath, "wb");

    if (outFs == NULL)
    {
        return EXIT_FAILURE;
    }
    if (outFt == NULL)
    {
        fclose(outFs);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

static inline int close_source_and_target_files(FILE* fs, FILE* ft)
{
    return (fclose(fs) != EOF || fclose(ft) != EOF) ? EXIT_FAILURE : EXIT_SUCCESS;
}

static char encrypt_byte(char ch, const char* key)
{
    int i, keyLength = ((int)strlen(key));

    for (i = 0; i < keyLength; ++i)
    {
        ch ^= key[i];
    }

    return ch;
}

static char decrypt_byte(char ch, const char* key)
{
    int i, keyLength = ((int)(strlen(key) - 1));

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
