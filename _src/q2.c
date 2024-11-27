#include "../_include/q2.h"

void readCommand(void){
    char* commandBuffer=(char*)malloc(sizeof(char)*MAX_COMMAND_LENGTH);

    read(1,commandBuffer,strlen(commandBuffer));
    write(1,commandBuffer,strlen(commandBuffer));

    free(commandBuffer);
}