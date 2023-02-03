#ifndef CONSTANTS_INCLUDED
#define CONSTANTS_INCLUDED

#define MAX_COMMAND_LEN 8 // no specification were given in assignment !
#define MAX_ARG_LEN 300 // no specification were given in assignment !
#define RUNNING 1

struct Command // a command and its arg will be stored in an struct
{
    char com[MAX_COMMAND_LEN];
    char arg[MAX_ARG_LEN];
    char execvp_args[MAX_COMMAND_LEN][MAX_ARG_LEN];
};

#endif