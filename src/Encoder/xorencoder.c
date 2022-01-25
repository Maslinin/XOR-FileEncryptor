#include "xorencoder.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//A local function that encrypts the specified character with each character of the key passed to it:
static char charencrypt(char ch, const char* key, int mode)
{
    int i;
    if(mode) //if we encrypt
        for(i = 0; i < strlen(key); ++i)
        {
            ch ^= key[i];
        }
    else //if we decrypt
        for(i = strlen(key) - 1; i >= 0; --i)
        {
            ch ^= key[i];
        }

    return ch;
}

//File encryption (mode 1 - encryption, 0 - decryption):
int file_encode(const char *srcFilePath, const char *trgtFilePath, const char *key, int encryptMode, int srcFileDelFlag)
{
    FILE * fs, * ft;
    char ch;

    //Open files in binary mode:
    if(!(fs = fopen(srcFilePath, "rb")))
    {
        perror(srcFilePath);
        return EXIT_FAILURE;
    }
    if(!(ft = fopen(trgtFilePath, "wb")))
    {
        fclose(fs);
        perror(trgtFilePath);
        return EXIT_FAILURE;
    }

    //Encryption/decryption:
    while(!feof(fs))
    {
        fread(&ch, sizeof(ch), 1, fs);
        ch = charencrypt(ch, key, encryptMode);
        fwrite(&ch, sizeof(ch), 1, ft);
    }
    fclose(fs);
    fclose(ft);

    //If the delete source file flag is
    if(srcFileDelFlag)
    {
        if(remove(srcFilePath))
        {
            return EXIT_FAILURE;
        }
    }

    return 0;
}

char *generate_key(char *str, int size)
{
    int i;
    //Set the grain of the random number generator so that each time the start is different key
    srand(time(NULL));

    for(i = 0; i < size; ++i)
        str[i] = rand()%95 + 33; //character range in ASCII

    del_spaces(str);
    str[i - 1] = '\0';

    return str;
}
