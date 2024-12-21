#pragma once

#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "checkManyThings.h"

#define MAX_INPUT_LENGTH 4096

ssize_t getCommandBuffer(char* commandBuffer);
int getArgsBuffer(char* commandBuffer, char** argsBuffer);

