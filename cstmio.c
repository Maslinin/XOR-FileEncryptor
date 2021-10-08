#include "cstmio.h"

char* s_gets(char* str, int value)
{
    char* res;
    res = fgets(str, value, stdin);
    if(res) // != NULL
    {
        del_spaces(res);
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
    if(pos != 0)
        while(getchar() != '\n')
            continue;
    return;
}

char* chr_isspace(char str[])
{
    while (*str)
    {
        if (isspace(*str))
            return str;
        ++str;
    }
    return NULL;
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
