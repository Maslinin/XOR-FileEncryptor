#include "encoder.h"

int encode(const encodeStr * restrict enc)
{
    FILE * fs, * ft;
    char ch;
    //Открытие файлов в бинарном режиме:
    if(!(fs = fopen(enc->sourceFilePath, "rb")) && !ferror(fs))
    {
        perror(enc->sourceFilePath);
        return EXIT_FAILURE;
    }
    if(!(ft = fopen(enc->targetFilePath, "wb")) && !ferror(fs))
    {
        perror(enc->targetFilePath);
        return EXIT_FAILURE;
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
        {
            perror("Не удается удалить файл");
        }
    return 0;
}

encodeStr * fill_struct(void)
{
    encodeStr * strct = malloc(sizeof(encodeStr));

    fputs("Введите путь к исходному (шифруемому) файлу: ", stdout);
    s_gets(strct->sourceFilePath, PATH_LENGTH);

    fputs("Введите путь записи зашифрованного файла: ", stdout);
    s_gets(strct->targetFilePath, PATH_LENGTH);

    //Ввод маски
    fputs("Введите маску шифрования: ", stdout);
    while(!scanf("%c", &strct->mask))
    {
        clear_buff();
        putchar('\n');
        fputs("Введите маску шифрования: ", stdout);
    }
    clear_buff();

    fputs("Введите флаг на удаление исходного файла: ", stdout);
    //Ввод флага на удаление
    while(!scanf("%d", &strct->srcFileDelFlag))
    {
        clear_buff();
        putchar('\n');
        fputs("Введите флаг на удаление исходного файла: ", stdout);
    }
    clear_buff();
    return strct;
}
