#include "cstmio.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
            clear_stdin_buff();
    }

    return res;
}

void clear_stdin_buff(void)
{
    clear_buff(stdin);
}

void clear_buff(FILE* stream)
{
    int pos, ch;

    fseek(stream, 0, SEEK_END);
    pos = ftell(stream);

    //If there are symbols in the stream
    if (pos)
    {
        ch = getchar();
        while (ch != '\n' || ch != EOF)
        {
            ch = getchar();
        }
    }
}

int file_exists_check(const char* filePath)
{
    FILE* fs = fopen(filePath, "rb");

    return (fs != NULL && fclose(fs) != EOF) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int check_file_path_availability(const char* filePath)
{
    FILE* fs = fopen(filePath, "wb");

    return (fs != NULL && fclose(fs) != EOF && remove(filePath) == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
