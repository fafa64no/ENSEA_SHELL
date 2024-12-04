#include "../_include/q7.h"



static char commandBuffer[MAX_INPUT_LENGTH];
static char* argsBuffer[MAX_ARGS_COUNT];

ssize_t readCommandWithArg(void){
    ssize_t ret;

    ret = read(0,commandBuffer,MAX_INPUT_LENGTH);
    commandBuffer[strlen(commandBuffer)-1]='\0';
    
    checkExit(commandBuffer, ret);

    int argc = getArgsBuffer(commandBuffer, argsBuffer);

    int redirectionPos;
    int redirection = doesContainRedirection(argsBuffer, argc, &redirectionPos);

    int stdOutCpy = dup(STDOUT_FILENO);
    int stdInCpy = dup(STDIN_FILENO);
    int fd;

    switch (redirection) {
    case REDIRECTION_NONE:
        execCommand(commandBuffer, argsBuffer);
        break;
    case REDIRECTION_INTO_FILE:
        fd = open(argsBuffer[redirectionPos+1], O_CREAT | O_WRONLY);
        dup2(fd, STDOUT_FILENO);
        
        execCommand2(commandBuffer, argsBuffer, fd, stdOutCpy);
        break;
    case REDIRECTION_FROM_FILE:
        fd = open(argsBuffer[redirectionPos+1], O_RDONLY);
        dup2(fd, STDIN_FILENO);
        
        execCommand3(commandBuffer, argsBuffer, fd, stdInCpy);
        break;
    }


    return 0;
}