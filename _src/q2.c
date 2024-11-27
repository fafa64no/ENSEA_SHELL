#include "../_include/q2.h"


static char commandBuffer[MAX_COMMAND_LENGTH];

ssize_t readCommand(void){
    int pid, status;
    ssize_t ret;

    ret = read(0,commandBuffer,MAX_COMMAND_LENGTH);

    commandBuffer[strlen(commandBuffer)-1]='\0';

    if(!strncmp(commandBuffer,"exit",4)){
        write(1,"Bye bye ...\n$\n",strlen("Bye bye ...\n$\n"));
        exit(EXIT_SUCCESS);
    }

    pid = fork();

    if(pid != 0){
        wait(&status);
    } else {
        ret = execlp(commandBuffer,commandBuffer,(char*)NULL);
        write(1,"Not good. At all. Like really.\n",strlen("Not good. At all. Like really.\n"));
        write(1,commandBuffer,strlen(commandBuffer));
        exit(EXIT_FAILURE);
    }

    return ret;
}