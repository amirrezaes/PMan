#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "Constants.h"
#include "Functions.h"
#include "linkedlist.h"

/*
 * Function: get_commnad
 *
 *   gets input command and passes it to parsing func
 *
 *   com:  pointer to the struct which will hold the command 
 *   returns: void
 */
int get_commnad(struct Command *com);

/*
 * Function: parse_command
 *
 *   extracts the commad name and args and adds them to the struct
 *
 *   com: pointer to the struct which will hold the command
 *   raw_command: pointer to the input string which will be parsed 
 *   returns: void
 */
void parse_command(struct Command *com, char *raw_command);


/*
 * Function: run_command
 *
 *   runs commands based of the inputs
 *
 *   com: pointer to the struct which will hold the command
 *   Childs: pointer to the linked list of childs 
 *   returns: void
 */
void run_command(struct Command *com, List *Childs);

int main(int argc, char *argv[])
{
    //struct Command com;
    List * Childs = makelist(); // taken from https://github.com/skorks/c-linked-list.git with some changes
    while(RUNNING){
        struct Command com;
        if(get_commnad(&com)){
            //printf("command: %s arg: %s\n", com.com, com.arg);
            //for(int i=0; i<3; i++) printf("external args: %s\n",com.execvp_args[i]);
            run_command(&com, Childs);
        }
    }
}


void run_command(struct Command *com, List *Childs){
    if(strcmp(com->com, "bg")==0){
        pid_t child_pid = fork();
        if(child_pid == 0){ // will run by child
            bg(com);
        }
        else{ // will run by parent
            int status;
            waitpid(child_pid, &status, WNOHANG); // checking if start was successful
            if(status > 0) add(child_pid, com->arg, Childs);
        }

    }

    else if(strcmp(com->com, "bglist\n")==0){
        bglist(Childs);
    }
    else if(strcmp(com->com, "bgkill") == 0){
        bgkill(com->arg, Childs);
    }
    else if(strcmp(com->com, "bgstop") == 0){
        bgstop(com->arg);
    }
    else if(strcmp(com->com, "bgstart") == 0){
        bgstart(com->arg);
    }
    else if(strcmp(com->com, "pstat") == 0){
        pstat(com->arg);
    }
    else if(strcmp(com->com, "clear\n") == 0){ // custom stuff
        system("clear");
    }
    else if(strcmp(com->com, "bgkillall\n") == 0){
        destroy(Childs);
        Childs = makelist();
    }
    
    else if(strcmp(com->com, "exit\n") == 0){
        destroy(Childs);
        exit(0);
    }
    else{
        printf("Worng command\n");
    }
}


int get_commnad(struct Command *com){
    char temp_inp[MAX_COMMAND_LEN + MAX_ARG_LEN]; // holding full command before it gets parsed
    printf("PMan: >");
    fgets(temp_inp, MAX_COMMAND_LEN+MAX_ARG_LEN, stdin); // fgets() seems to be safer than gets()
    if(strlen(temp_inp)<3) return 0;
    else parse_command(com, temp_inp);
    return 1;
}


void parse_command(struct Command *com, char *raw_command){
    char *temp; // temp part holder
    int temp_size = 0;
    int index = 1;
    temp = strtok(raw_command, " ");
    strcpy(com->com, temp); // the local command
    temp += strlen(com->com)+1;
    if(strlen(temp)==0) return;
    temp = strtok(temp, " ");
    strcpy(com->arg, temp); // the args or external commands
    if(com->arg[strlen(com->arg)-1] =='\n') com->arg[strlen(com->arg)-1] = 0;
    strcpy(com->execvp_args[0], temp); // C-style argument passing with name of the file at first
    temp += strlen(com->arg)+1;
    temp_size = strlen(temp);
    while(temp_size > 0){ // external args for external command
        temp = strtok(temp, " ");
        strcpy(com->execvp_args[index], temp);
        temp += strlen(com->execvp_args[index])+1;
        temp_size -= strlen(com->execvp_args[index])+1;
        index++;
    }
    com->execvp_args[index-1][strlen(com->execvp_args[index-1])-1] = 0; //removing the newline char
    strcpy(com->execvp_args[index], "\0"); // null terminated list
}