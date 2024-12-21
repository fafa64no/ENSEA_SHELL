#pragma once

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define REDIRECTION_NONE 0
#define REDIRECTION_INTO_FILE 1
#define REDIRECTION_FROM_FILE 2

int doesContainRedirection(char** argsBuffer, int argc, int* redirectionPos);

void removeRedirection(int fd, int stdCpy, int redirection);
void removeRedirectionOut(int fd, int stdCpy);
void removeRedirectionIn(int fd, int stdCpy);

int prepareRedirection(char** argsBuffer, int* fd, int* stdCpy, int argc);