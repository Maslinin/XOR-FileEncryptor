#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "encoder.h"
#include "cstmio.h"

#define EXIT_SYMBOL 'q'
#define END_INPUT_TEXT "Encryption completed. Type\' q\' to close the program or another character to continue."
#define END_TEXT "The program has completed successfully"

void call(ENCODE_INFO * enc);

int main(void)
{
    ENCODE_INFO * enc = (ENCODE_INFO *)malloc(sizeof(ENCODE_INFO));

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
    //Enter encryption information:
    FillEncodeInfo(enc);
    putchar('\n');

    //If the function call succeeds and we encrypt, we output the key:
    if(Encode(enc) && enc->Mode)
        ShowKey(enc);

    return;
}
