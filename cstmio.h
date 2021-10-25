#ifndef _CSTMIO_H
    #define _CSTMIO_H
        #include <stdio.h>
        #include <string.h>
        #include <ctype.h>

        //Интерфейс заголовочного файла
        //Функция ввода строки. Заменяет символ новой строки нулевым символом.
        char* s_gets(char* str, int value);
        //Функция очистки буфера ввода stdin
        void clear_buff(void);
        //удаляет все пробельные символы из строки
        void del_spaces(char str[]);
#endif // _CSTMIO_H
