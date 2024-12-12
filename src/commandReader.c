#include "commandReader.h"

ssize_t getCommandBuffer(char* commandBuffer) {
    ssize_t ret = read(0,commandBuffer,MAX_INPUT_LENGTH);
    commandBuffer[strlen(commandBuffer)-1]='\0';
    return ret;
}

int getArgsBuffer(char* commandBuffer, char** argsBuffer) {
    int argc = 0;
    char* tmpBuffer;
    tmpBuffer = strtok(commandBuffer, " \n");

    while (tmpBuffer != NULL) {
        checkHowManyArgs(argc);
        int argSize = (int)strlen(tmpBuffer);
        checkArgsSize(argSize);

        argsBuffer[argc] = malloc(sizeof(char)*(argSize+1));
        strncpy(argsBuffer[argc], tmpBuffer, argSize);
        argsBuffer[argc][argSize] = '\0';

        argc++;
        tmpBuffer = strtok(NULL, " \n");
    }
    argsBuffer[argc] = (char*)NULL;
    return argc;
}