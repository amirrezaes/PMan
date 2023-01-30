#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_COMMAND_LEN 8
#define MAX_ARG_LEN 300
#define RUNNING 1

struct Command // a command and its arg will be stored in an struct
{
    char com[MAX_COMMAND_LEN];
    char arg[MAX_ARG_LEN];
};

/*
 * Function: get_commnad
 *
 *   gets input command and passes it to parsing func
 *
 *   com:  pointer to the struct which will hold the command 
 *   returns: void
 */
void get_commnad(struct Command *com);

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
    struct Command com;
    while(RUNNING){
        get_commnad(&com);
        printf("command: %s arg: %s", com.com, com.arg);
    }
}

void get_commnad(struct Command *com){
    char temp_inp[MAX_COMMAND_LEN + MAX_ARG_LEN]; // holding full command before it gets parsed
    printf("PMan: >");
    fgets(temp_inp, MAX_COMMAND_LEN+MAX_ARG_LEN, stdin); // fgets() seems to be safer than gets()
    parse_command(com, temp_inp);
}

void parse_command(struct Command *com, char *raw_command){
    char *temp; // temp part holder
    temp = strtok(raw_command, " ");
    strcpy(com->com, temp);
    temp += strlen(com->com)+1;
    strcpy(com->arg, temp);
}