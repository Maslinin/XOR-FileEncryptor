#include "encoder.h"

int encode(const encodeStr * restrict enc)
{
    FILE * fs, * ft;
    char ch;
    //Открытие файлов в бинарном режиме:
    if(!(fs = fopen(enc->sourceFilePath, "rb")) && !ferror(fs))
    {
        perror(enc->sourceFilePath);
        return 1;
    }
    if(!(ft = fopen(enc->targetFilePath, "wb")) && !ferror(fs))
    {
        fclose(fs);
        perror(enc->targetFilePath);
        return 1;
    }

    //Шифровка/расшифровка:
    while(!feof(fs))
    {
        fread(&ch, sizeof(ch), 1, fs);
        ch = XOR_TO_BYTE(ch, enc->mask);
        fwrite(&ch, sizeof(ch), 1, ft);
    }
    fclose(fs);
    fclose(ft);

    //Если стоит флаг удаления исходного файла
    if(enc->srcFileDelFlag)
        if(remove(enc->sourceFilePath))
            perror(FILE_DEL_ERROR);
    return 0;
}

void fill_struct(encodeStr * restrict enc)
{
    fputs(FIRST_FILE_INPUT_TEXT, stdout);
    while(!s_gets(enc->sourceFilePath, PATH_LENGTH) || !*enc->sourceFilePath)
    {
        clear_buff();
        fputs(FIRST_FILE_INPUT_TEXT, stdout);
    }
    clear_buff();

    fputs(SECOND_FILE_INPUT_TEXT, stdout);
    while(!s_gets(enc->targetFilePath, PATH_LENGTH) || !*enc->targetFilePath)
    {
        clear_buff();
        fputs(SECOND_FILE_INPUT_TEXT, stdout);
    }
    clear_buff();

    //Ввод маски
    fputs(MASK_INPUT_TEXT, stdout);
    while(!scanf("%c", &enc->mask))
    {
        clear_buff();
        putchar('\n');
        fputs(MASK_INPUT_TEXT, stdout);
    }
    clear_buff();

    fputs(DEL_FILE_FLAG_INPUT_TEXT, stdout);
    //Ввод флага на удаление
    while(!scanf("%d", &enc->srcFileDelFlag))
    {
        clear_buff();
        putchar('\n');
        fputs(DEL_FILE_FLAG_INPUT_TEXT, stdout);
    }
    clear_buff();
    return;
}
