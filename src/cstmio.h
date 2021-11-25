#ifndef _CSTMIO_H
    #define _CSTMIO_H
        #include <stdio.h>
        #include <string.h>
        #include <ctype.h>

        //Line entry function. Replaces the new line character with a null character.
        char* s_gets(char* str, int value);
        //stdin input buffer cleaning function
        void clear_buff(void);
        //removes all space characters from the string
        void del_spaces(char str[]);
#endif // _CSTMIO_H
