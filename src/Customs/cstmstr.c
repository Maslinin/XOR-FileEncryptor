#include "cstmstr.h"

#include <ctype.h>
#include <stddef.h>

char *get_first_space(const char *str)
{
    //while in the string non-zero character
    while (*str)
    {
        if (isspace(*str))
        {
            return (char*) str;
        }
        ++str;
    }

    return NULL;
}

char *del_spaces(char *str)
{
    char *ch, *temp = str;

    if(!str)
    {
        return NULL;
    }

    while ((ch = get_first_space(str)))
    {
        str = ch;
        while (*str)
        {
            *str = *(str + 1);
            ++str;
        }
        str = temp;
    }

    return str;
}
