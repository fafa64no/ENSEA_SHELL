#include "checkManyThings.h"

static const char exitMsg1[] = "\nBye bye ...\n$\n";
static const char exitMsg2[] = "Bye bye ...\n$\n";

static const char tooManyArgs[] = "ENSEA_SHELL ERROR : too many arguments.\n";
static const char tooBigArgs[] = "ENSEA_SHELL ERROR : too many arguments.\n";

void checkExit(char* commandBuffer, int ret) {
    if(ret == 0) {
        write(STDOUT_FILENO,exitMsg1, strlen(exitMsg1));
        exit(EXIT_SUCCESS);
    }
    if(!strncmp(commandBuffer, "exit", 4)){
        write(STDOUT_FILENO,exitMsg2, strlen(exitMsg2));
        exit(EXIT_SUCCESS);
    }
}

void checkHowManyArgs(int argc) {
    if (argc < MAX_ARGS_COUNT) return;
    write(STDOUT_FILENO,tooManyArgs,strlen(tooManyArgs));
    exit(EXIT_FAILURE);
}

void checkArgsSize(int argSize) {
    if (argSize < MAX_ARGS_LENGTH) return;
    write(STDOUT_FILENO,tooBigArgs,strlen(tooBigArgs));
    exit(EXIT_FAILURE);
}