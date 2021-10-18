#ifndef _ENCODER_H
    #define _ENCODER_H
        #include <stdio.h>
        #include <stdlib.h>
        #include <errno.h>
        #include <stdbool.h>
        #include "cstmio.h"

        #define PATH_LENGTH 255
        #define MAX_KEY_LENGTH BUFSIZ
        #define XOR_TO_BYTE(X, MASK) ((X) ^ (MASK))
        #define ENCODE_INFO_FREE(X) free(X)

        typedef struct
        {
            char SourceFilePath[PATH_LENGTH];
            char TargetFilePath[PATH_LENGTH];
            char Key[MAX_KEY_LENGTH];
            int SourceFileDelFlag;
            bool Mode;
        } ENCODE_INFO;

        bool Encode(const ENCODE_INFO * restrict enc);
        void ShowKey(ENCODE_INFO * restrict enc);
        void FillEncodeInfo(ENCODE_INFO * restrict enc);
#endif // _ENCODER_H
