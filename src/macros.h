#ifndef _MACROS_H
#define _MACROS_H

#include "Custom/cstmio.h"

#include <limits.h>

#define DOWN putchar('\n')
#define CLEAR_STDIN_AND_DOWN CLEAR_STDIN; DOWN

#define EXIT_SYMBOL 'q'
#define KEY_LENGTH BUFSIZ - 1

#ifdef PATH_MAX
#define PATH_LENGTH PATH_MAX
#else
#if 255 > BUFSIZ - 1
#define PATH_LENGTH BUFSIZ - 1
#else
#define PATH_LENGTH 255
#endif
#endif

#define INPUT_SOURCE_FILE_MESSAGE "Input the path to the source file: "
#define INPUT_TARGET_FILE_MESSAGE "Input the path to save the encrypted file: "
#define INPUT_ENCODER_MODE_MESSAGE "Input the program mode\n1. 1 to encrypt\n2. 0 to decrypt\nInput: "
#define INPUT_KEY_MODE_MESSAGE "Input the key mode.\n1. 1 to input your key\n2. 0 to generate key\nInput: "
#define INPUT_KEY_MESSAGE "Input the encryption key:\n"
#define INPUT_EXIT_SYMBOL_MESSAGE "Input a symbol: "

#endif // _MACROS_H
