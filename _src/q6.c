#include "../_include/q6.h"



static char commandBuffer[MAX_INPUT_LENGTH];
static char* argsBuffer[MAX_ARGS_COUNT];
static char outBuffer[MAX_OUT_LENGTH];

ssize_t readCommandWithArg(void){
    int pid, status;
    ssize_t ret;

    ret = read(0,commandBuffer,MAX_INPUT_LENGTH);
    commandBuffer[strlen(commandBuffer)-1]='\0';
    
    checkExit(commandBuffer, ret);

    int argc = getArgsBuffer(commandBuffer, argsBuffer);

    struct timespec start, finish;
    int out, sig;
    float delta_ms;

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

    return sig;
}