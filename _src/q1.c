#include "../_include/q1.h"

const char defaultPrompt[] = "enseash % ";
const char welcomeText[] = "$./enseash\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";

void welcomeMsg(void){
    write(1,welcomeText,strlen(welcomeText));
    write(1,defaultPrompt,strlen(defaultPrompt));
}