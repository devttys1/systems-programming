**************************************
* 
* README
* Dale Matthews 17287757
* replace.c 
*
**************************************

NAME
	replace -- replace strings in a text file.

SYNOPSIS
	replace filename [-f] from to [from] [to] ...

DESCRIPTION
	The replace utility is used to replace strings in a text file. 

	The following options are avaliable:

	filename
		The path and name of the text file to be modified.

	from
		The string to be replaced.

	to
		The replacement string.
	-f
		Replace the first occurance of a matched string only.

NOTES
	The replace utility works for files of any size, and strings of any length.
	The replace unility also work for any number of replacement strings.
	To insert a space use the ecscape character '\ '
	To insert special characters use escapes, eg to insert '*' use '\*'
	Known limitations: file size must be smaller than avaliable RAM.


EXAMPLE "replace.o -f /path/to/example.txt The THE a BB c $5"
EXAMPLE "replace.o /path/to/matlab.m % \*"


//PSUEDOCODE
/* 
    Main
    ----
	Check number of command line arguments is correct
    If not correct 
      	display usage text
      	end
    
    Open file specified in first argument in read only mode
    Find size of file
    Allocate memory for buffer
    Read file into buffer
    close file

    Look for -f switch
    If found
    	check remaining arguments is an even number
    		If not even
    			display usage text
      			end
    	call function str_replace with replaceAll = False for each pair of arguments
    	if modified
    		open file in write mode
    		write modified buffer to file
    		close file
    		end
    	else
    		print string not found
    		end

	If not found
		check remaining arguments is an even number
    		If not even
    			display usage text
      			end
		call function str_replace with replaceAll = True for each pair of arguments
    	if modified
    		open file in write mode
    		write modified buffer to file
    		close file
    		end
    	else
    		print string not found
    		end

	If wrong switch is found
		display usage text
      	end

    str_replace
    -----------
    if string is empty
        return
    if replaceAll = False
        search for replacement string in buffer
            if not found
                return
            else
                set modified flag
                allocate memory for modified string
                do replacement
        return modified string pointer
    else replaceAll = True
        search for replacement string in buffer
            if not found
                return
            else
                set modified flag
                do while replacement strings are found
                    allocate memory for modified string
                    do replacement
                end while
        return modified string pointer

*/

TESTING

Test Plan
---------

1. Test without -f, make sure all occurances are changed
2. Test with -f, make sure only the first occurance is changed
3. Test with multiple replacement strings
4. Test with non matching strings, make sure program does not crash
5. Test with wrong filename, check for error text
6. Test with wrong number of arguments, check for error text
7. Test with -x (invalid option), check for usage text
8. Test with empty file, check for error text
9. Test with a large file, check nothing overflows

Results
-------

1. $ ./replace.o examples/example.txt e E
Read 45 bytes from file examples/example.txt
Replaced 3 occurances.
Wrote 45 bytes to file examples/example.txt

2. $ ./replace.o examples/example.txt -f E e
Read 45 bytes from file examples/example.txt
Replaced first occurance only.
Wrote 45 bytes to file examples/example.txt

3. $ ./replace.o examples/example.txt dog bear brown yellow
Read 45 bytes from file examples/example.txt
Replaced 1 occurances.
Replaced 1 occurances.
Wrote 47 bytes to file examples/example.txt

4. $ ./replace.o examples/example.txt -f bear Fox
Read 45 bytes from file examples/example.txt
Replacement strings not found in file examples/example.txt

5. $ ./replace.o examples/wrongname.txt -f E e 
File examples/wrongname.txt does not exist

6. $ ./replace.o examples/example.txt -f E e X
Read 45 bytes from file examples/example.txt
USAGE: ./replace.o -f filename from to [from to] ...

7. $ ./replace.o examples/example.txt -x E e
Read 45 bytes from file examples/example.txt
-x is not a valid option.

8. $ ./replace.o examples/empty_file.txt F f
Read 0 bytes from file examples/empty_file.txt
examples/empty_file.txt is an empty file. Try again.

9. $ ./replace.o examples/matlab.m % \#
Read 4688 bytes from file examples/matlab.m
Replaced 1493 occurances.
Wrote 4688 bytes to file examples/matlab.m
