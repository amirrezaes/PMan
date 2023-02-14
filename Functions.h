#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include "Constants.h"
#include "linkedlist.h"
/* ^^ these are the include guards */

/* Prototypes for the commands */


//starts a process on background
void bg(struct Command *);

// takes two linked list, one for running and one for dead childs and prints them
void bglist(List *Children);
/* kills a process on background*/
void bgkill(char arg[], List *Children);

/* stops a process on background*/
void bgstop(char arg[]);

/* resumes a process on the background*/
void bgstart(char arg[]);

void pstat(char arg[]);

#endif