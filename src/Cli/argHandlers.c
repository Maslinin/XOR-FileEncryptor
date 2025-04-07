#include "argHandlers.h"
#include <string.h>
#include <stdlib.h>

static int parseFlag(int argc, char *argv[], int *i, int *target, int value);
static int parseString(int argc, char *argv[], int *i, const char **target);

int handleEncrypt(int argc, char *argv[], int *i, CliArgs *opts)
{
    return parseFlag(argc, argv, i, &opts->encryptMode, 1);
}

int handleDecrypt(int argc, char *argv[], int *i, CliArgs *opts)
{
    return parseFlag(argc, argv, i, &opts->encryptMode, 0);
}

int handleGenerateKey(int argc, char *argv[], int *i, CliArgs *opts)
{
    return parseFlag(argc, argv, i, &opts->generateKey, 1);
}

int handleKey(int argc, char *argv[], int *i, CliArgs *opts)
{
    return parseString(argc, argv, i, &opts->key);
}

int handleInput(int argc, char *argv[], int *i, CliArgs *opts)
{
    return parseString(argc, argv, i, &opts->inputPath);
}

int handleOutput(int argc, char *argv[], int *i, CliArgs *opts)
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