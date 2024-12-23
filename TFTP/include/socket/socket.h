#pragma once

#include "fileReader.h"
#include "socketSend.h"
#include "socketReceive.h"
#include "utils.h"

int getSocket();

void readSocket(int source, struct addrinfo* dest, char* filename);
void writeSocket(int source, struct addrinfo* dest, char* sourceFilename, char* destFilename);
