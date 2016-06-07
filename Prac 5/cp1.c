/** cp1.c
 *     version 1 of cp - uses read and write 
 *     with tunable buffer size
 *
 *     usage: cp1 src dest
 */
#include        <stdio.h>
#include        <unistd.h>
#include        <fcntl.h>
#include        <sys/stat.h>
#include        <string.h>

#define BUFFERSIZE      4096
#define COPYMODE        0644

void oops(char *, char *);
int main(int ac, char *av[])
{
    struct stat statbuf;
    int     in_fd, out_fd, n_chars;
    char    buf[BUFFERSIZE];
    char currentPath[FILENAME_MAX];
                                                /* check args   */
    if (ac != 3 ){
        fprintf( stderr, "usage: %s source destination\n", *av);
        return 1;
    }
                                                /* open files   */

    if ((in_fd=open(av[1], O_RDONLY)) == -1)
        oops("Cannot open ", av[1]);

    if(stat(av[2], &statbuf) == -1){
      //perror("stat");
      //return 1;
    }

    if(S_ISDIR(statbuf.st_mode))
    {
        printf("Destination is a directory\n");
        *currentPath = '\0';
        strcat(currentPath, av[2]);
        strcat(currentPath, "/");
        strcat(currentPath, av[1]);
        printf("saving to %s\n", currentPath);
        if ((out_fd=creat(currentPath, COPYMODE)) == -1)
            oops( "Cannot creat", av[2]);
    }
    else
    {
        printf("saving to %s\n", av[2]);
        if ((out_fd=creat(av[2], COPYMODE)) == -1)
            oops("Cannot creat", av[2]);
    }

                                                /* copy files   */
while ((n_chars = read(in_fd , buf, BUFFERSIZE)) > 0 )
        if (write(out_fd, buf, n_chars) != n_chars )
                oops("Write error to ", av[2]);
        if (n_chars == -1)
                oops("Read error from ", av[1]);

                                                /* close files  */

 if (close(in_fd) == -1 || close(out_fd) == -1)
                oops("Error closing files","");
}

void oops(char *s1, char *s2)
{
        fprintf(stderr,"Error: %s ", s1);
        perror(s2);
        //exit(1);
}