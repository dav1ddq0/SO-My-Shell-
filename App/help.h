#ifndef HELP_H
#define HELP_H
#include "mylib.h"
#include <stdio.h>




#define KEYWORDCOLOR YELLOW_F "%s" RESET_COLOR "%s"
#define BUILTINCOLOR GREEN_F "%s" RESET_COLOR "%s"
#define HELPIASCII CYAN_F "%s" RESET_COLOR 
void printHelpMain();
void printCTRLC();
void printSpaces();
void printFG();
void printBG();
void printCD();
void printJobs();
void printHistory();
void printHelp(int _option);
#endif