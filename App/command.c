 
#include "command.h"

bool first_time_history_checked = TRUE;
int history_size;
int size;
int bg;

command init_command(STRING name,int cant_args,STRING* args){
    command new_command;
    new_command.name=name;
    new_command.cant_args=cant_args;
    new_command.args=args;
    new_command.background=FALSE;
    new_command.end_line=0;
    return new_command; 
}

//parser para los casos que no puedo resolver con strtok ,|| y &&
STRING* parser (STRING chain,const char* separator){
    STRING* tokens =string_tokenizer(chain," ");
    int init=0;
    int final=0;
    int size_string=0;
    int aux_size=0;
    STRING* result=malloc(sizeof(tokens)*2);
    int i=0;

    while (tokens[final] != NULL)
    {
        if(!strcmp(tokens[final],separator)){
            STRING temp=malloc(aux_size*size_string *sizeof(char));
            int pos=0;
            while (init!=final){
                STRING min=tokens[init];
                while (*min!='\0'){
                    temp[pos++] = *min;
                    min++;
                }

                temp[pos++]=' ';
                
                init++;
            }
            init++;
            result[i]=malloc(sizeof(temp));
            strcpy(result[i],temp);
            i++;
            final++;
            aux_size=0;
            size_string=0;

        }
        else{

            size_string+=(int)strlen(tokens[final]);
            aux_size++;
            final++;
        }
    }
    STRING temp=malloc(aux_size*size_string *sizeof(char));
    int pos=0;

    while (init!=final){
        STRING min=tokens[init];
        while (*min!='\0'){
            temp[pos++] = *min;
            min++;
        }

        temp[pos++]=' ';
        init++;

    }

    result[i]=malloc(sizeof(temp));
    strcpy(result[i],temp);
    i++;
    result[i]=NULL;
    
    return result;
} 

STRING* string_tokenizer(STRING line,const char* separator){
    size_t siz = 2;
    STRING* tokens = malloc((siz + 1) * sizeof(char*));
    STRING token;
    int index = 0;
    token = strtok(line, separator);// The first call to strtok must pass the C string to tokenize
    while (token != NULL){   //Cuando no queden mas token strtok returns NULL lo que quiere decir que la linea fue parseada completamente en tokens
		
        if(index == siz) {
    		siz *=2;
    		tokens = realloc(tokens, (siz + 1) * sizeof(char*)); 
    	}
        tokens[index++] = token;
        if(!strcmp(separator,"#") || !strcmp(separator,"\n")){
            break;
        }
    	
        
        //subsequent calls must specify NULL as the first argument, which tells the function to continue tokenizing the string you passed in first        
        token = strtok(NULL, separator);
    }
    
    tokens[index] = NULL;//NULL terminator
    size = index;
    return tokens;

}


STRING* parse_init(STRING line){
    STRING* tokens =string_tokenizer(*string_tokenizer(*string_tokenizer(line,"\n"),"#"),";");
    return tokens;
}
STRING* parse_and(STRING line){
     STRING* tokens = parser(line,"&&");     
     return tokens;
}
STRING* parse_or(STRING line){
    STRING* tokens = parser(line,"||");     
    return tokens;     
}

command* parse_line(STRING line){
    STRING* tokens = string_tokenizer(line,"|");
	int total = size, i;
	command* commands = malloc((total + 1)* sizeof(command));
	
	for(i = 0; i < total; i++) {       
        STRING* args = string_tokenizer(tokens[i], " ");
        commands[i]=init_command(args[0],size,args);      
	}
	commands[i - 1].end_line = 1;
	commands[i].name = NULL;

	return commands;

}
void myhandler(int signum){
    //if(signum==SIGUSR1)
    printf("GoodByeee\n");
    //kill(getpid(),SIGKILL);  
}

void calling_execute(STRING line){   
    STRING* inits=parse_init(line);//"#" "\n" ";"
    while (*inits!=NULL){
            
        //STRING* ands = parse_and(*inits); // "&&"
        // int out_status=-2;
        // while (*ands !=NULL){
        int out_status;
        //     STRING* ors=parse_or(*ands); // "||"
            
        //     while (*ors!=NULL){
        command* commands =parse_line(*inits); 
        //         int fd=-1;
                
        while (commands->name){
            int fd =-1;    
            fd=execute_command(*commands,fd,&out_status);
            commands++;            
            // }
            // if(out_status == 0) break;                   
            // ors++;
        }
            // if(out_status != 0) break;
            // ands++;
        
            inits++;
        } 
}

bool is_digit(STRING chain){
    while (*chain !='\0'){
        if(!isdigit(*chain)) return FALSE;
        chain++;                  
    }
    return TRUE;
}

