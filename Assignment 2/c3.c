#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

#define BUFSIZE 256

/*
This program reads its stdin and writes this to stdout
with a line number prepended (i.e. added to the beginning)
*/
void prepend(char* s, const char* t)
{
    size_t len = strlen(t);
    size_t i;

    memmove(s + len, s, strlen(s) + 1);

    for (i = 0; i < len; ++i)
    {
        s[i] = t[i];
    }
}

int main(int argc, char const *argv[])
{
	char readbuffer[BUFSIZE]; 
	int i = 0;
	char writebuffer[BUFSIZE];

	setbuf(stdout, NULL); //disable buffering

	for(;;)
	{
		fgets(readbuffer, BUFSIZE, stdin);
		i++; //increment line number
		sprintf(writebuffer, "%i %s", i, readbuffer); //modify string
		
		//write modified string to stdout
		if (printf("%s", writebuffer) < 0)
		{
			perror("*** ERROR: pipe write failed");
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}