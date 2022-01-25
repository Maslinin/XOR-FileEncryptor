#ifndef _CSTMIO_H
#define _CSTMIO_H

//stdin input buffer cleaning function
void clean_stdin_buff(void);
//Line entry function. Replaces the new line character with a null character.
char *s_gets(char *str, int len);

#endif // _CSTMIO_H