int execute_command(command command,int _fd,int *exit_status){
    //fd[0] will be the fd(file descriptor) for the 
    //read end of pipe.
    //fd[1] will be the fd for the write end of pipe.
    //Returns : 0 on Success.
    //-1 on error.ls;
    int fds[2];

	//pipe(fds);
     /* Create the pipe. */
    if (pipe (fds))
    {
      fprintf(stderr, "Pipe failed.\n");
      return EXIT_FAILURE;
    }
    
    if(!strcmp(command.args[0], "cd")) { //en caso que sea el comando cd
        
		close(fds[1]);
        if(command.cant_args != 2) { printf("bash: cd: to many arguments\n"); *exit_status=1;} // si existen mas de 2 argumentos imprimir error
        else if(chdir(command.args[1])) {            
            perror("cd"); 
            *exit_status=1;
        } // si el chdir retorna error
        else
        {
           *exit_status=0;
        }
        

        
    }
    else if(!strcmp(command.args[0], "exit")) { //si se escribe el comando exit salir de la consola	
    	close(fds[0]); 
        close(fds[1]);
        exit(0);
    }
    else if(!strcmp(command.args[0], "history")) { //Hay que implementarlo
         if(command.cant_args != 1){
             *exit_status=1;
             printf("history:to many arguments\n");
        }
         else{
            *exit_status=0; 
            show_history();   
        }
                     
    }
    
    else if(!strcmp(command.args[0], "jobs")){  //Hay que implementarlo


    }
    else if(!strcmp(command.args[0], "again")){ 
        if(command.cant_args!=2 || !is_digit(command.args[1])){
            *exit_status=1;
            perror("again");
        }
        else{
            *exit_status=0;
            exec_history_command(atoi(command.args[1]));
        }
        
    }
    else if(!strcmp(command.args[0],"true")){
        *exit_status=0;
    }
    else if(!strcmp(command.args[0],"false")){
        *exit_status=1;

    }
    
    //Cualquier otro comando
    else {
        int pid = fork();// fork child 0 child 1 parent
        
	    if (!pid) { //  Child
            //signal(SIGUSR1,myhandler);
			close(fds[0]);//
            int fd_read_out = _fd; 
            int fd_write_in = fds[1];
            
            STRING* process_result = malloc((command.cant_args+1)*sizeof(STRING)*sizeof(STRING));
            //en caso que el proceso que va esta siendo ejecutado es el ultimo de la linea antes parseada
            if(command.end_line){ 
                close(fds[1]); 
                fd_write_in = -1;                
            }
            int pos=0;
            for (int i = 0; i < command.cant_args; i++){
                if(!strcmp(command.args[i],">")){
                    close(fd_write_in);
                    i++;
                    //0766 permiso de todo lectura escritura para usuario y grupo

                    int fd_file =open(command.args[i],O_WRONLY|O_CREAT|O_TRUNC,0766);
                    // if(fd_file < 0){
                    //     fd_file=open(command.args[i],O_WRONLY|O_CREAT|O_TRUNC,0766);
                    // }
                    fd_write_in=fd_file;


                    //int fd_file =open(command.args[i],O_WRONLY);
                }
                else if(!strcmp(command.args[i],"<")){
                    i++;
                    close(fd_read_out);
                    fd_read_out=open(command.args[i],O_RDONLY,0766);
                }
                else if(!strcmp(command.args[i],">>")){
                    i++;
                    close(fd_write_in);                    
                    fd_write_in=open(command.args[i],O_WRONLY|O_CREAT|O_APPEND,0766);
                }
                                              
                else
                {
                    process_result[pos++] = command.args[i];
                }
            }
            process_result[pos] = STRING_TERMINATOR;           
            

            // here the newfd is the file descriptor of stdin
            //STDIN_FILENO 0 fd de stdin
            dup2(fd_read_out, STDIN_FILENO);
			close(fd_read_out);
            //here the newfd is the file descriptor of stdout (i.e. 1)
            //STDOUT_FILENO 1 fd de stdout
			dup2(fd_write_in, STDOUT_FILENO);
	    	close(fd_write_in);

            int res_execvp=execvp(process_result[0], process_result);
            if( res_execvp < 0) {//en caso que el sistema no pueda ejecutar ese comando 
                perror("execvp");
            }
            
            
            exit(EXIT_FAILURE);

	    }
	    else {    //Parent
            //signal(SIGINT,myhandler);
			close(fds[1]);
            // variable que va a guardar el status que devuelva wait
            int status=0;
            // take one argument status and returns 
            // a process ID of dead children.
            //kill(pid,SIGUSR1);
            //printf("%i\n",pid);
            wait(&status);
            *exit_status=status;
            //This macro returns a nonzero value if the child process terminated normally with exit 
            if(WIFEXITED(status)){
                //int exit_status=WEXITSTATUS(status);
                //*out_status=exit_status;
                //printf("child_status %d\n",exit_status);
            }
            else{
                perror(command.args[0]);
            }
            
            
            // if(!WIFEXITED(status)){
            //     perror(command.args[0]);
            // }
            

           
	    }
    }

	return fds[0];

}


