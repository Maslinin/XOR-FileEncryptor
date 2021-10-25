#include "encoder.h"
#include <string.h>
#include <time.h>

#define FIRST_FILE_INPUT_TEXT "Введите путь к исходному (шифруемому) файлу: "
#define SECOND_FILE_INPUT_TEXT "Введите путь записи шифрованного (нового) файла: "
#define KEY_MODE_INPUT_TEXT "0 - ввести свой ключ, 1 - генерировать ключ\nВвод: "
#define MASK_INPUT_TEXT "Введите ключ(маску) шифрования: "
#define DEL_FILE_FLAG_INPUT_TEXT "Введите флаг на удаление исходного файла(0: оставить, 1: удалить): "
#define ENCODER_MODE_INPUT_TEXT "Введите режим работы программы(1: шифровать, 0: дешифровать): "
#define FILE_DEL_ERROR "Не удается удалить файл"

//Локальная функция, получающая местонахождение файла и проверяющая его существование/существование пути
static char * getpath(char* out_str, char* file_mode, char * out_message);
//Локальная функция, шифрующая указанный символ каждым символом переданного ей ключа:
static char charencrypt(char ch, const char* key, bool mode);
//Локальная функция для ввода ключа шифрования:
static char * inputkey(char * restrict storage, int size, char * out_message);
//Локальная функция, генерирующая ключ шифрования:
static char * generatekey(char * restrict storage, int size);

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
    int encodeMode, keyMode;

    //Получение пути исходного файла:
    getpath(enc->SourceFilePath, "rb", FIRST_FILE_INPUT_TEXT);
    //Получение пути нового файла:
    getpath(enc->TargetFilePath, "wb", SECOND_FILE_INPUT_TEXT);

    //Ввод режима работы программы:
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

    //Ввод флага на удаление исходного файла:
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

//Функция для отображения ключа(маски) шифрования:
void ShowKey(ENCODE_INFO * restrict enc)
{
    fputs("Ваш ключ(маска) шифрования: ", stdout);
    puts(enc->Key);
    return;
}

//Локальная функция для ввода пути файла:
static char * getpath(char* out_str, char* file_mode, char * out_message)
{
    FILE * fs = NULL;
    do
    {
        fputs(out_message, stdout);
        //Вводим путь и убираем из строки все пробелы(del_spaces, s_gets и clearbuff кастомные функции из cstmio.h)
        del_spaces(s_gets(out_str, PATH_LENGTH));
        clear_buff();
        if(!(fs = fopen(out_str, file_mode)))
            perror(out_str);
    }
    while(!fs);
    //закрываем открытый файл для дальнейшего использования:
    fclose(fs);

    //Если подразумевается запись в файл, удаляем открытый(созданный) файл
    if(strcmp(file_mode, "wb") == 0)
        if(remove(out_str)) //если удалить не удается, выводим ошибку
            perror(FILE_DEL_ERROR);
    return out_str;
}

//true - шифрование, false - дешифрование
//Локальная функция, шифрующая указанный символ каждым символом переданного ключа:
static char charencrypt(char ch, const char* key, bool mode)
{
    int i;
    if(mode) //если шифруем
        for(i = 0; i < strlen(key); ++i)
            ch ^= key[i];
    else //если расшифровываем
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
    //Задаем зерно генератора случайных чисел, что бы каждый раз при запуске был разный ключ
    srand(time(NULL));
    for(i = 0; i < size; ++i)
        storage[i] = rand()%95 + 33; //диапазон символов в ASCII
    del_spaces(storage);
    storage[i - 1] = '\0';

    return storage;
}
