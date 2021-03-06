#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "command.h"
#include "mylib.h"
#include "linked_list.h"

STRING line; 
STRING hostname;
STRING user_login;
list bg;


size_t size;

void init();

//collect all children processes zombies 
void ZombiesHandler(int signum){
    list temp;
    int status;
    int pid=waitpid(-1,&status,WNOHANG);// whose execution is completed but it still has an entry in the process table
    while (pid > 0){
        remove_pid(&bg,pid);
        pid=waitpid(-1,&status,WNOHANG);
    }
}

int main(int arc,char** argv){
    init();
    current_pid=-1;
    
    
    while (TRUE){
        
        is_bg_com=0;
        getcwd(current_working_directory,cwd_buffer); 
        printf(PROMPT_FORMAT,user_login,hostname,current_working_directory);
        int characters = getline(&line, &size, stdin);
        if(characters==-1){
            if(errno==EINTR){
                clearerr(stdin);
                continue;
            }
            perror("gentile");

        }
        
        update_history(line);
        calling_execute(line,&bg);
        sizePIDs=0;
    }
    free(line);
}

void init(){
    system("clear");
    //logo ,team name
    printf(RED_F"        ╭━╮╭━┳╮╱╱╭╮╱╭━━━┳╮╱╭┳━━━┳╮╱╱╭╮\n");
    printf("        ┃┃╰╯┃┃╰╮╭╯┃╱┃╭━╮┃┃╱┃┃╭━━┫┃╱╱┃┃\n");
    printf("        ┃╭╮╭╮┣╮╰╯╭╯╱┃╰━━┫╰━╯┃╰━━┫┃╱╱┃┃\n");
    printf("        ┃┃┃┃┃┃╰╮╭╋━━╋━━╮┃╭━╮┃╭━━┫┃╱╭┫┃╱╭╮\n");
    printf("        ┃┃┃┃┃┃╱┃┃╰━━┫╰━╯┃┃╱┃┃╰━━┫╰━╯┃╰━╯┃\n");
    printf("        ╰╯╰╯╰╯╱╰╯╱╱╱╰━━━┻╯╱╰┻━━━┻━━━┻━━━╯\n" RESET_COLOR);

    printf(NAMES_GROUPS,"David Orlando De Quesada Oliva ","C211,","Javier Dominguez" ,"C212");
    size =0;
    hostname=malloc(sizeof(char)*hostname_buffer);
    current_working_directory=malloc(sizeof(char)*cwd_buffer);
    user_login=getlogin();
    gethostname(hostname,hostname_buffer);
    history_wd=malloc(sizeof(char)*cwd_buffer);
    getcwd(history_wd,cwd_buffer);
    line=malloc(sizeof(char)*line_buffer);
    signal(SIGINT, InterruptHandler);
    signal(SIGCHLD,ZombiesHandler);
    init_list(&bg);
    canCtrlCPid=0;
    sizePIDs=0;
    ppid=getpid();
}