void show_history(){
    // Simplemente leer de History.txt
    chdir(history_wd);
    int fd = open("History.txt",O_RDONLY);
    char buf;
    int i = 49;
    const char hyphen = '-';

    if(history_size > 0){
        write(1,&i,1);
        write(1,&hyphen,1);
    }
     
    while (read(fd, &buf, 1)){
        write(1, &buf, 1);
        
        if (buf == '\n'){
            i++;
            if(i == 58){
                i = 49;
                write(1,&i,1);
                i = 48;
                write(1,&i,1);
                write(1,&hyphen,1);
                i = 58;
            }

            else if((i-48) <= history_size){
                write(1,&i,1);
                write(1,&hyphen,1);
            }
        }
    }
    chdir(current_working_directory);
}

void update_history(STRING line){
    chdir(history_wd);
    if(cfileexists("History.txt")){ // En caso de que alguien lo borre
       // printf("VERDADERAMENTE EXISTE PENDEJO\n");
        if(first_time_history_checked){ //Para saber cuantos elementos hay guardados en el history (solo e ejecuta la primera vez q se ejecuta el shell)
            history_size = history_count();
            first_time_history_checked = 0;
        }
    }
    else history_size = FALSE;

   // printf("HISTORY CURRENT SIZE TOP --> %d\n",history_size);
    char* line_reader = line;
    int line_length = strlen(line);

    //printf("ESTOY ACA\n");
    //printf("LINE ---> %s",line);
    int fd1;
    char buf1;

    if(history_size < 10){ // Si hay menos de 10 commandos guardados en el history simplemente agregar/crear History.txt en caso de que no exista
        fd1 = open("History.txt",O_WRONLY | O_APPEND | O_CREAT,0766);

        for(int i = 0; i < line_length;i++,line_reader++){
            write(fd1,line_reader,1);
           // printf("%d\n",i);
        }
        close(fd1);
        history_size++;
    }

    else {  // Si hay 10 elementos esto es lo que se hace : 
            // 1-Cambiarle el nombre de History.txt ---> Old_History.txt;                                               
            // 2-Crear un nuevo txt que se llame History.txt :) ;
            // 3-Con 2 filedescriptors leer de Old_History con uno de ellos y con el otro escribir en el recien creado History.txt
            // los ultimos 9 commandos de Old_history + el actual commando 
            // 4-Borrar Old_History :D                                             
        rename("History.txt","Old_History.txt");
        fd1 = open("Old_History.txt",O_RDONLY);
        int fd2 = open("History.txt",O_WRONLY | O_CREAT,0766);

        while (read(fd1,&buf1,1)){ //Ignorar primer comando de la lista
            if(buf1 == '\n') break;
           // printf("Ignorar primer comando de la lista\n");
        } 
            

        while (read(fd1,&buf1,1)){ //Copiar los 9 ultimos para el nuevo .txt
            write(fd2,&buf1,1);
           // printf("Copiar los k ultimos para el nuevo .txt\n");
        }

        int curr_char = 0;
        while(curr_char < line_length){ //Agregar ultimo comando al txt
            write(fd2,line_reader,1);
           // printf("Agregar ultimo comando al txt");
            line_reader++;
            curr_char++;
        }

        close(fd1);
        close(fd2);
        remove("Old_History.txt"); // Eliminar Old_History.txt
    }
    chdir(current_working_directory);
   // printf("HISTORY CURRENT SIZE BOTTOM--> %d\n",history_size);
}

int history_count(){
    int answer = 0;

    int fd = open("History.txt",O_RDONLY);
    char buf;
    if(fd != -1){
        while (read(fd, &buf, 1))
            if(buf == '\n') answer++;
    }
   return answer;
}

int cfileexists(char* filename){
    FILE* file;
    if(file = fopen(filename,"r")){
        fclose(file);
        return 1;
    }
    return 0;
}

void exec_history_command(int index){
    if(1 <= index && index <= history_size){
        chdir(history_wd);
        STRING history_reader =  malloc(sizeof(char));
        STRING history_line = history_reader;

        char buf;
        int fd = open("History.txt",O_RDONLY);

        int i = 1;
        
        while (read(fd,&buf,1)){

            if(i == index){
                //printf("buf char value is ---> %c\n",buf);
                *history_reader = buf;
                //printf("history_reader char value is ---> %c\n",*history_reader);
                history_reader++;
                if(buf == '\n')
                    break;
                
            }
            if(buf == '\n'){
                i++;
                //printf("I++ anormal\n");
            } 
        }
        close(fd);

        calling_execute(history_line);
        chdir(current_working_directory);
    }
    else printf("Again argument not in range\n");
}