#include "args.h"
#include "argHandlers.h"
#include "../constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static void printUsage(const char *programName);
static int validateArgs(const CliArgs *opts, const char *programName);

const ArgOption argOptions[] = {
    {"-e", handleEncrypt},
    {"-d", handleDecrypt},
    {"-g", handleGenerateKey},
    {"-k", handleKey},
    {"-i", handleInput},
    {"-o", handleOutput},
    {NULL, NULL}
};

int parseArgs(int argc, char *argv[], CliArgs *opts)
{
    memset(opts, 0, sizeof(CliArgs));
    opts->encryptMode = -1;

    for (int i = 1; i < argc; ++i)
    {
        bool matched = false;
        for (const ArgOption *opt = argOptions; opt->flag; ++opt)
        {
            if (strcmp(argv[i], opt->flag) == 0)
            {
                if (opt->handler(argc, argv, &i, opts) != 0)
                {
                    printUsage(argv[0]);
                    return EXIT_FAILURE;
                }
                matched = true;
                break;
            }
        }

        if (!matched)
        {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            printUsage(argv[0]);
            return EXIT_FAILURE;
        }
    }

    return validateArgs(opts, argv[0]);
}

static int validateArgs(const CliArgs *opts, const char *programName)
{
    if (opts->encryptMode == -1 || !opts->inputPath || !opts->outputPath)
    {
        printUsage(programName);
        return EXIT_FAILURE;
    }

    if (opts->encryptMode)
    {
        if (opts->generateKey && opts->key)
        {
            fprintf(stderr, "Error: use either -k or -g, not both.\n");
            return EXIT_FAILURE;
        }
        else if (!opts->generateKey && !opts->key)
        {
            fprintf(stderr, "Error: encryption requires a key (-k) or generation (-g).\n");
            return EXIT_FAILURE;
        }
    }
    else
    {
        if (opts->generateKey)
        {
            fprintf(stderr, "Error: -g cannot be used in decryption mode.\n");
            return EXIT_FAILURE;
        }
        else if (!opts->key)
        {
            fprintf(stderr, "Error: decryption requires a key.\n");
            return EXIT_FAILURE;
        }
    }

    if (opts->key && strlen(opts->key) >= KEY_LENGTH)
    {
        fprintf(stderr, "Error: provided key is too long (max %d characters).\n", KEY_LENGTH - 1);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

static void printUsage(const char *programName)
{
    fprintf(stderr, "Usage: %s [-e | -d] [-k <key> | -g] -i <input_file> -o <output_file>\n", programName);
}