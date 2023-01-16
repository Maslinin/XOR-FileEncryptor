#ifndef _DINPUT_H
#define _DINPUT_H

char* input_path(char* forPath, int pathLength, const char* fileMode);
int input_encrypt_mode(int* encMode);
int input_key_mode(int* keyMode);
char* input_key(char* forKey, int size);
int input_exit_symbol(int* ch);

#endif // _DINPUT_H