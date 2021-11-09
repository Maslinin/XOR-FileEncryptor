#include "cstmio.h"

//Local function that finds the space character in the string.
static char* chr_isspace(char str[]);

char* s_gets(char* str, int value)
{
    char* res;
    res = fgets(str, value, stdin);
    if(res) // != NULL
    {
        char* symb = strchr(res, '\n');
        if(symb)
            *symb = '\0';
        else
            clear_buff();
    }

    return res;
}
void clear_buff(void)
{
    int pos;
    fseek(stdin, 0, SEEK_END);
    pos = ftell(stdin);

    //If there are symbols in the stream
    if(pos != 0)
        while(getchar() != '\n')
            continue;

    return;
}
void del_spaces(char str[])
{
    char* ch, * temp = str;
    while ((ch = chr_isspace(str)))
    {
        str = ch;
        while (*str)
        {
            *str = *(str + 1);
            ++str;
        }
        str = temp;
    }

    return;
}

static char* chr_isspace(char str[])
{
    //while in the string non-zero character
    while (*str)
    {
        if (isspace(*str))
            return str;
        ++str;
    }

    return NULL;
}
