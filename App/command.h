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
#include "linked_list.h"
#include "help.h"

void hijo(int signum);
typedef struct command{
    STRING name;
    int cant_args;
    STRING* args;
    bool background;
    bool end_line;

}command;

STRING history_wd;
STRING current_working_directory;
int running_bg(STRING line);
command init_command(STRING _command_name,int _cant_args,STRING* _args);
STRING concatStr(STRING str1,STRING str2);
STRING* parser(STRING tokens,const char* separator);
command* parse_line(STRING _line);

STRING* string_tokenizer(STRING line,const char* separator);
STRING* parse_init(STRING _line);
STRING* parse_and(STRING _line);
STRING* parse_or(STRING _line);
void calling_execute(STRING _line,list* _jobs);
int execute_command(command _command,int _fd,int *_out_status,list* _jobs,int *__pid);
bool is_digit(STRING _chain);
void show_history();

void update_history(STRING line);

int history_count();

int cfileexists(char* filename);

void exec_history_command(int index,list* _jobs);
void padre(int _signum);
int child_pid;
int is_bg_com;
int gpid;
STRING current_line;
int wait_bg_pid;
int canCtrlCPid; 
int ppid;
static int SIGUSR1_pid = 0;

#endif