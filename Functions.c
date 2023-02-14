#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "Functions.h"
#include "Constants.h"
#include "linkedlist.h"


/// @brief starts a background process with given args for it
/// @param com pointer to the struct contatining input
void bg(struct Command *com){
    char* argument_list[MAX_COMMAND_LEN] = {NULL}; // null terminated array
    for(int i=0; i<MAX_COMMAND_LEN; i++){
        argument_list[i] = strdup(com->execvp_args[i]);
        if(strcmp(argument_list[i], "") == 0){
            argument_list[i] = NULL;
            break;
        }
    }
    if(execvp(com->arg, argument_list) < 0){
        exit(-1); // unsecsessful start
    }
}


/// @brief prints all the alivea and dead children
/// @param Children 
void bglist(List *Children){
    display(Children);
}


/// @brief kills the given PID
/// @param arg PID
/// @param Children linked list of children
void bgkill(char arg[], List *Children){
    if(kill(atoi(arg), SIGKILL) == 0){
        printf("\rProcess %s killed\n", arg);
        delete(atoi(arg), Children);
    }else{
        printf("\rCould not kill the process %s", arg);
    }
}

/// @brief sends stop signal to given child
/// @param arg PID
void bgstop(char arg[]){
    if(kill(atoi(arg), SIGSTOP) == 0){
        printf("Process %s stopped\n", arg);
    }else{
        printf("Could not stop the process %s", arg);
    }
}


/// @brief resumes the stopped child
/// @param arg PID
void bgstart(char arg[]){
    if(kill(atoi(arg), SIGCONT)==0){
        printf("Process %s Continued\n", arg);
    }else{
        printf("Could not start the process %s", arg);
    }
}

/// @brief parses and prints proc/stat and proc/status files 
/// @param arg 
void pstat(char arg[]){
    char filename[50]; // this will be enought to span all file name lenghts
    int len = strlen(arg), pid, finished=0; //we will use this to get last two lines of proc/status
    if( arg[len-1] == '\n') arg[len-1] = 0;
    sprintf(filename, "/proc/%s/stat", arg);
    FILE *f = fopen(filename, "r");
    char comm[MAX_PATH_LEN], state, dump[100];
    unsigned long int utime, stime;
    long int rss;
    fscanf(f, "%d %s %c", &pid, comm, &state);
    for(int i=0; i<10; i++) fscanf(f, "%s", dump); // this data not needed
    fscanf(f, "%lu %lu", &utime, &stime);
    for(int i=0; i<8; i++) fscanf(f, "%s", dump); // this data not needed
    fscanf(f, "%ld", &rss);
    printf("command: %s \nstatus: %c\nutime: %fs\nstime: %fs\nrss: %ld\n", comm, state, (float)utime/100, (float)stime/100, rss);
    fclose(f); // we are done with proc/stat
    sprintf(filename, "/proc/%s/status", arg);
    f = fopen(filename, "r");
    while(finished!=2){
        fgets(dump, 100, f);
        if(strstr(dump, "voluntary_ctxt_switches:")!=NULL || strstr(dump, "nonvoluntary_ctxt_switches:")!=NULL){
            printf("%s", dump);
            finished += 1;
        }
    }
}