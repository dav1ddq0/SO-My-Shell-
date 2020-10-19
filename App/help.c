#include "help.h"

void printHelpMain(){
    printf(HELPIASCII,"'||         '||`\n");
    printf(HELPIASCII," ||          ||\n");
    printf(HELPIASCII," ||''|,.|''|,||'||''|,\n");
    printf(HELPIASCII," ||  ||||..|||| ||  ||\n");
    printf(HELPIASCII,".||  ||`|....||.||..|'\n");
    printf(HELPIASCII,"                ||   \n");
    printf(HELPIASCII,"               .||    \n");




    printf("Integrantes:"BLUE_B"David Orlando De Quesada Oliva y Javier Dominguez\n"RESET_COLOR);
    printf(RED_F"El ejecutable del proyecto es shell.out y con el script execute.sh se compila y ejecuta el proyecto\n"RESET_COLOR);
    printf(RED_F"Funcionalidades que implementamos:\n"RESET_COLOR);
    printf(KEYWORDCOLOR,"basic:","contempla los puntos del 1 al 8 que son las funcionalidades básicas del shell\n");
    printf(KEYWORDCOLOR,"multi-pipe:"," nuestro shell admite más de una tubería \npor ejemplo :ls -l | head -2 | wc -l es válido\n");
    printf(KEYWORDCOLOR,"spaces:","Admite cualquier cantidad de espacios entre los comandos y parámetros \nls  -l y ls         -l   | head      -2 son válidos\n");
    printf("para mayor información escriba:"RED_F" help spaces\n" RESET_COLOR);
    printf(KEYWORDCOLOR,"history:","El shell tiene un historial de comandos que permite imprimir los últimos 10 comandos\nSe guarda permanentemente en el archivo History\n");
    printf("para mayor información escriba:"RED_F" help history\n" RESET_COLOR);
    printf(KEYWORDCOLOR,"chain:"," Nuestro shell admite los operadores ; && ||\npor ejemplo :ls  && ls > a.txt ; ls -l || ls -l | head-2 && | wc -l es válido\n");
    printf(KEYWORDCOLOR,"ctrl+c:","Nuestro shell no se muere cuando das  ctrl+c y si estoy ejecutando un proceso hijo y decide ignorar el ctrl+c\nla segunda vez le mando un SIGKILL para que termine de ejecutarse\n");
    printf("para mayor información escriba:"RED_F" help ctrl+c\n" RESET_COLOR);
    printf(KEYWORDCOLOR,"help:","Muestra una ayuda explicando como funciona el shell\n");
    printf(KEYWORDCOLOR,"background:","Nuesto shell admite tener procesos en background con &  y despues regresarlos al foreground con fg\n"); 
    printf("por ejemplo ping localhost & es totalmente válido\n");
    printf("para mayor información escriba:"RED_F" help background\n" RESET_COLOR);
    printf(RED_F"Comandos built-in:\n"RESET_COLOR);
    printf(BUILTINCOLOR,"help",":muetra esta ayuda \n");
    printf(BUILTINCOLOR,"cd",":cambia de directorio\n");
    printf("para mayor información escriba:"RED_F" help cd\n" RESET_COLOR);
    printf(BUILTINCOLOR,"true",":retorna 0 al exitstatus\n");
    printf(BUILTINCOLOR,"false",":retona 1 al exitstatus\n");
    printf(BUILTINCOLOR,"fg",":fg solo retorna el último job que se puso en bg fg<id> envia el proceso\n");
    printf("al foreground\n");
    printf("para mayor información escriba:"RED_F" help fg\n" RESET_COLOR);
    printf(BUILTINCOLOR,"jobs",":lista los procesos que estan corriendo en bg a travez de una linked list que uso como cola\n");
    printf("para mayor información escriba:"RED_F" help jobs\n" RESET_COLOR);
    printf(BUILTINCOLOR,"history",":imprime los ultimos 10 comandos ejecutados haciendo read del file History\n");
    printf("para mayor información escriba:"RED_F" help history\n" RESET_COLOR);
    printf(BUILTINCOLOR,"again:","vuelve a ejecutar el comando <number> que esta guardado en el History \n");
    printf("para mayor información escriba:"RED_F" help again\n" RESET_COLOR);
    printf(BUILTINCOLOR,"exit",":sale del shell con exit(EXIT_SUCCESS)\n");

    
    
    printf(CYAN_F"Idea general de como funciona el shell que implementamos:\n\n"RESET_COLOR);
    printf("Lo primero que hacemos es inicializar las variables que uso y pintar en consola el logo del  shell\n");
    printf("asi como activar con signal  los handler para SIGINT y SIGCHILD\n");
    printf("El handler para SIGINT es el encargado de controla el Ctrl+C para que mi shell no se muera\n");
    printf("y cualquier proceso hijo que se ejecute si decide ignorar la señal de SIGINT la primera vez la ignore\n");
    printf("a la segunda ya le mando una señal de SIGKILL para matar el proceso\n");
    printf("Inicializo algunas estructuras que voy a usar con malloc y obtengo el login y hostname de la pc en la que\n ");
    printf("se esta ejecutando el shell para luego pintarlo en consola asi como el directorio actual el cual voy actualizando\n");
    printf("antes que se muestre nuevamente el prompt.Luego en cada iteracion del while 1 hago lo siguinete: \n");
    printf("actualizo el directorio actual para nuevamente pintarlo en consola junto al login y al hostname\n");
    printf("lee la línea que se escribió en el stdin y la guarda en un STRING line(Por comodidad me cree varios define entre ellos STRING=char*) \n");
    printf("luego actualizo el history con esa line\n");
    printf("ahora paso a parsear y ejecutar los comandos de la siguiente forma\n");
    printf("primeramente como ignoro donde aparece # en adelante ,quito los saltos de lineas y voy separando por ;\n");
    printf("como el operador ; me permite ejecutar varios comandos en una sola línea voy ejecutando uno a une las lineas que \n");
    printf("obtuve de separar por ; como si fueran independientes por eso me quedo con un STRING* inits que guarda cada linea\n");
    printf("resultado de hacer split por ; En mi implementacion por ejemplo ls -l ; ping localhost & como yo lo trato como dos\n");
    printf("linas distintas solo mando al bg a ping localhost tambien es valido ls -l &;ping localhost en cuyo caso solo mando al bg\n");
    printf("a ls -l.Por cada STRING de mi inits  paso a splitear por ands y por cada  ands resultado paso a splitear por ors\n");
    printf("para chequear los ands y los ors tengo una variable que guarda el exit statos del ultimo proceso que se ejecuto y segun el resultado \n");
    printf("si es 1 paso a ejecutar el próximo command de ors y de la salida de este veo si puedo ejecutar otra comando de ands en caso que sea 0\n");
    printf("esta parte creo que mejor se entiende en el código del método calling_execute que esta en command.c\n");
    printf("ahora por cada línea de ors separo por | y paso a ejecutar cada comando\n");
    printf("cada vez que ejecuto un comando me quedo con el file descritor de salida de cuando hice pipe y se lo paso como entrada\n");
    printf("al proximo comando a ejecutar de esta forma logro hacer multiples pipes\n");
    printf("al ejecutar un comando hago lo siguiente:\n");
    printf("primero si esa línea va para el fg entonces inicializo si aun no se ha hecho mi struct background \n");
    printf("que va el gpid de los proceso que estan en bg el id que le corresponde dentro de la lista de jobs y el name \n");
    printf("del comando al cual se le hizo fg\n");
    printf("verifico si el comando a ejecutar es un built-in de los que no le hago fork  de lo contrario\n");
    printf("hago fork verifico si hay < > >> y en cada caso hago:\n");
    printf("si < mando para el file descriptor fd_read_out el fd resultado de abrir el archivo \n");
    printf("si > o >> mando para el file descriptor fd_write_in el fd resultado de abrir el archivo \n");
    printf("en el código se aprecia mejor lo que hago en cada caso y que diferencias hay al abrir un file en caso de > , >>,<\n");
    printf("luego duplico el fd fd_read_out en la standard input y el fd en la standard output \n ");
    printf("en el código se ve como hago eso.Ahora verifico si el comando a ejecutar es un built-in de los que se le hace fork\n");
    printf("en caso contrario ejecuto el comando con execvp\n");
    printf("si el comando a ejecutar no va al bg le hago wait al proceso y guardo el exitstatus de su ejecución\n");
    printf("En caso contrario no hago wait y le asigno al proceso hijo un gpid que va a ser el mismo que van a tener\n");
    printf("los demás procesos de la línea que va al bg\n");

    printf(CYAN_F"Sobre algunas implementaciones:\n"RESET_COLOR);
    printf("Con el handler ZombiesHandler verifico si hay algun proceso que terminó pero sigue como entrada de la tabla de procesos(zombie)\n");
    printf("Esto es muy útil cuando mando un proceso al background y este finaliza asi puedo quitar los jobs de la jobsList \n ");
    printf("si se terminó el proceso que estaba en bg\n");
    printf("Tengo dos métodos fundamentales para splitear uno es string_tokenizer que separa por un char como'|','#' y el otro \n");
    printf("es parser que separa por STRING este lo uso sobre todo para los && y los ||\n");
    printf("Tomamos como decisión a algunos comandos built-in hacerle fork como history help y jobs porque me permitían \n");
    printf("poder hacer comandos como history | less ,help > u.txt,history | head -2 | wc -l \n");
    printf("a otros no les vi funcionalidad alguna y por eso no se los hice como exit cd y fg\n");
    
    
    
}

