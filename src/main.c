#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Encoders/xorencoder.h"
#include "Customs/cstmio.h"
#include "Customs/cstmstr.h"
#include "Constants.h"

#define DOWN putchar('\n')
#define CLEAR_STDIN clear_stdin_buff()

char* get_path(char* forPath, int keyLength, const char* file_mode);
int check_path(const char* path, const char* fileMode);
int get_int();
char* input_key(char* storage, int size);

int main(void)
{
    int encMode = 0, keyMode = 0;
    char s_path[PATH_LENGTH], t_path[PATH_LENGTH];
    char key[KEY_LENGTH];
    int exitCh;

    do
    {
        puts(INPUT_SOURCE_FILE_MESSAGE);
        while(get_path(s_path, KEY_LENGTH, "rb") == NULL)
        {
            perror(NULL);
            DOWN;
            puts(INPUT_SOURCE_FILE_MESSAGE);
        }
        CLEAR_STDIN;
        DOWN;

        puts(INPUT_TARGET_FILE_MESSAGE);
        while(get_path(t_path, PATH_LENGTH, "wb") == NULL)
        {
            perror(NULL);
            DOWN;
            puts(INPUT_TARGET_FILE_MESSAGE);
        }
        CLEAR_STDIN;
        DOWN;

        fputs(INPUT_ENCODER_MODE_MESSAGE, stdout);
        while(scanf("%d", &encMode) == 0)
        {
            perror(NULL);
            CLEAR_STDIN;
            DOWN;
            fputs(INPUT_ENCODER_MODE_MESSAGE, stdout);
        }
        CLEAR_STDIN;
        DOWN;

        if(encMode)
        {
            fputs(INPUT_KEY_MODE_MESSAGE, stdout);
            while(scanf("%d", &keyMode) == 0)
            {
                perror(NULL);
                CLEAR_STDIN;
                DOWN;
                fputs(INPUT_KEY_MODE_MESSAGE, stdout);
            }
            CLEAR_STDIN;
            DOWN;
        }

        if(encMode && keyMode)
        {
            generate_key(key, KEY_LENGTH);
        }
        else
        {
            puts(INPUT_MASK_MESSAGE);
            while(input_key(key, KEY_LENGTH) != NULL)
            {
                perror(NULL);
                CLEAR_STDIN;
                DOWN;
                puts(INPUT_MASK_MESSAGE);
            }
        }
        CLEAR_STDIN;
        DOWN;

        encMode ? puts("Encrypting file...") : puts("Decrypting file...");
        if(encMode)
        {
            if(encrypt_file(s_path, t_path, key) == EXIT_SUCCESS)
            {
                puts("The file was successfully encrypted. Your key:");
                puts(key);
            }
            else
            {
                perror("Encryption failed. Please, try again");
                DOWN;
            }
        }
        else
        {
            if(decrypt_file(s_path, t_path, key) == EXIT_SUCCESS)
            {
                puts("The file was successfully decrypted.");
            }
            else
            {
                perror("Decryption failed. Please, try again");
                DOWN;
            }
        }

        printf("Input \'%c\' to exit or any other key if you want to continue\n", EXIT_SYMBOL);
        fputs("Input a symbol: ", stdout);
        exitCh = getchar();

        CLEAR_STDIN;
        DOWN;
    }
    while(exitCh != EXIT_SYMBOL);

    return 0;
}

char* get_path(char* forPath, int keyLength, const char* fileMode)
{
    FILE* fs = NULL;

    s_gets(forPath, keyLength);
    remove_spaces(forPath);

    if(check_path(forPath, fileMode) == EXIT_FAILURE)
    {
        return NULL;
    }

    return forPath;
}

int check_path(const char* path, const char* fileMode)
{
    if (strcmp(fileMode, "rb") == 0 && file_exists_check(path))
    {
        return EXIT_FAILURE;
    }
    if(strcmp(fileMode, "wb") == 0 && check_file_path_availability(path))
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int get_int()
{
    int arrSize = 10;
    char str[arrSize];

    s_gets(str, arrSize);
    if(str == NULL)
    {
        return 0;
    }
}

char* input_key(char* forKey, int size)
{
    s_gets(forKey, size);
    remove_spaces(forKey);

    return forKey;
}
