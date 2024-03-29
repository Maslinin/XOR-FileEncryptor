#include "cstmio.h"
#include "../Custom/cstmstr.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int check_path_correct_by_mode(const char* path, const char* fileMode);

char* s_gets(char* str, int len)
{
    char* res, *symb;
    res = fgets(str, len, stdin);

    if (res != NULL)
    {
        symb = strchr(res, '\n');
        if (symb != NULL)
            *symb = '\0';
        else
            CLEAR_STDIN;
    }

    return res;
}

void clear_buff(FILE* stream)
{
    int pos, ch;

    fseek(stream, 0, SEEK_END);
    pos = ftell(stream);

    if (pos)
    {
        ch = getchar();
        while (ch != '\n' || ch != EOF)
        {
            ch = getchar();
        }
    }
}

char* get_valid_path(char* forPath, int keyLength, const char* fileMode)
{
    s_gets(forPath, keyLength);
    remove_spaces(forPath);

    if (check_path_correct_by_mode(forPath, fileMode) == EXIT_FAILURE)
    {
        return NULL;
    }

    return forPath;
}

static int check_path_correct_by_mode(const char* path, const char* fileMode)
{
    if (strcmp(fileMode, "rb") == 0 && file_exists(path) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }
    if (strcmp(fileMode, "wb") == 0 && file_path_is_valid(path) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int file_exists(const char* filePath)
{
    FILE* fs = fopen(filePath, "rb");

    return (fs != NULL && fclose(fs) != EOF) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int file_path_is_valid(const char* filePath)
{
    FILE* fs = fopen(filePath, "wb");

    return (fs != NULL && fclose(fs) != EOF && remove(filePath) == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int read_byte_from_file(FILE* fs, char* byte)
{
    fread(byte, sizeof(*byte), 1, fs);

    return ferror(fs);
}

int write_byte_to_file(FILE* fs, const char* byte)
{
    fwrite(byte, sizeof(*byte), 1, fs);

    return ferror(fs);
}