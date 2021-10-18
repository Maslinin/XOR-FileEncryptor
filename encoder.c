#include "encoder.h"
#include <string.h>

#define FIRST_FILE_INPUT_TEXT "Введите путь к исходному (шифруемому) файлу: "
#define SECOND_FILE_INPUT_TEXT "Введите путь записи зашифрованного файла: "
#define MASK_INPUT_TEXT "Введите ключ(маску) шифрования: "
#define DEL_FILE_FLAG_INPUT_TEXT "Введите флаг на удаление исходного файла(0: оставить, 1: удалить): "
#define ENCODER_MODE_INPUT_TEXT "Введите режим работы программы(1: шифровать, 0: дешифровать): "
#define FILE_DEL_ERROR "Не удается удалить файл"

//Локальная функция, получающая местонахождение файла и проверяющая его существование/существование пути
static char* getpath(char* out_str, char * out_message, char* file_mode);
//Локальная функция, шифрующая указанный символ каждым символом переданного ей ключа:
static char charencrypt(char ch, const char* key, bool mode);

//Шифрование файла(mode true - шифрование, bool - дешифрование):
bool Encode(const ENCODE_INFO * restrict enc)
{
    FILE * fs, * ft;
    char ch;
    //Открытие файлов в бинарном режиме:
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

    //Шифровка/расшифровка:
    while(!feof(fs))
    {
        fread(&ch, sizeof(ch), 1, fs);
        ch = charencrypt(ch, enc->Key, enc->Mode);
        fwrite(&ch, sizeof(ch), 1, ft);
    }
    fclose(fs);
    fclose(ft);

    //Если стоит флаг удаления исходного файла
    if(enc->SourceFileDelFlag)
        if(remove(enc->SourceFilePath))
            perror(FILE_DEL_ERROR);
    return true;
}

//Функция для заполнения полей структуры:
void FillEncodeInfo(ENCODE_INFO * restrict enc)
{
    int mode;

    //Получение пути исходного файла:
    getpath(enc->SourceFilePath, FIRST_FILE_INPUT_TEXT, "rb");
    //Получение пути нового файла:
    getpath(enc->TargetFilePath, SECOND_FILE_INPUT_TEXT, "wb");

    //Ввод ключа(маски) шифрования:
    fputs(MASK_INPUT_TEXT, stdout);
    if(s_gets(enc->Key, MAX_KEY_LENGTH) == NULL)
    {
        perror(NULL);
        exit(EXIT_FAILURE);
    }
    clear_buff();

    //Ввод флага на удаление исходного файла:
    fputs(DEL_FILE_FLAG_INPUT_TEXT, stdout);
    while(!scanf("%d", &enc->SourceFileDelFlag))
    {
        clear_buff();
        putchar('\n');
        fputs(DEL_FILE_FLAG_INPUT_TEXT, stdout);
    }
    clear_buff();

    //Ввод режима работы программы:
    fputs(ENCODER_MODE_INPUT_TEXT, stdout);
    while(!scanf("%d", &mode))
    {
        clear_buff();
        putchar('\n');
        fputs(ENCODER_MODE_INPUT_TEXT, stdout);
    }
    clear_buff();
    enc->Mode = mode;

    return;
}

//Функция отображения ключа(маски) шифрования:
void ShowKey(ENCODE_INFO * restrict enc)
{
    fputs("Ваш ключ(маска) шифрования: ", stdout);
    puts(enc->Key);
    return;
}

//Локальная функция для ввода пути файла:
static char* getpath(char* out_str, char * out_message, char* file_mode)
{
    FILE * fs = NULL;
    do
    {
        fputs(out_message, stdout);
        del_spaces(s_gets(out_str, PATH_LENGTH));
        clear_buff();
        if(!(fs = fopen(out_str, file_mode)))
            perror(out_str);
    }
    while(!fs);
    fclose(fs);
    if(strcmp(file_mode, "wb") == 0)
        if(remove(out_str))
            perror(FILE_DEL_ERROR);
    return out_str;
}

//true - шифрование, false - дешифрование
//Локальная функция, шифрующая указанный символ каждым символом переданного ключа:
static char charencrypt(char ch, const char* key, bool mode)
{
    int i;
    if(mode)
    {
        for(i = 0; i < strlen(key); ++i)
            ch ^= key[i];
    }
    else
    {
        for(i = strlen(key) - 1; i >= 0; --i)
            ch ^= key[i];
    }

    return ch;
}
