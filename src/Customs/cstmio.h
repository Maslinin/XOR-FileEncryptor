#ifndef _CSTMIO_H
#define _CSTMIO_H

#include <stdio.h>

char* s_gets(char* str, int len);
void clear_stdin_buff(void);
void clear_buff(FILE* stream);
int file_exists_check(const char* filePath);
int check_file_path_availability(const char* filePath);

#endif // _CSTMIO_H
