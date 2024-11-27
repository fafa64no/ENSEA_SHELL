#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

const char output[] = "Test function.\n";

int main (int argc, char **argv ){
    write(1,output,strlen(output));

    return EXIT_SUCCESS;
}