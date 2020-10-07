#ifndef LINKEDLISTH
#define LINKEDLISTH
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "mylib.h"
#define __SAFE_ALLOCATED_POINTER__(X) if (X == NULL) exit(1);


typedef struct background{
    int pid;
    int gpid;
    STRING name;
    int number;
    
}background;


typedef struct node
{
    background data;
    struct node* next;
    struct node* prev;
    
}node;

typedef struct list
{
    node* head;
    node* tail;
    unsigned int size;

}list;

list init_list();
void append(list* _lista ,background _value);
background dequeue(list*_lista);
background popend(list* _lista);
void  clear(list* _lista);
background get(list* _lista,int index);
node* getnode(list* _lista,int index);
void removeat(list* list,int index);
void print_last_bg(list* lista);
void print_jobs(list* lista);
int remove_number(list* lista,int number);
void remove_pid(list* lista,int pid);
#endif // !LINKEDLISTH


