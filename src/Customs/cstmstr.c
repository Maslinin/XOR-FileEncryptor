#include "cstmstr.h"

#include <ctype.h>
#include <string.h>
#include <stddef.h>

void remove_spaces(char* str)
{
    char* ch,* temp = str;

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
