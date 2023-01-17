#include <stdio.h>
#include <stdlib.h>

#include "dinput.h"
#include "macros.h"
#include "Custom/cstmio.h"
#include "Custom/cstmstr.h"
#include "Encryptors/xorencryptor.h"

int main(void)
{
    int encMode = 0, keyMode = 0, exitCh = 0;
    char s_path[PATH_LENGTH], t_path[PATH_LENGTH];
    char key[KEY_LENGTH];

    do
    {
        input_path(s_path, PATH_LENGTH, "rb");
        input_path(t_path, PATH_LENGTH, "wb");
        input_encrypt_mode(&encMode);

        if (encMode)
        {
            input_key_mode(&keyMode);
        }
        (!encMode || keyMode) ? input_key(key, KEY_LENGTH) : generate_key(key, KEY_LENGTH);

        encMode ? puts("Encrypting file...") : puts("Decrypting file...");
        if (encMode)
        {
            if (encrypt_file(s_path, t_path, key) == EXIT_SUCCESS)
                printf("The file was successfully encrypted. Your key:\n%s\n", key);
            else
                perror("Encryption failed. Please, try again");
        }
        else
        {
            if (decrypt_file(s_path, t_path, key) == EXIT_SUCCESS)
                puts("The file was successfully decrypted.");
            else
                perror("Decryption failed. Please, try again");
        }
        DOWN;

        printf("Input \'%c\' to exit or any other key if you want to continue\n", EXIT_SYMBOL);
        input_exit_symbol(&exitCh);
    } 
    while (exitCh != EXIT_SYMBOL);

    return 0;
}