#include "../_include/q6.h"



static char inputBuffer[MAX_INPUT_LENGTH];
static char commandBuffer[MAX_COMMAND_LENGTH];
static char outBuffer[MAX_OUT_LENGTH];

ssize_t readCommandWithArg(void){
    int pid, status;
    ssize_t ret;

    ret = read(0,inputBuffer,MAX_INPUT_LENGTH);
    commandBuffer[strlen(inputBuffer)-1]='\0';

    if(!strncmp(inputBuffer,"exit",4) || ret==0){
        write(STDOUT_FILENO,"Bye bye ...\n$\n",strlen("Bye bye ...\n$\n"));
        exit(EXIT_SUCCESS);
    }

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
        execlp(commandBuffer,commandBuffer,(char*)NULL);
        write(STDOUT_FILENO,"Command not found : ",strlen("Command not found : "));
        write(STDOUT_FILENO,commandBuffer,strlen(commandBuffer));
        write(STDOUT_FILENO,"\n",strlen("\n"));
        exit(EXIT_FAILURE);
    }

    return sig;
}