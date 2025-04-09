#include "argHandlers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int parseFlag(int argc, char *argv[], int *i, int *target, int value);
static int parseString(int argc, char *argv[], int *i, const char **target);

static int validateArgLength(const char *key, size_t length);

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

    const char *arg;
    if (parseString(argc, argv, i, &arg) != 0)
    {
        fprintf(stderr, "Error: -k requires a value.\n");
        return -1;
    }
    if (validateArgLength(arg, KEY_LENGTH) != 0)
    {
        fprintf(stderr, "Error: key is too long (max %d characters).\n", KEY_LENGTH - 1);
        return -1;
    }

    strncpy(opts->key, arg, KEY_LENGTH);

    return 0;
}

int handleInput(int argc, char *argv[], int *i, CliArgs *opts)
{
    if (opts->inputPath)
    {
        fprintf(stderr, "Error: duplicate -i flag.\n");
        return -1;
    }

    const char *arg;
    if (parseString(argc, argv, i, &arg) != 0)
    {
        fprintf(stderr, "Error: -i requires a value.\n");
        return -1;
    }
    if (validateArgLength(arg, PATH_LENGTH) != 0)
    {
        fprintf(stderr, "Error: the input path is too long (max %d characters).\n", KEY_LENGTH - 1);
        return -1;
    }
    
    strncpy(opts->inputPath, arg, PATH_LENGTH);

    return 0;
}

int handleOutput(int argc, char *argv[], int *i, CliArgs *opts)
{
    if (opts->outputPath)
    {
        fprintf(stderr, "Error: duplicate -o flag.\n");
        return -1;
    }

    const char *arg;
    if (parseString(argc, argv, i, &arg) != 0)
    {
        fprintf(stderr, "Error: -o requires a value.\n");
        return -1;
    }
    if (validateArgLength(arg, PATH_LENGTH) != 0)
    {
        fprintf(stderr, "Error: the output path is too long (max %d characters).\n", KEY_LENGTH - 1);
        return -1;
    }

    strncpy(opts->outputPath, arg, PATH_LENGTH);
    
    return 0;
}

static int parseFlag(int argc, char *argv[], int *i, int *target, int value)
{
    (void)argc; (void)argv; (void)i;
    *target = value;
    return 0;
}

static int parseString(int argc, char *argv[], int *i, const char **arg)
{
    if (*i + 1 >= argc)
    {
        return -1;
    }
    *arg = argv[++(*i)];
    return 0;
}

static int validateArgLength(const char *key, size_t length)
{
    if (strlen(key) >= length)
    {
        return -1;
    }
    return 0;
}
