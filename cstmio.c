#include "cstmio.h"

char* s_gets(char* str, int value)
{
    char* return_value;
    return_value = fgets(str, value, stdin);
    if(return_value) // != NULL
    {
        char* symb = strchr(return_value, '\n');
        if(symb)
            *symb = '\0';
        else
        {
            clear_buff();
            str[value - 1] = '\0';
        }
    }
    return return_value;
}
void clear_buff(void)
{
    if(!feof(stdin))
        while(getchar() != '\n')
            continue;
    return;
}
