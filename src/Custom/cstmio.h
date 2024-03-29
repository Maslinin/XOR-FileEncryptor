#ifndef _CSTMIO_H
#define _CSTMIO_H

#include <stdio.h>

#define CLEAR_STDIN clear_buff(stdin)

char* s_gets(char* str, int len);
void clear_buff(FILE* stream);
char* get_valid_path(char* forPath, int keyLength, const char* file_mode);
int file_exists(const char* filePath);
int file_path_is_valid(const char* filePath);
int read_byte_from_file(FILE* fs, char* byte);
int write_byte_to_file(FILE* fs, const char* byte);

#endif // _CSTMIO_H
