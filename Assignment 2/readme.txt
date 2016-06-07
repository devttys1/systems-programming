**************************************
* 
* README
* Dale Matthews 17287757
* controller.c, c1.c, c2.c, c3.c 
*
**************************************

NAME
	controller -- program to execute 3 child processes and send data with pipes.

SYNOPSIS
	./controller

DESCRIPTION
	The controller will create 3 child processes, and 2 pipes.

    stdin > c1 > pipe1 > c2 > pipe2 > c3 > stdout

    c1, c2, and c3 must be located in the same directory as controller.

    To end the program, type 'quit'



	The following options are avaliable:

	none

NOTES
	c1 will prompt the user for input and send it to c2.
    c2 will convert lower case characters into uppercase and send to c3.
    c3 will prepend a line number and print to the terminal.

    Known limitations: The user input is limited by the buffersize which is 255 characters (not including NULL char)


EXAMPLE "./controller"

COMPILING
    To compile all run "make all". 
    Old binaries are removed before compiling.
    Uses gcc with gnu99 option.

//PSUEDOCODE
/* 
controller
----------
    create pipe1
        if failed 
            print error to stderr
            exit

    create pipe2
        if failed 
            print error to stderr
            exit

    fork process for c1
        if failed 
            print error to stderr
            exit
        if child process
            redirect stdout to pipe1
            exec c1
                if failed
                print error to stderr
                exit

    fork process for c2
        if failed 
            print error to stderr
            exit
        if child process
            redirect stdin to pipe1
            redirect stdout to pipe2
            exec c2
                if failed
                print error to stderr
                exit

    fork process for c3
        if failed 
            print error to stderr
            exit
        if child process
            redirect stdin to pipe2
            exec c3
                if failed
                print error to stderr
                exit

    if parent process
        wait for child1 to exit
            print exit status
            send sigterm to c2
            send sigterm to c3
            exit

c1
--
    prompt user for input (tty)
    read characters from stdin to buffer
    check input is not null
    if input is 'quit'
        exit
    write buffer to stdout

c2
--
    read from stdin
    convert lowercase char to uppercae
    write to stdout

c3
--
    read from stdin
    increment line number
    prepend line number to string
    write to stdout

*/

TESTING

Test Plan
---------

1. Test 2 lines of input text from terminal, with upper and lower case.

2. Type quit to check program exits, and child status is returned.

3. Compiling from makefile

4. Child binaries are not in same folder, or missing

5. Test each child alone ./c1, ./c2, ./c3



Results
-------
1.  $ ./controller 
    Please enter the next line of input: The Quick brown
    1 THE QUICK BROWN
    Please enter the next line of input: fox jumps over the lazy dog 
    2 FOX JUMPS OVER THE LAZY DOG                                       
    Please enter the next line of input: 

2. $ ./controller 
Please enter the next line of input: quit
Child1 exit code: 0
Child2 exit code: 0
Child3 exit code: 0

3. $ make all
rm -f c1 c2 c3 controller
gcc -Wall -g -std=gnu99 -Werror c1.c -o c1
gcc -Wall -g -std=gnu99 -Werror c2.c -o c2
gcc -Wall -g -std=gnu99 -Werror c3.c -o c3
gcc -Wall -g -std=gnu99 -Werror controller.c -o controller

4. $ ./controller 
*** ERROR: exec failed
: No such file or directory
*** ERROR: exec failed
: No such file or directory
child exited, status=1

5.
$ ./c1
Please enter the next line of input: test
test
Please enter the next line of input: test2
test2

$ ./c2
test
TEST
test2
TEST2

$ ./c3
test
1 test
test2
2 test2