void printCTRLC(){
    printf("Tengo una variable global que guarda pid del proceso que está corriendo\n");
    printf("y en un handler chequeo si el pid del proceso que recibio un SIGINT no es el del propio shell\n");
    printf("Con un contador voy chequeando la cantidad de veces que se le ha hecho SIGINT a ese proceso\n");
    printf("y a la segunda vez que el proceso decide ignorar esa señal le mando un SIGKILL con kill(SIGKILL,piddelproceso)\n");
    printf("Para los procesos en background hago otro handler pues ellos estan en entro grouppid y tengo que redirigir la señal a ese\n");
    printf("grupo pues por defecto no la reciben asi que la primera vez   mando un kill(-gpid,SIGINT) y la segunda un kill(-gpid,SIGKILL)\n");
}
void printSpaces(){
    printf("Yo siempre quito los espacios y me quedo con la lista de tokens que me quedan\n");
    printf("Asi que no influye la cantidad de espacios que reciba como entrada\n"); 
}
void printFG(){
    printf("Cuando se ejecuta el comando fg si me  pasas id de la lista de procesos saco a esa linea de la lista\n");
    printf("De lo contrario con fg saca al ultimo proceso que se puso en background que en mi implementación\n");
    printf("es sacar el tail de mi cola.Ya una vez que tenga el comando que voy a volver a fg hago lo siguiente:\n");
    printf("activo el handler para los procesos en background y actualizo el current pid como el pid del grupo del los\n");
    printf("procesos que voy a poner en el fg , luege con un do while voy haciendo wait a cada proceso a travez de su group id\n");
    printf("mientras tengan procesos pendientes por sacar \n");
    printf("Luego quito del la lista de procesos en bg el correspondiente con el id que saque\n");
}
void printBG(){
    printf("Cuando una linea se va ejecutar en background yo le asigno a cada proceso que se ejecute un mismo grouppid.\n");
    printf("Tengo una linked list de tipo  background  que guarda para cada línea que se va a ejecutar en background \n");
    printf("La cantidad de procesos que son y el gpid de ellos asi como el id en su lista de background process \n");
    printf("Luego imprimo en consola el id del background process list y su id de grupo\n");
    printf("Tengo una variable global para saber si la línea está en bg o no\n");
}
void printJobs(){
    printf("Tengo una linkedlist que funciona como cola donde voy guardando los jobs que tengo en el bg\n\n");
    printf("Cada vez que meto a un comando en la lista jobs imprimo en consola el id que le toca en la lista asi como el gpid que le asigné \n");
    printf("Una vez que un comando termina en bg automaticamente este es removido de la lista jobs\n");
    printf("Esto lo chequeo con un handler para comprobar procesos que se queden zombies o sea los procesos\n"); 
    printf("cuya ejecución está completa pero todavía tiene una entrada en la tabla de procesos\n");
    printf("mi cola de proceso en bg usa los metodos bg_jobs que devuelve un background b que contiene el id gpid name y cantidad\n");
    printf("de procesos y remove_number para sacar dado un id de lista el background de la lista\n.");
}
void printCD(){
    printf("Con chdir(directory name) cambio de directorio y si no fue exitoso retorno error\n");

}

