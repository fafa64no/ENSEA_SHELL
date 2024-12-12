#pragma once

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS_LENGTH 256
#define MAX_ARGS_COUNT 64

void checkExit(char* commandBuffer, int ret);

void checkHowManyArgs(int argc);
void checkArgsSize(int argSize);