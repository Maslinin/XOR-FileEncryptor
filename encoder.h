#ifndef _ENCODER_H
    #define _ENCODER_H
        #include <stdio.h>
        #include <stdlib.h>
        #include <errno.h>
        #include "cstmio.h"
        #define PATH_LENGTH 255
        #define XOR_TO_BYTE(X, MASK) ((X) ^ (MASK))
        #define FREE_MEM(X) free(X)

        typedef struct
        {
            char sourceFilePath[PATH_LENGTH];
            char targetFilePath[PATH_LENGTH];
            char mask;
            int srcFileDelFlag;
        } encodeStr;

        int encode(const encodeStr * restrict enc);
        encodeStr * fill_struct(void);
        void free_mem(const encodeStr *);
#endif // _ENCODER_H
