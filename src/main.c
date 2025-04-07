#include "Encryptors/xorencryptor.h"
#include "Cli/options.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    CliOptions opts;
    if (parseArgs(argc, argv, &opts) != 0)
    {
        return EXIT_FAILURE;
    }

    if (opts.encryptMode == 1)
    {
        char key[KEY_LENGTH];

        if (opts.generateKey)
        {
            generateKey(key, KEY_LENGTH);
        }
        else
        {
            strncpy(key, opts.key, KEY_LENGTH);
            key[KEY_LENGTH - 1] = '\0';
        }

        printf("Encrypting file...\n");
        if (encryptFile(opts.inputPath, opts.outputPath, key) == EXIT_SUCCESS)
        {
            printf("The file was successfully encrypted. Your key:\n%s\n", key);
        }
        else
        {
            perror("Encryption failed. Please, try again");
            return EXIT_FAILURE;
        }
    }
    else
    {
        printf("Decrypting file...\n");
        if (decryptFile(opts.inputPath, opts.outputPath, opts.key) == EXIT_SUCCESS)
        {
            printf("The file was successfully decrypted.\n");
        }
        else
        {
            perror("Decryption failed. Please, try again");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
