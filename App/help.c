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
    printf(KEYWORDCOLOR,"help:","Muestra una ayuda explicando como funciona el shell\n");
    printf(KEYWORDCOLOR,"background:","Nuesto shell admite tener procesos en background con &  y despues regresarlos al foreground con fg\n"); 
    printf("por ejemplo ping localhost & es totalmente valido\n");
    printf("Comandos built-in:\n");
    printf(BUILTINCOLOR,"help",":muetra esta ayuda \n");
    printf(BUILTINCOLOR,"cd",":cambia de directorio para info escribe help cd\n");
    printf(BUILTINCOLOR,"true",":retorna o al exitstatus\n");
    printf(BUILTINCOLOR,"false",":retona 1 al exitstatus\n");
    printf(BUILTINCOLOR,"fg","fg solo retorna el ultimo jobs que se puso en bg fg<id> envia el proceso\n");
    printf("al foreground\n");
    printf(BUILTINCOLOR,"jobs:","lista los procesos que estan corriendo en bg a travez de una linked list que uso como cola\n");
    printf("escriba help jobs para mas info\n");
    printf(BUILTINCOLOR,"history:imprime los ultimos 10 comandos ejecutados haciendo read del file History\n");
    printf("escribe help history para mas info\n");
    printf(BUILTINCOLOR,"again:","vuelve a ejecutar el comando <number> que esta guardado en en History \n");
    
    
    printf("Idea general de como funciona el help:\n");
    printf("Lo primero que hago es inicializar las variables que uso y printar el logo de mi shell\n");
    printf("aqui activo los handler para SIGINT y SIGCHILD.El handler para SIGCHILD lo que hace es controlar que\n");
    printf("no se quede ningun proceso zombie muy util para cuando se hace bg\n");
    printf("Printeo en mi prompt el user login hostname y nombre del directorio actual donde \n");
    printf("se esta ejecutando el shell similar al prompt de bash\n ");
    printf("Despues leo la línea y paso a parsear \n");
    printf("En el parser primeramente ignoro los # y los saltos de linea y luego voy haciendo split por los ;\n");
    printf("para procesar los && y los || primeramente creo una variable para chequear el exitstatus de un proceso\n");
    printf("Luego separo mi linea por && y ejecuto la siguiente si el exit status de la primera fue SUCESS \n");
    printf("Luego separo por || y ejecuto la siguiente si el exit status de la anteriro fue NOTSUCESS \n ");
    printf("Ahora separo por | y voy guardando el pipe de salida de cada comando para ponerlo como pipe de entrada del otro\n");
    printf("Ahora paso a ejecutar un comando\n");
    printf("Tome como decision a algunos comandos built-in hacerle fork como history help y jobs porque me permitian \n");
    printf("poder hacer comandos como history | less ,help > u.txt,history | head -2 | wc -l \n");
    printf("a otros no les vi funcionalidad alguna y por eso no se los hice como exit cd y fg\n");
    printf("Entonces primero compruebo que no sea ningun comando buil-in de los que no hago fork\n");
    printf("En caso contrario hago pid=fork dentro de if(!pid) busca a ver si tiene < > >> en cuyo caso paso a crear o leer los files\n");
    printf("para que luego funcione cuando con execvp ejecute el comando\n");
    printf("aqui tambien chequeo los comandos built-in que hago fork en cuyo caso no llamo a execvp\n");
    printf("Si el proceso que se esta ejecutando tengo que mandarlo para el bg le asigno al grouppid de los procesos del\n");
    printf("background de esa linea en caso de que el sea el primero si gpid = pid\n");
    printf("le hago wait al proceso hijo solo si no va para el bg y comprueba su estatus cuando termina con una variable\n");

    
    
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
void printFG(){
    printf("Cuando se ejecuta el comando fg si me lo pasas id de la lista procesos saco a esa linea de la lista\n");
    printf("De lo contrario con fg saca al ultimo proceso que se puso en background que en mi implementacion\n");
    printf("es sacar el tail de mi linkedlist.Ya una vez que tenga el comando que voy a volver a fg hago lo siguiente:\n");
    printf("activo el handler para los procesos en background y actualizo el current pid como el pid del grupo del los\n");
    printf("procesos que voy a poner en el fg , luege con un do while voy haciendo wait a cada proceso a travez de su group id\n");
    printf("mientras tengan procesos pendientes por sacar \n");
    
}
void printBG(){
    printf("Cuando una linea se va ejecutar en background yo le asigno a cada proceso que se ejecute un mismo grouppid.\n");
    printf("Tengo una linked list con el tipo background  que guarda para cada linea que se va a ejecutar en background \n");
    printf("La cantidad de procesos que son y el gpid de ellos asi como el id en su lista de background process \n");
    printf("Luego printeo en console el id del background process list y su id de grupo\n");
    printf("Tengo una varibale global para saber si la linea esta en bg o no\n");
}
void printJobs(){
    printf("\n");
    printf("Tengo una linkedlist que funciona como cola donde voy guardando los jobs que tengo en el bg\n\n");
    printf("Cada vez que meto a un comando en la lista jobs imprimo en consola el id que le toca en la lista asi como el gpid que le asigne \n");
    printf("Una vez que un comando termina en bg automaticamente este es removido de la lista jobs\n");
    printf("Esto lo chequeo con un handler para comprobar procesos que se queden zombies o sea los procesos\n"); 
    printf("cuya ejecución está completa pero todavía tiene una entrada en la tabla de procesos\n");
    printf("mi cola de proceso en bg usa los metodos bg_jobs que devuelve un background b que contiene el id gpid name y cantidad\n");
    printf("de procesos y remove_number para sacar dado un id de lista el background de la lista\n.");
}
void printCD(){
    printf("Con chdir(directory name) cambio de directorio y se no fue exitoso retorno error\n");

}

void printHelp(int option){
    
    switch (option)
    {
    case 0:
        printHelpMain();
        break;
    case 1:
        printCTRLC();
    case 2:
        printSpaces();
        break;
    case 3:
        printFG();
        break;
    case 4:
        printBG();
        break;
    case 5:
        printCD();
        break;
    case 6:
        printJobs();
        break;                    
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