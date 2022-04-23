#include "cstmio.h"

#include <stdio.h>
#include <string.h>

void clean_stdin_buff(void)
{
    int pos;
    fseek(stdin, 0, SEEK_END);
    pos = ftell(stdin);

    //If there are symbols in the stream
    if(pos)
    {
        while(getchar() != '\n')
        {
            continue;
        }
    }
}

char *s_gets(char *str, int len)
{
    char *res, *symb;
    res = fgets(str, len, stdin);

    if(res) // != NULL
    {
        symb = strchr(res, '\n');
        if(symb)
            *symb = '\0';
        else
            clean_stdin_buff();
    }

    return res;
}
