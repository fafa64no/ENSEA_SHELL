#include <stdlib.h>

#include "defaultMsg.h"
#include "commandReader.h"
#include "redirection.h"
#include "checkManyThings.h"
#include "commandExec.h"

int main (int argc, char **argv ){
    welcomeMsg();

    while(1){
        defaultPromptMsg();

        char commandBuffer[MAX_INPUT_LENGTH];
        ssize_t ret = getCommandBuffer(commandBuffer);
        checkExit(commandBuffer, ret);

        char* argsBuffer[MAX_ARGS_COUNT];
        int argc = getArgsBuffer(commandBuffer, argsBuffer);

        int fd, stdCpy, redirection = prepareRedirection(argsBuffer, &fd, &stdCpy, argc);
        
        execCommand(commandBuffer, argsBuffer, fd, stdCpy, redirection);
    }

    return EXIT_SUCCESS;
}