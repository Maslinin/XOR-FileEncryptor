#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include "encoder.h"
#include "cstmio.h"

#define EXIT_SYMBOL 'q'
#define END_INPUT_TEXT "Шифрование завершено. Введите \'q\', что бы закрыть программу, или другой символ, что бы продолжить."
#define END_TEXT "Программа успешно завершила свое выполнение"

void call(ENCODE_INFO * enc);
int main(void)
{
    ENCODE_INFO * enc = (ENCODE_INFO *)malloc(sizeof(ENCODE_INFO));
    setlocale(LC_ALL, "Rus");

    //Ввод режима работы программы:
    call(enc);
    puts(END_INPUT_TEXT);
    while(getchar() != EXIT_SYMBOL)
    {
        putchar('\n');
        clear_buff();
        call(enc);
        puts(END_INPUT_TEXT);
    }
    ENCODE_INFO_FREE(enc);
    puts(END_TEXT);
    return 0;
}
void call(ENCODE_INFO * enc)
{
    FillEncodeInfo(enc);
    if(!Encode(enc))
        putchar('\n');
    else
        ShowKey(enc);
    return;
}

