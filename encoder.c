#include "encoder.h"
#include <string.h>
#include <time.h>

#define FIRST_FILE_INPUT_TEXT "Enter the path to the source (encrypted) file: "
#define SECOND_FILE_INPUT_TEXT "Enter the write path of the encrypted (new) file: "
#define KEY_MODE_INPUT_TEXT "0 - enter your key, 1 - generate key\nEnter: "
#define MASK_INPUT_TEXT "Enter the encryption key (mask):"
#define DEL_FILE_FLAG_INPUT_TEXT "Enter the flag to delete the source file (0: do not touch, 1: delete):"
#define ENCODER_MODE_INPUT_TEXT "Enter the program mode (1: encrypt, 0: decrypt): "
#define FILE_DEL_ERROR "Unable to delete file"

//Local function that receives the location of the file and checks whether the file or path exists
static char * getpath(char* out_str, char* file_mode, char * out_message);
//A local function that encrypts the specified character with each character of the key passed to it:
static char charencrypt(char ch, const char* key, bool mode);
//Local function to enter encryption key:
static char * inputkey(char * restrict storage, int size, char * out_message);
//Local function generating encryption key:
static char * generatekey(char * restrict storage, int size);

//File encryption (mode true - encryption, bool - decryption):
bool Encode(const ENCODE_INFO * restrict enc)
{
    FILE * fs, * ft;
    char ch;

    //Open files in binary mode:
    if(!(fs = fopen(enc->SourceFilePath, "rb")) && !ferror(fs))
    {
        perror(enc->SourceFilePath);
        return false;
    }
    if(!(ft = fopen(enc->TargetFilePath, "wb")) && !ferror(fs))
    {
        fclose(fs);
        perror(enc->TargetFilePath);
        return false;
    }

    //Encryption/decryption:
    while(!feof(fs))
    {
        fread(&ch, sizeof(ch), 1, fs);
        ch = charencrypt(ch, enc->Key, enc->Mode);
        fwrite(&ch, sizeof(ch), 1, ft);
    }
    fclose(fs);
    fclose(ft);

    //If the delete source file flag is
    if(enc->SourceFileDelFlag)
        if(remove(enc->SourceFilePath))
            perror(FILE_DEL_ERROR);
    return true;
}

//Function for filling structure fields:
void FillEncodeInfo(ENCODE_INFO * restrict enc)
{
    int encodeMode, keyMode;

    //Retrieving source file path:
    getpath(enc->SourceFilePath, "rb", FIRST_FILE_INPUT_TEXT);
    //Get new file path:
    getpath(enc->TargetFilePath, "wb", SECOND_FILE_INPUT_TEXT);

    //Entry of program operation mode:
    fputs(ENCODER_MODE_INPUT_TEXT, stdout);
    while(!scanf("%d", &encodeMode))
    {
        clear_buff();
        putchar('\n');
        fputs(ENCODER_MODE_INPUT_TEXT, stdout);
    }
    clear_buff();
    enc->Mode = encodeMode;

    if(enc->Mode)
    {
        fputs(KEY_MODE_INPUT_TEXT, stdout);
        while(!scanf("%d", &keyMode))
        {
            clear_buff();
            putchar('\n');
            fputs(KEY_MODE_INPUT_TEXT, stdout);
        }
        clear_buff();

        if(!keyMode)
            inputkey(enc->Key, KEY_LENGTH, MASK_INPUT_TEXT);
        else
            generatekey(enc->Key, KEY_LENGTH);
    }
    else
    {
        inputkey(enc->Key, KEY_LENGTH, MASK_INPUT_TEXT);
    }

    //Enter flag to delete source file:
    fputs(DEL_FILE_FLAG_INPUT_TEXT, stdout);
    while(!scanf("%d", &enc->SourceFileDelFlag))
    {
        clear_buff();
        putchar('\n');
        fputs(DEL_FILE_FLAG_INPUT_TEXT, stdout);
    }
    clear_buff();

    return;
}

//Function to display encryption key (mask):
void ShowKey(ENCODE_INFO * restrict enc)
{
    fputs("Ваш ключ(маска) шифрования: ", stdout);
    puts(enc->Key);

    return;
}

//Local function to enter file path:
static char * getpath(char* out_str, char* file_mode, char * out_message)
{
    FILE * fs = NULL;
    do
    {
        fputs(out_message, stdout);
        //Enter the path and remove all spaces from the line (del_spaces, s_gets and clearbuff - custom functions from cstmio.h)
        del_spaces(s_gets(out_str, PATH_LENGTH));
        clear_buff();
        if(!(fs = fopen(out_str, file_mode)))
            perror(out_str);
    }
    while(!fs);
    fclose(fs);

    //If writing to a file is intended, delete the open (created) file
    if(strcmp(file_mode, "wb") == 0)
        if(remove(out_str)) //if it is not possible to delete, we display an error
            perror(FILE_DEL_ERROR);
    return out_str;
}

//true - encode, false - decode
//Local function encrypting the specified character with each character of the transmitted key:
static char charencrypt(char ch, const char* key, bool mode)
{
    int i;
    if(mode) //if we encrypt
        for(i = 0; i < strlen(key); ++i)
            ch ^= key[i];
    else //if we decrypt
        for(i = strlen(key) - 1; i >= 0; --i)
            ch ^= key[i];

    return ch;
}

static char * inputkey(char * restrict storage, int size, char * out_message)
{
    fputs(out_message, stdout);
    if(s_gets(storage, KEY_LENGTH) == NULL)
    {
        perror(NULL);
        exit(EXIT_FAILURE);
    }
    del_spaces(storage);
    clear_buff();

    return storage;
}

static char * generatekey(char * restrict storage, int size)
{
    int i;
    //Set the grain of the random number generator so that each time the start is different key
    srand(time(NULL));
    for(i = 0; i < size; ++i)
        storage[i] = rand()%95 + 33; //character range in ASCII
    del_spaces(storage);
    storage[i - 1] = '\0';

    return storage;
}
