#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include "Constants.h"
/* ^^ these are the include guards */

/* Prototypes for the commands */


//starts a process on background
int bg(struct Command *);

/* lists processes running on background */
//void bglist();

/* kills a process on background*/
//int bgkill(char *arg);

/* stops a process on background*/
//int bgstop(char *arg);

/* resumes a process on the background*/
//int bgstart(char *arg);

//void pstat(char *arg);

#endif