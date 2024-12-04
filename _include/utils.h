#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>

#define REDIRECTION_NONE 0
#define REDIRECTION_INTO_FILE 1
#define REDIRECTION_FROM_FILE 2

#define MAX_INPUT_LENGTH 4096
#define MAX_ARGS_LENGTH 256
#define MAX_ARGS_COUNT 256
#define MAX_OUT_LENGTH 4096

void checkExit(char* commandBuffer, int ret);

int getArgsBuffer(char* commandBuffer, char** argsBuffer);

int doesContainRedirection(char** argsBuffer, int argc, int* redirectionPos);

void execCommand(char* commandBuffer, char** argsBuffer);
void execCommand2(char* commandBuffer, char** argsBuffer, int fd, int stdCpy);
void execCommand3(char* commandBuffer, char** argsBuffer, int fd, int stdCpy);

void removeRedirectionOut(int fd, int stdCpy);
void removeRedirectionIn(int fd, int stdCpy);