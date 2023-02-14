#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include "Constants.h"
#include "linkedlist.h"
#include "Functions.h"

struct node {
  pid_t pid;
  char path[MAX_PATH_LEN];
  struct node * next;
};

struct list {
  Node * head; 
};

Node * createnode(pid_t data, char path[]);

Node * createnode(pid_t data, char path[]){
  Node * newNode = malloc(sizeof(Node));
  if (!newNode) {
    return NULL;
  }
  newNode->pid = data;
  strcpy(newNode->path, path);
  newNode->next = NULL;
  return newNode;
}

List * makelist(){
  List * list = malloc(sizeof(List));
  if (!list) {
    return NULL;
  }
  list->head = NULL;
  return list;
}

void display(List * list) {
  int count = 0;
  int p_status;
  Node * current = list->head;
  if(list->head == NULL) return;
  
  for(; current != NULL; current = current->next) {
    int pid=waitpid(current->pid, &p_status, WNOHANG);
    if(pid == -1) printf("wait() error");
    if(kill(current->pid, 0)==0 || WIFCONTINUED(p_status)){
      printf("%d: %s\n", current->pid, current->path);
      count++;
    }
    else if(WIFSIGNALED(p_status)){
      printf("Process %d was killed\n", current->pid);
      delete(current->pid, list);
    }else if (WIFEXITED(p_status)) {
      printf("Process %d exits\n", current->pid);
      delete(current->pid, list);
    } else{
    printf("%d: %s\n", current->pid, current->path);
    count++;
    }
  }
  printf("Total background jobs: %d\n", count);
}

void add(pid_t data, char path[] ,List * list){
  Node * current = NULL;
  if(list->head == NULL){
    list->head = createnode(data, path);
  }
  else {
    current = list->head; 
    while (current->next!=NULL){
      current = current->next;
    }
    current->next = createnode(data, path);
  }
}

void delete(pid_t data, List * list){
  Node * current = list->head;            
  Node * previous = current;           
  while(current != NULL){           
    if(current->pid == data){      
      previous->next = current->next;
      if(current == list->head)
        list->head = current->next;
      free(current);
      return;
    }                               
    previous = current;             
    current = current->next;        
  }                                 
}                                   

void reverse(List * list){
  Node * reversed = NULL;
  Node * current = list->head;
  Node * temp = NULL;
  while(current != NULL){
    temp = current;
    current = current->next;
    temp->next = reversed;
    reversed = temp;
  }
  list->head = reversed;
}
//Reversing the entire list by changing the direction of link from forward to backward using two pointers
void reverse_using_two_pointers(List *list){
    Node *previous = NULL;
    while (list->head)
    {
        Node *next_node = list->head->next; //points to second node in list
        list->head->next = previous;//at initial making head as NULL
        previous = list->head;//changing the nextpointer direction as to point backward node 
        list->head = next_node; //moving forward by next node
    }
    list->head=previous;
}
void destroy(List * list){
  Node * current = list->head;
  Node * next = current;
  while(current != NULL){
    next = current->next;
    kill(current->pid, SIGKILL);
    free(current);
    current = next;
  }
  free(list);
}
