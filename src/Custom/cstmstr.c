#include "cstmstr.h"

#include <string.h>

void remove_spaces(char* str)
{
    char* ch, * temp = str;

    while ((ch = strchr(str, ' ')))
    {
        str = ch;
        while (*str)
        {
            *str = *(str + 1);
            ++str;
        }
        str = temp;
    }
}