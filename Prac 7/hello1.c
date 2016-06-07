/* hello1.c
 *	purpose	 show the minimal calls needed to use curses
 *	outline  initialize, draw stuff, wait for input, quit
 */

#include	<stdio.h>
#include	<ncurses.h>
#include	<string.h>

int main(int argc, char *argv[])
{
	initscr() ;		/* turn on curses	*/

				/* send requests	*/
	clear();			/* clear screen	*/
	
	char *myStr;

	if (argc < 2)
		myStr = "Hello, world";
		//addstr("Hello, world");		/* add a string	*/
	else
		myStr = argv[1];
		//addstr(argv[1]);		/* add a string	*/
	while(1)
	{
		move(10,20);			/* row10,col20	*/
		addstr(myStr);
		move(LINES-1,0);		/* move to LL	*/
		refresh();
		sleep(1);
		clear();
		move(LINES-1,0);		/* move to LL	*/
		refresh();
        sleep(1);
	}
	

	//refresh();		/* update the screen	*/
	//getch();		/* wait for user input	*/

	endwin();		/* turn off curses	*/
	return 0;
}
