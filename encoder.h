#ifndef _ENCODER_H
    #define _ENCODER_H
        #include <stdio.h>
        #include <errno.h>
        #include "cstmio.h"

        #define PATH_LENGTH 255
        #define FIRST_FILE_INPUT_TEXT "Введите путь к исходному (шифруемому) файлу: "
        #define SECOND_FILE_INPUT_TEXT "Введите путь записи зашифрованного файла: "
        #define MASK_INPUT_TEXT "Введите маску шифрования: "
        #define DEL_FILE_FLAG_INPUT_TEXT "Введите флаг на удаление исходного файла: "
        //#define FILE_OPEN_ERROR " - не удается найти или найти файл"
        #define FILE_DEL_ERROR "Не удается удалить файл"

        #define XOR_TO_BYTE(X, MASK) ((X) ^ (MASK))
        #define MEM_FREE(X) free(X)

        typedef struct
        {
            char sourceFilePath[PATH_LENGTH];
            char targetFilePath[PATH_LENGTH];
            char mask;
            int srcFileDelFlag;
        } encodeStr;

        int encode(const encodeStr * restrict enc);
        void fill_struct(encodeStr * restrict enc);
        void free_mem(const encodeStr *);
#endif // _ENCODER_H
