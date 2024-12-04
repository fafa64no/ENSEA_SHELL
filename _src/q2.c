#include "../_include/q2.h"


static char commandBuffer[MAX_COMMAND_LENGTH];
static char outBuffer[MAX_OUT_LENGTH];

ssize_t readCommand(void){
    int pid, status;
    ssize_t ret;

    ret = read(0,commandBuffer,MAX_COMMAND_LENGTH);

    commandBuffer[strlen(commandBuffer)-1]='\0';

    if(!strncmp(commandBuffer,"exit",4) || ret==0){
        write(STDOUT_FILENO,"Bye bye ...\n$\n",strlen("Bye bye ...\n$\n"));
        exit(EXIT_SUCCESS);
    }

    pid = fork();
    int out, sig;

    if(pid != 0){
        waitpid(pid, &status, 0);
        out = WEXITSTATUS(status);
        sig = WIFSIGNALED(status);
        sprintf(outBuffer,"[exit:%d]\n[sign:%d]\n",out,sig);
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