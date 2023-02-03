#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Constants.h"
#include "Functions.h"

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

int main(int argc, char *argv[])
{
    //struct Command com;
    while(RUNNING){
        struct Command com;
        if(get_commnad(&com)){
            printf("command: %s arg: %s\n", com.com, com.arg);
            for(int i=0; i<3; i++) printf("external args: %s\n",com.execvp_args[i]);
            bg(&com);
        }
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
    temp = strtok(temp, " ");
    strcpy(com->arg, temp); // the args or external commands
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