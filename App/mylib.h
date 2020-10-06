#ifndef MYLIB_H
#define MYLIB_H
//Tabla de colores en C
#define RESET_COLOR    "\x1b[0m"
#define BLACK_F        "\x1b[30m"
#define BLACK_B    "\x1b[40m"
#define RED_F     "\x1b[31m"
#define RED_B     "\x1b[41m"
#define GREEN_F    "\x1b[32m"
#define GREEN_B    "\x1b[42m"
#define YELLOW_F "\x1b[33m"
#define YELLOW_B  "\x1b[43m"
#define BLUE_F     "\x1b[34m"
#define BLUE_B      "\x1b[44m"
#define MAGENTA_F  "\x1b[35m"
#define MAGENTA_B  "\x1b[45m"
#define CYAN_F     "\x1b[36m"
#define CYAN_B     "\x1b[46m"
#define WHITE_F   "\x1b[37m"
#define WHITE_B   "\x1b[47m"

#define STRING_TERMINATOR ((void *)0) 
#define TRUE 1
#define FALSE 0
#define line_buffer 200
#define user_login_buffer 100
#define hostname_buffer 100
#define cwd_buffer 500
#define PROMPT_FORMAT  GREEN_F "%s@%s" RESET_COLOR ":" BLUE_F "%s" WHITE_F "$ "  RESET_COLOR
#define NAMES_GROUPS   RED_F  "%s "  WHITE_F "%s" RED_F  "%s " WHITE_F "%s\n" RESET_COLOR 
typedef char* STRING;
typedef int bool;

#endif