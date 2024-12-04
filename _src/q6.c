#include "../_include/q6.h"



static char commandBuffer[MAX_INPUT_LENGTH];
static char* argsBuffer[MAX_ARGS_COUNT];
static char outBuffer[MAX_OUT_LENGTH];

ssize_t readCommandWithArg(void){
    int pid, status;
    ssize_t ret;

    ret = read(0,commandBuffer,MAX_INPUT_LENGTH);
    commandBuffer[strlen(commandBuffer)-1]='\0';
    
    if(!strncmp(commandBuffer,"exit",4) || ret==0){
        write(STDOUT_FILENO,"Bye bye ...\n$\n",strlen("Bye bye ...\n$\n"));
        exit(EXIT_SUCCESS);
    }

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

    struct timespec start, finish;
    clock_gettime(CLOCK_REALTIME, &start);
    pid = fork();
    int out, sig;
    float delta_ms;

    if(pid != 0){
        waitpid(pid, &status, 0);
        clock_gettime(CLOCK_REALTIME, &finish);

        out = WEXITSTATUS(status);
        sig = WIFSIGNALED(status);

        delta_ms = (finish.tv_nsec - start.tv_nsec)/1000000.0f;

        if (out) {
            sprintf(outBuffer,"[exit:%d|%.1f ms]\n",out,delta_ms);
        } else {
            sprintf(outBuffer,"[sign:%d|%.1f ms]\n",sig,delta_ms);
        }
        
        write(STDOUT_FILENO,outBuffer,strlen(outBuffer));
    } else {
        execvp(commandBuffer,(char* const*)argsBuffer);

        write(STDOUT_FILENO,"Command not found : ",strlen("Command not found : "));
        write(STDOUT_FILENO,argsBuffer[0],strlen(argsBuffer[0]));
        write(STDOUT_FILENO,"\n",strlen("\n"));

        exit(EXIT_FAILURE);
    }

    return sig;
}