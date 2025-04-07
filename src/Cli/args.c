#include "args.h"
#include "../constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void printUsage(const char *programName);
static int handleEncrypt(int argc, char *argv[], int *i, CliArgs *opts);
static int handleDecrypt(int argc, char *argv[], int *i, CliArgs *opts);
static int handleGenerateKey(int argc, char *argv[], int *i, CliArgs *opts);
static int handleKey(int argc, char *argv[], int *i, CliArgs *opts);
static int handleInput(int argc, char *argv[], int *i, CliArgs *opts);
static int handleOutput(int argc, char *argv[], int *i, CliArgs *opts);
static int parseFlag(int argc, char *argv[], int *i, int *target, int value);
static int parseString(int argc, char *argv[], int *i, const char **target);
static int validateCliArgs(const CliArgs *opts, const char *programName);

typedef int (*ArgHandler)(int argc, char *argv[], int *i, CliArgs *opts);

typedef struct
{
    const char *flag;
    ArgHandler handler;
} ArgOption;

static ArgOption argCliArgs[] = {
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
        int matched = 0;
        for (ArgOption *opt = argCliArgs; opt->flag; ++opt)
        {
            if (strcmp(argv[i], opt->flag) == 0)
            {
                if (opt->handler(argc, argv, &i, opts) != 0)
                {
                    printUsage(argv[0]);
                    return EXIT_FAILURE;
                }
                matched = 1;
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

    return validateCliArgs(opts, argv[0]);
}

void printUsage(const char *programName)
{
    fprintf(stderr, "Usage: %s [-e | -d] [-k <key> | -g] -i <input_file> -o <output_file>\n", programName);
}

static int handleEncrypt(int argc, char *argv[], int *i, CliArgs *opts)
{
    return parseFlag(argc, argv, i, &opts->encryptMode, 1);
}

static int handleDecrypt(int argc, char *argv[], int *i, CliArgs *opts)
{
    return parseFlag(argc, argv, i, &opts->encryptMode, 0);
}

static int handleGenerateKey(int argc, char *argv[], int *i, CliArgs *opts)
{
    return parseFlag(argc, argv, i, &opts->generateKey, 1);
}

static int handleKey(int argc, char *argv[], int *i, CliArgs *opts)
{
    return parseString(argc, argv, i, &opts->key);
}

static int handleInput(int argc, char *argv[], int *i, CliArgs *opts)
{
    return parseString(argc, argv, i, &opts->inputPath);
}

static int handleOutput(int argc, char *argv[], int *i, CliArgs *opts)
{
    return parseString(argc, argv, i, &opts->outputPath);
}

static int parseFlag(int argc, char *argv[], int *i, int *target, int value)
{
    (void)argc; (void)argv;
    *target = value;
    return 0;
}

static int parseString(int argc, char *argv[], int *i, const char **target)
{
    if (*i + 1 >= argc)
        return -1;
    *target = argv[++(*i)];
    return 0;
}

static int validateCliArgs(const CliArgs *opts, const char *programName)
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
        if(opts->generateKey)
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
