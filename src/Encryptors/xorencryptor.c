#include "xorencryptor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *generateKey(char *buffer, size_t size)
{
    if (size == 0)
    {
        return buffer;
    }

    srand((unsigned int) time(NULL));
    for (size_t i = 0; i < size - 1; ++i)
    {
        buffer[i] = (char) ((rand() % 94) + 33);
    }

    buffer[size - 1] = '\0';
    return buffer;
}

int encryptFile(const char *srcFilePath, const char *destFilePath, const char *key)
{
    FILE *fs = fopen(srcFilePath, "rb");
    if (!fs)
    {
        return EXIT_FAILURE;
    }

    FILE *ft = fopen(destFilePath, "wb");
    if (!ft)
    {
        fclose(fs);
        return EXIT_FAILURE;
    }

    int result = EXIT_SUCCESS;
    
    int ch;
    size_t keyIndex = 0, keyLength = strlen(key);

    while ((ch = fgetc(fs)) != EOF)
    {
        unsigned char encrypted = (unsigned char)ch ^ key[keyIndex];
        if (fputc(encrypted, ft) == EOF)
        {
            result = EXIT_FAILURE;
            break;
        }
        keyIndex = (keyIndex + 1) % keyLength;
    }

    if (ferror(ft))
    {
        result = EXIT_FAILURE;
    }

    fclose(fs);
    fclose(ft);

    return result;
}

int decryptFile(const char *srcFilePath, const char *destFilePath, const char *key)
{
    return encryptFile(srcFilePath, destFilePath, key);
}