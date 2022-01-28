#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "Encoder/xorencoder.h"
#include "Custom/cstmio.h"
#include "Custom/cstmstr.h"

#define EXIT_SYMBOL 'q'
#define KEY_LENGTH BUFSIZ
#define PATH_LENGTH PATH_MAX

#define INPUT_SOURCE_FILE_MESSAGE "Input the path to the source file:"
#define INPUT_TARGET_FILE_MESSAGE "Input the path to save the encrypted file:"
#define INPUT_KEY_MODE_MESSAGE "Input the key mode (0 to generate key, 1 to input your key):"
#define INPUT_ENCODER_MODE_MESSAGE "Input the program mode (1 to encrypt, 0 to decrypt):"
#define INPUT_MASK_MESSAGE "Input the encryption key (mask):"
#define INPUT_DEL_FILE_FLAG_MESSAGE "Input the flag to delete the source file (0 to do not touch, 1 to delete):"

//Function that receives the location of the file and checks whether the file or path exists
char *get_path(char *for_path, int path_length, const char *file_mode);
//Function to input encryption key
char *input_key(char *storage, int size);

int main(void)
{
    char s_path[PATH_LENGTH], t_path[PATH_LENGTH], key[KEY_LENGTH];
    int encMode = 0, keyMode = 0, srcFileDelFlag;

    do
    {
        puts(INPUT_SOURCE_FILE_MESSAGE);
        while(!(get_path(s_path, PATH_LENGTH, "rb")))
        {
            perror(NULL);
            putchar('\n');
            puts(INPUT_SOURCE_FILE_MESSAGE);
        }
        putchar('\n');
        clean_stdin_buff();

        puts(INPUT_TARGET_FILE_MESSAGE);
        while(!(get_path(t_path, PATH_LENGTH, "wb")))
        {
            perror(NULL);
            putchar('\n');
            puts(INPUT_TARGET_FILE_MESSAGE);
        }
        putchar('\n');
        clean_stdin_buff();

        fputs(INPUT_KEY_MODE_MESSAGE, stdout);
        while(!scanf("%d", &keyMode))
        {
            clean_stdin_buff();
            putchar('\n');
            fputs(INPUT_KEY_MODE_MESSAGE, stdout);
        }
        clean_stdin_buff();
        if(keyMode)
        {
            puts(INPUT_MASK_MESSAGE);
            while(!input_key(key, KEY_LENGTH))
            {
                clean_stdin_buff();
                perror(NULL);
                putchar('\n');
                puts(INPUT_MASK_MESSAGE);
            }
        }
        else
        {
            generate_key(key, KEY_LENGTH);
        }
        clean_stdin_buff();

        fputs(INPUT_ENCODER_MODE_MESSAGE, stdout);
        while(!scanf("%d", &encMode))
        {
            clean_stdin_buff();
            putchar('\n');
            fputs(INPUT_ENCODER_MODE_MESSAGE, stdout);
        }
        putchar('\n');
        clean_stdin_buff();

        fputs(INPUT_DEL_FILE_FLAG_MESSAGE, stdout);
        while(!scanf("%d", &srcFileDelFlag))
        {
            clean_stdin_buff();
            putchar('\n');
            fputs(INPUT_DEL_FILE_FLAG_MESSAGE, stdout);
        }
        putchar('\n');
        clean_stdin_buff();

        puts("Encrypting file...");
        if(file_encode(s_path, t_path, key, encMode, srcFileDelFlag))
        {
            perror("Encode is fail. Please, try again");
            putchar('\n');
        }
        else
        {
            puts("Your key:");
            puts(key);
            putchar('\n');
        }

        printf("Input \'%c\' to exit or any other key if you want to continue", EXIT_SYMBOL);
        clean_stdin_buff();
    }
    while(getchar() != EXIT_SYMBOL);

    return 0;
}

char *get_path(char* for_path, int path_length, const char* file_mode)
{
    FILE *fs = NULL;

    //Enter the path and remove all spaces from the line (del_spaces, s_gets and clearbuff - custom functions from cstmio.h)
    if(del_spaces(s_gets(for_path, path_length)))
    {
        return NULL;
    }

    if(!(fs = fopen(for_path, file_mode)))
    {
        return NULL;
    }
    fclose(fs);

    //If writing to a file is intended, delete the open (created) file
    if(strcmp(file_mode, "wb") == 0)
    {
        if(remove(for_path)) //if it is not possible to delete, we display an error
        {
            return NULL;
        }
    }

    return for_path;
}

char *input_key(char *for_key, int size)
{
    if(s_gets(for_key, KEY_LENGTH) == NULL)
    {
        return NULL;
    }
    del_spaces(for_key);

    return for_key;
}
