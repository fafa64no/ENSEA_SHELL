#include <stdlib.h>

#include "../_include/q1.h"
#include "../_include/q2.h"

int main (int argc, char **argv ){
    ssize_t returnMsg;
    char buffer[100]={0};
    welcomeMsg();
    while(1){
        defaultPromptMsg();
        returnMsg = readCommand();
        sprintf(buffer,"test : %d\n",(int)returnMsg);
        write(1,buffer,strlen(buffer));
    }

    return EXIT_SUCCESS;
}