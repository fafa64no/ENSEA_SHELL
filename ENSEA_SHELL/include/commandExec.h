#pragma once

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

#include "redirection.h"

#define MAX_OUT_LENGTH 4096

void execCommand(char* commandBuffer, char** argsBuffer, int fd, int stdCpy, int redirection);
void fatherExecCommand(int pid, int status, int fd, int stdCpy, int redirection);
void childExecCommand(char* commandBuffer, char** argsBuffer);