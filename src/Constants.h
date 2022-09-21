#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <limits.h>

#define EXIT_SYMBOL 'q'

#ifdef PATH_MAX
#define PATH_LENGTH PATH_MAX
#else
#define PATH_LENGTH 256
#endif

#define INPUT_SOURCE_FILE_MESSAGE "Input the path to the source file: "
#define INPUT_TARGET_FILE_MESSAGE "Input the path to save the encrypted file: "
#define INPUT_KEY_MODE_MESSAGE "Input the key mode.\n1. 0 to input your key\n2. 1 to generate key\nInput: "
#define INPUT_MASK_MESSAGE "Input the encryption key:"
#define INPUT_ENCODER_MODE_MESSAGE "Input the program mode\n1. 1 to encrypt\n2. 0 to decrypt\nInput:"

#endif // _CONSTANTS_H