void printHistory(){
    printf("Nuestro comando history funciona de la siguiente manera:\n\n");
    printf("Nosotros guardamos los ultimos 10 comandos q se ejecutan en un archivo llamado History de forma permanente\n");
    printf("este archivo se actualiza cada vez que se ejecuta un comando de la siguiente manera:\n");
    printf("1- si aun no se ha ejecutado ningun comando hay q crear el History y agregar el comando\n");
    printf("2- si ya existe el History y hay menos de 10 comandos guardados es simplemente con un file descriptor\n");
    printf("movernos hasta el final de History y escribir el nuevo comando\n");
    printf("3- si ya existe el History y esta lleno (ya hay 10 comandos almacenados), lo que hacemos es renombrar el History");
    printf(" a OldHistory \ny usando 2 file descriptors con uno leemos de OldHistory y con el otro copiamos a partir del 2do comando hacia un nuevo History,\n");
    printf("luego agregamos el nuevo comando al final del archivo y eliminamos el OldHistory\n");
    printf("Como a history le hago fork tanto history > a.txt como history | cat | wc -l funcionan en el shell\n");
}

void printAgain(){
    printf("Leo la línea del history correspondiente al number que se le pasa a again\n");
    printf("luego ejecuto esa línea de la misma forma que ejecuto cualquier línea que leo  de la stdin\n");
}

void printHelp(int option){
    
    switch (option)
    {
    case 0:
        printHelpMain();
        break;
    case 1:
        printCTRLC();
        break;
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
    case 7:
        printHistory();
        break;
    case 8:
        printAgain();
        break;                            
    default:
        break;
    }
    
}