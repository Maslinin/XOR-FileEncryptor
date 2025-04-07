#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct
{
    int encryptMode;
    int generateKey;
    const char *key;
    const char *inputPath;
    const char *outputPath;
} CliArgs;

int parseArgs(int argc, char *argv[], CliArgs *outOptions);

#endif // OPTIONS_H