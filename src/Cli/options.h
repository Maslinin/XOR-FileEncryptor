#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct
{
    int encryptMode;
    int generateKey;
    const char *key;
    const char *inputPath;
    const char *outputPath;
} CliOptions;

int parseArgs(int argc, char *argv[], CliOptions *outOptions);

#endif // OPTIONS_H