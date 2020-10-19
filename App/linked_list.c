
#include "linked_list.h"


void print_last_bg(list* lista){
   if(lista->size>0){
      background l = lista->tail->data;
      printf(YELLOW_F"[%d]  %d\n" RESET_COLOR,l.id,l.gpid);
   }
}

void print_jobs(list* lista){
   node* n = lista->head;
   while (n!=NULL)
   {
      background bg =n->data; 
      printf(YELLOW_F"[%d]  %d   %s\n" RESET_COLOR,bg.id,bg.gpid,bg.name);
      n=n->next;
   }

}

void append(list* lista, background data)
{
   node* n = (node*)malloc(sizeof(node));
   n->data =data;
   
   if(lista->size == 0)
   {
      n->data.id=1;
      n->prev = NULL;
      n->next = NULL;
      lista->head = lista->tail = n;
   }
   else
   {
      n->data.id=lista->tail->data.id + 1;
      n->next = NULL;  
      n->prev = lista->tail;
      lista->tail->next = n;
      lista->tail = n;  
   }
   (lista->size)++;    
}


/* constructor of my list struct*/
list init_list()
{
    
   list l;
   l.head =NULL;
   l.tail =NULL;
   l.size=0;
   return l;
}

background popend(list* lista)
{
   node* currentTail = lista->tail;
   node* nextTail = currentTail->prev;
   nextTail->next=NULL;
   background valReturn =currentTail->data;
   lista->tail=nextTail;
   free(currentTail);
   lista->size--;
   return valReturn;
}

background dequeue(list* lista){
   node* actualHead = lista->head;
   node* nextHead = lista->head->next;
   lista->head =nextHead;
   actualHead->prev=NULL;
   background val = actualHead->data;
   free(actualHead);
   lista->size--;
   return val;
}
/* clear the list to defaul state*/
void clear(list* lista){
  
   if(lista->head!=NULL)
   {
      for (node* current = lista->head; current->next !=NULL; current=current->next){
         free(current);    
      }

      lista->head=NULL;
      lista->tail=NULL;
      lista->size=0;
   }
   
    
}

node* getnode(list* _lista,int index)
{
   int pos=0;
   for (node* i = _lista->head; i!= NULL; i=i->next)
   {
       if(pos==index)
       {
           return i;
       }
       pos++;
   }
   return NULL; 
} 
background get(list* lista,int index)
{
   return getnode(lista,index)->data;     
}

void remove_number(list* lista,int number){
   node* n = lista->head;
   int index=0;
   while (n!=NULL)
   {
      if(n->data.id==number){
         removeat(lista,index);
         
      }
      else
      {
         index++;
         n=n->next;
      }
      
   }

   
   
}

background bg_job(list* lista,int number){
   node* n = lista->head;
   int index=0;
   while (n!=NULL)
   {
      if(n->data.id==number){
         background bg=get(lista,index);
         return bg;
      }
      else
      {
         index++;
         n=n->next;
      }
      
   }

   
   
}
void remove_pid(list* lista,int pid){
   node* n = lista->head;
   int index=0;
   while (n!=NULL)
   {
      if(n->data.gpid==pid){
         removeat(lista,index);
         return;
      }
      else
      {
         index++;
         n=n->next;
      }
      
   }
   
}

void removeat(list* list,int index)
{
   
   if(index > 0 && list->size > 1)
   {
      node* n = getnode(list,index);
   
      if(n == list->tail)
      {
         n->prev->next = NULL;
        list->tail = n->prev; 
      }
      else
      {
        n->prev->next = n->next;      
        n->next->prev = n->prev;
      }
      
      free(n);
   }

   if(index == 0 && list->size >= 1)
   {
      node* n = list->head;
      if(list->size == 1)
      {         
         list->tail=list->head = NULL;
      }
      else
      {
         list->head = list->head->next;
      }
      
      free(n);
   }
   list->size--;
}

