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
    printf(KEYWORDCOLOR,"history:","El shell tiene un historial de comandos que permite imprimir los últimos 10 comandos\nSe guarda permanentemente en el archivo History.txt\n");
    printf(KEYWORDCOLOR,"chain:"," Nuestro shell admite los operadores ; && ||\npor ejemplo :ls  && ls > a.txt ; ls -l || ls -l | head-2 && | wc -l es válido\n");
    printf(KEYWORDCOLOR,"ctrl+c:","Nuestro shell no se muere cuando das  ctrl+c y si estoy ejecutando un proceso hijo y decide ignorar el ctrl+c\nla segunda vez le mando un SIGKILL para que termine de ejecutarse\n");
    printf("Comandos built-in:\n");
    printf(BUILTINCOLOR,"help",":para info del proyecto vea help \n");
    printf(BUILTINCOLOR,"cd",":para info vea help cd\n");
    printf(BUILTINCOLOR,"true",":para info vea help true\n");
    printf(BUILTINCOLOR,"false",":para info vea help false\n");
    
    printf("Idea general de como funciona el help:\n");
    printf("Lo primero que hago es incializar las variables que uso y printar el logo de mi shell\n");
    printf("Printeo en mi prompt el user login hostname y nombre del directorio actual donde \n");
    printf("se esta ejecutando el shell simular al prompt de bash\n ");
    printf("Despues leo la línea y paso a parsear\n");
    
}

void printCTRLC(){
    printf("Tengo una variable global que guarda pid del proceso que esta corriendo\n");
    printf("y en un handler chequeo si el pid del proceso que recibio un SIGINT no es el del propio shell\n");
    printf("Con un contador voy chequeando la cantidad de veces que se le ha hecho SIGINT a ese proceso\n");
    printf("y a la segunda vez que el proceso decide ignorar esa señal le mando un SIGKILL con kill(SIGKILL,piddelproceso)\n");
}
void printSpaces(){
    printf("Yo siempre quito los espacios y me quedo con la lista de tokens que me quedan\n");
    printf("Asi que no influye la cantidad de espacios que reciba como entrada\n");   
}


void printHelp(int option){
    if (option == 0){
        
    }
    switch (option)
    {
    case 0:
        printHelpMain();
        break;
    case 1:
        printCTRLC();
    default:
        break;
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