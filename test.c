#include <unistd.h>


int main(){
    char* argument_list[] = {"aa","aa",NULL};
    execvp("./PMan.o", argument_list);
}