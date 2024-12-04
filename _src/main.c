#include <stdlib.h>

#include "../_include/q1.h"
#include "../_include/q2.h"
#include "../_include/q6.h"

char buffer[100]={0};

int main (int argc, char **argv ){
    ssize_t returnMsg;
    welcomeMsg();
    while(1){
        defaultPromptMsg();
        readCommandWithArg();
    }

    return EXIT_SUCCESS;
}