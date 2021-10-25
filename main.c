#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include "encoder.h"
#include "cstmio.h"

#define EXIT_SYMBOL 'q'
#define END_INPUT_TEXT "���������� ���������. ������� \'q\', ��� �� ������� ���������, ��� ������ ������, ��� �� ����������."
#define END_TEXT "��������� ������� ��������� ���� ����������"

void call(ENCODE_INFO * enc);
int main(void)
{
    ENCODE_INFO * enc = (ENCODE_INFO *)malloc(sizeof(ENCODE_INFO));
    setlocale(LC_ALL, "Rus");

    //���� ������ ������ ���������:
    call(enc);
    puts(END_INPUT_TEXT);
    while(getchar() != EXIT_SYMBOL)
    {
        clear_buff();
        call(enc);
        puts(END_INPUT_TEXT);
    }
    free(enc);
    puts(END_TEXT);

    return 0;
}
void call(ENCODE_INFO * enc)
{
    FillEncodeInfo(enc);
    putchar('\n');

    //���� ����� ������� ������� � �� ���������, ������� ����
    if(Encode(enc) && enc->Mode)
    {
        ShowKey(enc);
    }

    return;
}
