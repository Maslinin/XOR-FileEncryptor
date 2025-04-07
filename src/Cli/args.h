#ifndef ARGS_H
#define ARGS_H

typedef struct
{
    int encryptMode;
    int generateKey;
    const char *key;
    const char *inputPath;
    const char *outputPath;
} CliArgs;

int parseArgs(int argc, char *argv[], CliArgs *outOptions);

#endif // ARGS_H