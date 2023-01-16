#include "dinput.h"
#include "macros.h"
#include "Customs/cstmio.h"
#include "Customs/cstmstr.h"

#include <stdio.h>
#include <string.h>
#include <stddef.h>

char* input_path(char* forPath, int pathLength, const char* fileMode)
{
    const char* textToDisplay = (strcmp(fileMode, "rb") == 0) ? INPUT_SOURCE_FILE_MESSAGE : INPUT_TARGET_FILE_MESSAGE;

    puts(textToDisplay);

    while (get_valid_path(forPath, pathLength, fileMode) == NULL)
    {
        perror(NULL);
        CLEAR_STDIN_AND_DOWN;
        puts(textToDisplay);
    }
    CLEAR_STDIN_AND_DOWN;

    return forPath;
}

int input_encrypt_mode(int* encMode)
{
    fputs(INPUT_ENCODER_MODE_MESSAGE, stdout);

    while (scanf("%d", encMode) == 0)
    {
        perror(NULL);
        CLEAR_STDIN_AND_DOWN;
        fputs(INPUT_ENCODER_MODE_MESSAGE, stdout);
    }
    CLEAR_STDIN_AND_DOWN;

    return *encMode;
}

int input_key_mode(int* keyMode)
{
    fputs(INPUT_KEY_MODE_MESSAGE, stdout);

    while (scanf("%d", keyMode) == 0)
    {
        perror(NULL);
        CLEAR_STDIN_AND_DOWN;
        fputs(INPUT_KEY_MODE_MESSAGE, stdout);
    }
    CLEAR_STDIN_AND_DOWN;

    return *keyMode;
}

char* input_key(char* forKey, int size)
{
    fputs(INPUT_KEY_MESSAGE, stdout);

    s_gets(forKey, size);
    remove_spaces(forKey);
    CLEAR_STDIN_AND_DOWN;

    return forKey;
}

int input_exit_symbol(int* exitCh)
{
    fputs(INPUT_EXIT_SYMBOL_MESSAGE, stdout);

    *exitCh = getchar();
    CLEAR_STDIN_AND_DOWN;

    return *exitCh;
}