#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "encoder.h"
#include "cstmio.h"
#define EXIT_SYMBOL 'q'
#define END_INPUT_TEXT "Шифрование завершено. Введите \'q\', что бы закрыть программу, или другой символ, что бы продолжить."
#define END_TEXT "Программа успешно завершила свое выполнение"

void call(encodeStr * enc);
int main(void)
{
    encodeStr * enc = (encodeStr *) malloc(sizeof(encodeStr));
    setlocale(LC_ALL, "Rus");
    call(enc);
    puts(END_INPUT_TEXT);
    while(getchar() != EXIT_SYMBOL)
    {
        putchar('\n');
        clear_buff();
        call(enc);
        puts(END_INPUT_TEXT);
    }
    MEM_FREE(enc);
    puts(END_TEXT);
    return 0;
}
void call(encodeStr * enc)
{
    fill_struct(enc);
    if(encode(enc))
        putchar('\n');
    return;
}

