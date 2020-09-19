#ifndef COMMANDH
#define COMMANDH
#include "mylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>
#include <signal.h>

void myhandler(int signum);
typedef struct command{
    STRING name;
    int cant_args;
    STRING* args;
    bool background;
    bool end_line;

}command;

STRING history_wd;
STRING current_working_directory;

command init_command(STRING _command_name,int _cant_args,STRING* _args);

STRING* parser(STRING tokens,const char* separator);
command* parse_line(STRING _line);

STRING* string_tokenizer(STRING line,const char* separator);
STRING* parse_init(STRING _line);
STRING* parse_and(STRING _line);
STRING* parse_or(STRING _line);
void calling_execute(STRING _line);
int execute_command(command _command,int _fd,int *_out_status);
bool is_digit(STRING _chain);
void show_history();

void update_history(STRING line);

int history_count();

int cfileexists(char* filename);

void exec_history_command(int index);

#endif