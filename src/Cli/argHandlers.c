#include "argHandlers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int parseFlag(int argc, char *argv[], int *i, int *target, int value);
static int parseString(int argc, char *argv[], int *i, const char **target);

int handleEncrypt(int argc, char *argv[], int *i, CliArgs *opts)
{
    if (opts->encryptMode != -1)
    {
        fprintf(stderr, "Error: multiple mode flags (-e / -d) specified.\n");
        return -1;
    }
    return parseFlag(argc, argv, i, &opts->encryptMode, 1);
}

int handleDecrypt(int argc, char *argv[], int *i, CliArgs *opts)
{
    if (opts->encryptMode != -1)
    {
        fprintf(stderr, "Error: multiple mode flags (-e / -d) specified.\n");
        return -1;
    }
    return parseFlag(argc, argv, i, &opts->encryptMode, 0);
}

int handleGenerateKey(int argc, char *argv[], int *i, CliArgs *opts)
{
    if (opts->generateKey != 0)
    {
        fprintf(stderr, "Error: duplicate -g flag.\n");
        return -1;
    }
    return parseFlag(argc, argv, i, &opts->generateKey, 1);
}

int handleKey(int argc, char *argv[], int *i, CliArgs *opts)
{
    if (opts->key)
    {
        fprintf(stderr, "Error: duplicate -k flag.\n");
        return -1;
    }
    return parseString(argc, argv, i, &opts->key);
}

int handleInput(int argc, char *argv[], int *i, CliArgs *opts)
{
    if (opts->inputPath)
    {
        fprintf(stderr, "Error: duplicate -i flag.\n");
        return -1;
    }
    return parseString(argc, argv, i, &opts->inputPath);
}

int handleOutput(int argc, char *argv[], int *i, CliArgs *opts)
{
    if (opts->outputPath)
    {
        fprintf(stderr, "Error: duplicate -o flag.\n");
        return -1;
    }
    return parseString(argc, argv, i, &opts->outputPath);
}

static int parseFlag(int argc, char *argv[], int *i, int *target, int value)
{
    (void)argc; (void)argv; (void)i;
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