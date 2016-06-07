#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>

#define BUFSIZE 256

/* 
This program reads its stdin, converts the lower case of
the input to upper case, and writes this to stdout.
*/

void upper_string(char *string)
{
   while(*string)
   {
       if ( *string >= 'a' && *string <= 'z' )
       {
          *string = *string - 32;
       }
       string++;
   }
}

int main(int argc, char const *argv[])
{
	char readbuffer[BUFSIZE];

	setbuf(stdout, NULL); //disable buffering

	for(;;)
	{
		fgets(readbuffer, BUFSIZE, stdin);		/* read */
		//modify string
		upper_string(readbuffer);
		if (printf("%s", readbuffer) < 0)
		{
			perror("*** ERROR: writing to pipe failed");
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}