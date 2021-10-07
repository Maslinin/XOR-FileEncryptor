#include <stdio.h>
#include <locale.h>
#include "encoder.h"
#define EXIT_SYMBOL 'q'

int main(void)
{
    encodeStr * enc;
    setlocale(LC_ALL, "Rus");
    do
    {
        getchar();
        putchar('\n');
        enc = fill_struct();
        if(encode(enc))
        {//если произошла ошибка в функции
            putchar('\n');
            continue;
        }
        puts("Шифрование завершено. Введите \'q\', что бы закрыть программу, или другой символ, что бы продолжить.");
    }
    while(getchar() != EXIT_SYMBOL);
    FREE_MEM(enc);
    puts("Программа успешно завершила свое выполнение");
    return 0;
}
