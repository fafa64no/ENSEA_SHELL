#include "defaultMsg.h"

static const char defaultPrompt[] = "enseash % ";
static const char welcomeText[] = "$./enseash\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";

void welcomeMsg(){
    write(STDOUT_FILENO,welcomeText,strlen(welcomeText));
}

void defaultPromptMsg(){
    write(STDOUT_FILENO,defaultPrompt,strlen(defaultPrompt));
}