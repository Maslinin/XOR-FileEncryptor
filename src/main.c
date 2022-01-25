#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Encoder/xorencoder.h"
#include "Custom/cstmio.h"

#define EXIT_SYMBOL 'q'
#define KEY_LENGTH BUFSIZ

//Function that receives the location of the file and checks whether the file or path exists
char *get_path(char* for_path, int path_length, const char* file_mode);
//Local function to enter encryption key
char *input_key(char *storage, int size);

int main(void)
{
    puts("Input the path to the source file: ");
    do
    {
        clean_stdin_buff();

    }
    while(getchar() != EXIT_SYMBOL);

    return 0;
}

char *get_path(char* for_path, int path_length, const char* file_mode)
{
    FILE * fs = NULL;

    //Enter the path and remove all spaces from the line (del_spaces, s_gets and clearbuff - custom functions from cstmio.h)
    del_spaces(s_gets(for_path, path_length));
    clean_stdin_buff();

    if(!(fs = fopen(for_path, file_mode)))
    {
        perror(for_path);
        return NULL;
    }
    fclose(fs);

    //If writing to a file is intended, delete the open (created) file
    if(strcmp(file_mode, "wb") == 0)
    {
        if(remove(for_path)) //if it is not possible to delete, we display an error
        {
            perror(NULL);
            return NULL;
        }
    }

    return for_path;
}

char *input_key(char *storage, int size)
{
    if(s_gets(storage, KEY_LENGTH) == NULL)
    {
        perror(NULL);
        return NULL;
    }
    del_spaces(storage);
    clean_stdin_buff();

    return storage;
}
