#include "../_include/q1.h"

static const char defaultPrompt[] = "enseash % ";
static const char welcomeText[] = "$./enseash\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";

void welcomeMsg(void){
    write(STDOUT_FILENO,welcomeText,strlen(welcomeText));
}

void defaultPromptMsg(void){
    write(STDOUT_FILENO,defaultPrompt,strlen(defaultPrompt));
}