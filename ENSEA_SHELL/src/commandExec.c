#include "commandExec.h"

void execCommand(char* commandBuffer, char** argsBuffer, int fd, int stdCpy, int redirection) {
    int pid, status;

    pid = fork();

    if(pid != 0){
        fatherExecCommand(pid, status, fd, stdCpy, redirection);
    } else {
        childExecCommand(commandBuffer, argsBuffer);
    }
}

void fatherExecCommand(int pid, int status, int fd, int stdCpy, int redirection) {
    struct timespec start, finish;
    int out, sig;
    float delta_ms;
    char outBuffer[MAX_OUT_LENGTH];

    clock_gettime(CLOCK_REALTIME, &start);
    waitpid(pid, &status, 0);
    clock_gettime(CLOCK_REALTIME, &finish);

    removeRedirection(fd, stdCpy, redirection);
    
    out = WEXITSTATUS(status);
    sig = WIFSIGNALED(status);
    delta_ms = (finish.tv_nsec - start.tv_nsec)/1000000.0f;
    if (sig) {
        sprintf(outBuffer,"[sign:%d|%.1f ms]\n",sig,delta_ms);
    } else {
        sprintf(outBuffer,"[exit:%d|%.1f ms]\n",out,delta_ms);
    }
    
    write(STDOUT_FILENO,outBuffer,strlen(outBuffer));
}

void childExecCommand(char* commandBuffer, char** argsBuffer) {
    execvp(commandBuffer,(char* const*)argsBuffer);

    write(STDOUT_FILENO,"Command not found : ",strlen("Command not found : "));
    write(STDOUT_FILENO,argsBuffer[0],strlen(argsBuffer[0]));
    write(STDOUT_FILENO,"\n",strlen("\n"));

    exit(EXIT_FAILURE);
}