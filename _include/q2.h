#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_COMMAND_LENGTH 4096
#define MAX_OUT_LENGTH 4096

ssize_t readCommand(void);