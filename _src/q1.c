#include "../_include/q1.h"

static const char defaultPrompt[] = "enseash % ";
static const char welcomeText[] = "$./enseash\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";

void welcomeMsg(void){
    write(1,welcomeText,strlen(welcomeText));
}

void defaultPromptMsg(void){
    write(1,defaultPrompt,strlen(defaultPrompt));
}