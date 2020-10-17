#include "help.h"

void printHelpMain(){
    printf(HELPIASCII,"'||         '||`\n");
    printf(HELPIASCII," ||          ||\n");
    printf(HELPIASCII," ||''|,.|''|,||'||''|,\n");
    printf(HELPIASCII," ||  ||||..|||| ||  ||\n");
    printf(HELPIASCII,".||  ||`|....||.||..|'\n");
    printf(HELPIASCII,"                ||   \n");
    printf(HELPIASCII,"               .||    \n");




    printf("Integrantes:David Orlando De Quesada Oliva y Javier Dominguez\n");
    printf("Funcionalidades que implementamos:\n");
    printf(KEYWORDCOLOR,"basic:","contempla los puntos del 1 al 8 que son las funcionalidades básicas del shell\n");
    printf(KEYWORDCOLOR,"multi-pipe:"," nuestro shell admite más de una tubería \npor ejemplo :ls -l | head -2 | wc -l es válido\n");
    printf(KEYWORDCOLOR,"spaces:","Admite cualquier cantidad de espacios entre los comandos y parámetros \nls  -l y ls         -l   | head      -2 son válidos\n");
    printf(KEYWORDCOLOR,"multi-pipe:"," nuestro shell admite más de una tubería \npor ejemplo :ls -l | head -2 | wc -l es válido\n");
    printf(KEYWORDCOLOR,"history:","El shell tiene un historial de comandos que permite imprimir los últimos 10 comandos\nSe guarda permanentemente en el archivo History.txt\n");
    printf(KEYWORDCOLOR,"chain:"," Nuestro shell admite los operadores ; && ||\npor ejemplo :ls  && ls > a.txt ; ls -l || ls -l | head-2 && | wc -l es válido\n");
    printf(KEYWORDCOLOR,"ctrl+c:","Nuestro shell no se muere cuando das  ctrl+c y si estoy ejecutando un proceso hijo y decide ignorar el ctrl+c\nla segunda vez le mando un SIGKILL para que termine de ejecutarse\n");
    printf("Comandos built-in:\n");
    printf(BUILTINCOLOR,"help",":para info del proyecto vea help \n");
    printf(BUILTINCOLOR,"cd",":para info vea help cd\n");
    printf(BUILTINCOLOR,"true",":para info vea help true\n");
    printf(BUILTINCOLOR,"false",":para info vea help false\n");
    // false->history->para info vea help history
    // \nagain->para info vea help again\n");
}
void printHelp(int option){
    if (option == 0){
        printHelpMain();
    }
     // printf("multi-pipe:");
    // 
    // printf("Funcionalidades que implementamos:\n");
    // printf("Funcionalidades que implementamos:\n");
    // printf("Funcionalidades que implementamos:\n");
    // printf("Funcionalidades que implementamos:\n");
    // printf("Funcionalidades que implementamos:\n");    
    // basic: funcionalidades básicas (3 puntos)
    // multi-pipe: multiples tuberías (1 punto)
    // ctrl+c: captuar y enviar señales a procesos (0.5 puntos)
    // help: ayuda (1 punto)
}