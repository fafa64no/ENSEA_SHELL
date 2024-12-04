#include "../_include/utils.h"

void checkExit(char* commandBuffer, int ret) {
    if(!strncmp(commandBuffer,"exit",4) || ret==0){
        write(STDOUT_FILENO,"Bye bye ...\n$\n",strlen("Bye bye ...\n$\n"));
        exit(EXIT_SUCCESS);
    }
}

int getArgsBuffer(char* commandBuffer, char** argsBuffer) {
    int argc = 0;
    char* tmpBuffer;
    tmpBuffer = strtok(commandBuffer, " \n");

    while (tmpBuffer != NULL) {
        int argSize = (int)strlen(tmpBuffer);
        argsBuffer[argc] = malloc(sizeof(char)*(argSize+1));
        strncpy(argsBuffer[argc], tmpBuffer, argSize);
        argsBuffer[argc][argSize] = '\0';
        argc++;
        tmpBuffer = strtok(NULL, " \n");
    }
    argsBuffer[argc] = (char*)NULL;

    return argc;
}

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

void execCommand(char* commandBuffer, char** argsBuffer) {
    int pid, status;

    struct timespec start, finish;
    int out, sig;
    float delta_ms;
    char outBuffer[MAX_OUT_LENGTH];

    clock_gettime(CLOCK_REALTIME, &start);

    pid = fork();

    if(pid != 0){
        waitpid(pid, &status, 0);
        
        clock_gettime(CLOCK_REALTIME, &finish);
        out = WEXITSTATUS(status);
        sig = WIFSIGNALED(status);
        delta_ms = (finish.tv_nsec - start.tv_nsec)/1000000.0f;
        if (sig) {
            sprintf(outBuffer,"[sign:%d|%.1f ms]\n",sig,delta_ms);
        } else {
            sprintf(outBuffer,"[exit:%d|%.1f ms]\n",out,delta_ms);
        }
        
        write(STDOUT_FILENO,outBuffer,strlen(outBuffer));
    } else {
        execvp(commandBuffer,(char* const*)argsBuffer);

        write(STDOUT_FILENO,"Command not found : ",strlen("Command not found : "));
        write(STDOUT_FILENO,argsBuffer[0],strlen(argsBuffer[0]));
        write(STDOUT_FILENO,"\n",strlen("\n"));

        exit(EXIT_FAILURE);
    }
}

void execCommand2(char* commandBuffer, char** argsBuffer, int fd, int stdCpy) {
    int pid, status;

    struct timespec start, finish;
    int out, sig;
    float delta_ms;
    char outBuffer[MAX_OUT_LENGTH];

    clock_gettime(CLOCK_REALTIME, &start);

    pid = fork();

    if(pid != 0){
        waitpid(pid, &status, 0);
        removeRedirectionOut(fd, stdCpy);
        
        clock_gettime(CLOCK_REALTIME, &finish);
        out = WEXITSTATUS(status);
        sig = WIFSIGNALED(status);
        delta_ms = (finish.tv_nsec - start.tv_nsec)/1000000.0f;
        if (sig) {
            sprintf(outBuffer,"[sign:%d|%.1f ms]\n",sig,delta_ms);
        } else {
            sprintf(outBuffer,"[exit:%d|%.1f ms]\n",out,delta_ms);
        }
        
        write(STDOUT_FILENO,outBuffer,strlen(outBuffer));
    } else {
        execvp(commandBuffer,(char* const*)argsBuffer);

        write(STDOUT_FILENO,"Command not found : ",strlen("Command not found : "));
        write(STDOUT_FILENO,argsBuffer[0],strlen(argsBuffer[0]));
        write(STDOUT_FILENO,"\n",strlen("\n"));

        exit(EXIT_FAILURE);
    }
}

void execCommand3(char* commandBuffer, char** argsBuffer, int fd, int stdCpy) {
    int pid, status;

    struct timespec start, finish;
    int out, sig;
    float delta_ms;
    char outBuffer[MAX_OUT_LENGTH];

    clock_gettime(CLOCK_REALTIME, &start);

    pid = fork();

    if(pid != 0){
        waitpid(pid, &status, 0);
        removeRedirectionIn(fd, stdCpy);
        
        clock_gettime(CLOCK_REALTIME, &finish);
        out = WEXITSTATUS(status);
        sig = WIFSIGNALED(status);
        delta_ms = (finish.tv_nsec - start.tv_nsec)/1000000.0f;
        if (sig) {
            sprintf(outBuffer,"[sign:%d|%.1f ms]\n",sig,delta_ms);
        } else {
            sprintf(outBuffer,"[exit:%d|%.1f ms]\n",out,delta_ms);
        }
        
        write(STDOUT_FILENO,outBuffer,strlen(outBuffer));
    } else {
        execvp(commandBuffer,(char* const*)argsBuffer);

        write(STDOUT_FILENO,"Command not found : ",strlen("Command not found : "));
        write(STDOUT_FILENO,argsBuffer[0],strlen(argsBuffer[0]));
        write(STDOUT_FILENO,"\n",strlen("\n"));

        exit(EXIT_FAILURE);
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