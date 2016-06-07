#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>


#define BUFSIZE 256

/* 
This program repeatedly prompts the user for input, 
reads this input in and writes it to stdout. You may send your
prompts to stderr.
*/

int main(int argc, char const *argv[])
{
	char message[BUFSIZE];
	setbuf(stdout, NULL); //disable buffering
	
	for(;;)
	{
		int ttyfd = open("/dev/tty", O_RDWR);
		write(ttyfd, "Please enter the next line of input: ", 37);
		fgets(message,BUFSIZE,stdin); //read chars from stdin
		
		if(strcmp(message,"quit\n") == 0)
		{
			return 0;
		}

		if(message != NULL) //check user entered text
		{
			/* Send "string" through the output side of pipe */
			if (printf("%s", message) < 0)
			{
				perror("*** ERROR: pipe write failed");
				exit(EXIT_FAILURE);
			}			
		}
		usleep(100); //ensure other processes finish before next prompt
	}
	return 0;
}