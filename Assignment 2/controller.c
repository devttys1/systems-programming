#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

/*
This program implements the controller. It sets up
pipes for the children to communicate, and then invokes the three
programs to perform the tasks.
*/

#define NUM_CHILD 2
#define BUFSIZE 256
#define READ_PIPE 0
#define WRITE_PIPE 1


int main(int argc, char const *argv[])
{
	int pipefd1[2], pipefd2[2];
	int pipe1, pipe2;
	pid_t w;
	int status;

	pipe1 = pipe(pipefd1);
	if (pipe1 == -1)
	{
		perror("*** ERROR: creating pipe failed\n");
		exit(EXIT_FAILURE);
	}

	pipe2 = pipe(pipefd2);
	if (pipe2 == -1)
	{
		perror("*** ERROR: creating pipe failed\n");
		exit(EXIT_FAILURE);
	}

	pid_t pid1 = fork(); //fork process for c1
	if (pid1<0)
	{
		perror("*** ERROR: forking child process failed\n");
		exit(EXIT_FAILURE);
	}
	else if (pid1 == 0) //process is child
	{
		int fd;
		close(STDOUT_FILENO);
		if((fd = dup(pipefd1[WRITE_PIPE])) < 0)
		{
			perror("*** ERROR: pipe error");
			exit(EXIT_FAILURE);
		}
		
		char* args[] = {"./c1", NULL}; //store arguments in vector
		
		if (execv(args[0], args) < 0) /* execute the c1 binary  */
		{     
        	perror("*** ERROR: exec failed\n");
            exit(EXIT_FAILURE);
        }	
	}

	pid_t pid2 = fork(); //fork process for c2
	if (pid2<0) //fork error
	{
		perror("*** ERROR: forking child process failed\n");
		exit(EXIT_FAILURE);
	}
	else if (pid2 == 0) //process is child
	{
		int fd1, fd2;
		close(STDIN_FILENO);
		if((fd1 = dup(pipefd1[READ_PIPE])) < 0)
		{
			perror("*** ERROR: pipe error");
			exit(EXIT_FAILURE);
		}

		close(STDOUT_FILENO);
		if((fd2 = dup(pipefd2[WRITE_PIPE])) < 0)
		{
			perror("*** ERROR: pipe error");
			exit(EXIT_FAILURE);
		}
		
		char* args[] = {"./c2", NULL}; //store arguments in vector

		if (execv(args[0], args) < 0) /* execute the c2 binary  */
		{     
        	perror("*** ERROR: exec failed\n");
            exit(EXIT_FAILURE);
        }
	}


	pid_t pid3 = fork(); //fork process for c3
	if (pid3<0)
	{
		perror("*** ERROR: forking child process failed\n");
		exit(EXIT_FAILURE);
	}
	else if (pid3 == 0) //if child process
	{
		int fd;
		close(STDIN_FILENO);
		if((fd = dup(pipefd2[READ_PIPE])) < 0)
		{
			perror("*** ERROR: pipe error");
			exit(EXIT_FAILURE);
		}
		char* args[] = {"./c3", NULL}; //store arguments in vector
		
		if (execv(args[0], args) < 0) /* execute the c3 binary  */
		{     
        	perror("*** ERROR: exec failed\n");
            exit(EXIT_FAILURE);
        }
	}

	//Parent now executes
	//Parent waits for children
		do 
		{
			w = waitpid(pid1, &status, WUNTRACED | WCONTINUED); //Parent waits for child1 to 
            if (w == -1) 
            { 
            	perror("waitpid"); 
            	exit(EXIT_FAILURE); 
            }

            if (WIFEXITED(status)) //child1 exited
            {
                printf("Child1 exit code: %d\n", WEXITSTATUS(status));
                //send SIGTERM to remaining children
				kill(pid2, SIGTERM);
				kill(pid3, SIGTERM);

				for(int i=0; i<NUM_CHILD; i++)
				{
					wait(&status); /* wait for child to exit, and store child's exit status */
             		printf("Child%i exit code: %d\n", i+2, WEXITSTATUS(status));
				}
            } 
            else if (WIFSIGNALED(status)) 
            {
                printf("killed by signal %d\n", WTERMSIG(status));
            } 
            else if (WIFSTOPPED(status)) 
            {
                printf("stopped by signal %d\n", WSTOPSIG(status));
            } 
            else if (WIFCONTINUED(status)) 
            {
                printf("continued\n");
            }
        } 
        while (!WIFEXITED(status) && !WIFSIGNALED(status));
        exit(EXIT_SUCCESS);
}
