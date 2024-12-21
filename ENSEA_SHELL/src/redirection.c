#include "redirection.h"

int doesContainRedirection(char** argsBuffer, int argc, int* redirectionPos) {
    for(int i = 0; i < argc; i++) {
        if(!strncmp(argsBuffer[i],">",1)) {
            argsBuffer[i] = (char*) NULL;
            *redirectionPos = i;
            return REDIRECTION_INTO_FILE;
        } else if(!strncmp(argsBuffer[i],"<",1)) {
            argsBuffer[i] = (char*) NULL;
            *redirectionPos = i;
            return REDIRECTION_FROM_FILE;
        }
    }
    return REDIRECTION_NONE;
}

void removeRedirection(int fd, int stdCpy, int redirection) {
    switch (redirection) {
    case REDIRECTION_NONE:
        break;
    case REDIRECTION_INTO_FILE:
        removeRedirectionOut(fd, stdCpy);
        break;
    case REDIRECTION_FROM_FILE:
        removeRedirectionIn(fd, stdCpy);
        break;
    default:
        write(STDOUT_FILENO,"Unknown redirection type.\n",strlen("Unknown redirection type.\n"));
        break;
    }
}

void removeRedirectionOut(int fd, int stdCpy) {
    close(fd);
    dup2(stdCpy, STDOUT_FILENO);
}

void removeRedirectionIn(int fd, int stdCpy) {
    close(fd);
    dup2(stdCpy, STDIN_FILENO);
}

int prepareRedirection(char** argsBuffer, int* fd, int* stdCpy, int argc) {
    int redirectionPos, redirection = doesContainRedirection(argsBuffer, argc, &redirectionPos);
    int stdOutCpy = dup(STDOUT_FILENO), stdInCpy = dup(STDIN_FILENO);

    switch (redirection) {
    case REDIRECTION_NONE:
        break;
    case REDIRECTION_INTO_FILE:
        *fd = open(argsBuffer[redirectionPos+1], O_CREAT | O_WRONLY);
        dup2(*fd, STDOUT_FILENO);
        *stdCpy = stdOutCpy;
        break;
    case REDIRECTION_FROM_FILE:
        *fd = open(argsBuffer[redirectionPos+1], O_RDONLY);
        dup2(*fd, STDIN_FILENO);
        *stdCpy = stdInCpy;
        break;
    }

    return redirection;
}