#include <unistd.h>
#include <string.h>
#include "Functions.h"
#include "Constants.h"

int bg(struct Command *com){
    char *argument_list[MAX_COMMAND_LEN];
    for(int i=0; i<MAX_COMMAND_LEN; i++){
        strcat(argument_list, com->execvp_args[i]);
    }
    int resutl = execvp(com->arg, argument_list);
    return resutl;
}