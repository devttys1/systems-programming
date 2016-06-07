#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//#define DEBUG //Uncomment this line to display debugging text

//function to print help text
void usage(char *p){
  fprintf(stderr, "USAGE: %s -f filename from to [from to] ...\n", p);
}
 
char *str_replace(const char *string, const char *substr, const char *replacement, int* modified, int replaceAll){
  char *tok = NULL;
  char *newstr = NULL;
  char *oldstr = NULL;
  char *head = NULL;
  long count = 0; 
 
  //if either substr or replacement is NULL, duplicate string and let caller handle it
  if(substr == NULL || replacement == NULL) 
    return strdup(string);
  newstr = strdup(string);
  head = newstr;
	if (!replaceAll)//only replace 1 occurance	
  { 
		if((tok = strstr(head, substr)) == NULL) //if no match was found
  	{
    	free(oldstr);
    	return newstr; //return original string
  	} 
		oldstr = newstr;
  	*modified = 1; //set modified flag
  	newstr = malloc(strlen(oldstr) - strlen(substr) + strlen(replacement) + 1); //allocate memory for replacement
  	if(newstr == NULL) //failed to allocate memory, free old string and return NULL
    {
    	free(oldstr);
    	return NULL;
  	}
    //Do replacement
    memcpy(newstr, oldstr, tok - oldstr);
    memcpy(newstr + (tok - oldstr), replacement, strlen (replacement));
    memcpy(newstr + (tok - oldstr) + strlen(replacement), tok + strlen(substr), strlen(oldstr) - strlen(substr) - (tok - oldstr));
    memset(newstr + strlen(oldstr) - strlen(substr) + strlen(replacement), 0, 1);
    //move back head right after the last replacement
    head = newstr + (tok - oldstr) + strlen(replacement);
    free(oldstr);
    printf("Replaced first occurance only.\n");
    return newstr;
	}
  while((tok = strstr(head, substr)) && replaceAll) //replace all occurances
  {
    count++;
    oldstr = newstr;
    newstr = malloc(strlen(oldstr) - strlen(substr) + strlen(replacement) + 1); //calculate size of new string and allocate memory
    if(newstr == NULL){ //failed to allocate memory, free old string and return NULL
      free(oldstr); //free memory
      return NULL;
    }
    //Do replacement
    memcpy(newstr, oldstr, tok - oldstr);
    memcpy(newstr + (tok - oldstr), replacement, strlen(replacement));
    memcpy(newstr + (tok - oldstr) + strlen(replacement), tok + strlen(substr), strlen(oldstr) - strlen(substr) - (tok - oldstr));
    memset(newstr + strlen(oldstr) - strlen(substr) + strlen(replacement), 0, 1);
    //move back head right after the last replacement
    head = newstr + (tok - oldstr) + strlen(replacement);
    free(oldstr); //free memory
}
    *modified = 1;
    printf("Replaced %li occurances.\n", count);
  return newstr;
}

int main(int argc, char *argv[])
{
  int modified = 0;

  if(argc < 4) //invalid number of arguments
  { 
    usage(argv[0]);
    return 1;
  }
  
  if(access(argv[1], F_OK) == -1) //check file exists
  {
    printf("File %s does not exist\n", argv[1]);
    return 1;
  }
  FILE *change = fopen(argv[1], "r"); //open file read only
  fseek(change, 0, SEEK_END);
  long fsize = ftell(change); //find size of file
  fseek(change, 0, SEEK_SET); //reset pointer to beginning of stream

  char *string = malloc(fsize + 1); //allocate memory for buffer
  fread(string, fsize, 1, change); //read file into buffer
  fclose(change); //close file
  printf("Read %li bytes from file %s\n", fsize, argv[1]);
  if(fsize < 1) //opened empty file
  {
    printf("%s is an empty file. Try again.\n", argv[1]);
    return 1;
  }
  string[fsize] = 0; //set string to NULL

  //Check for -f option
  int l, m, n;
  char ch;

  for(n = 2; n < argc; n++) //Scan through arguments
  {
    switch((int)argv[n][0]) //Check for option character
    {
     case '-':
     {
      l = strlen(argv[n]);
        for(m = 1; m < l; ++m) //Scan through options
        {
          ch = (int)argv[n][m];
          switch( ch )
          {
            case 'f': 
            {
                int i,j=3, k=4;
                int x = (argc-3); //find number of arguments after -f

                if (x%2 != 0) //if it is an odd number, display usage text
                {
                  usage(argv[0]);
                  return 1;
                }
                x = x/2; //calculate number of times to call str_replace_first function
                for(i=0; i<x; i++, j+=2, k+=2) //increment j,k by 2 to go to next pair of argv[] 
                {
                  string = str_replace(string, argv[j], argv[k], &modified, 0); //get chars* form argv[] variable
                }
                if(modified) //write file only if buffer has been modified
                {
                  #ifdef DEBUG
                    puts(string); //display string for testing,
                  #endif
                  change = fopen(argv[1], "w"); //open file for writing, clearing all contents
                  long written = fwrite(string, 1, strlen(string), change); //use written variable to store number of written bytes
                  if (written == strlen(string)) //check written bytes matches total bytes
                  {
                      printf("Wrote %li bytes to file %s\n", written, argv[1]);
                      fclose(change); //close file
                      return 0; //end program here
                  } else {
                    printf("Error writing to file %s. Wrote %li bytes.\n", argv[1],written);
                    fclose(change);
                    return -1; //return error
                  }
                } else {
                  printf("Replacement strings not found in file %s\n", argv[1]);
                  return 1;
                }
            }
            default:  printf("%s is not a valid option.\n", argv[n]); //display usage text
              return 0; //end program
          }
        }
      }
    }
  }

  //No option found
  int i,j=2, k=3; //offset for argv strings
  int x = (argc-2); //calculate number of times to loop
  //call replace function for x = (argc - 2)/2
  if (x%2 != 0) //if it is an odd number then display usage text
  {
    usage(argv[0]);
    return 1;
  }
  x = x/2; //calculate number of times to call replace function
  for(i=0; i<x; i++, j+=2, k+=2) //go to next pair of argv
  {
    string = str_replace(string, argv[j], argv[k], &modified, 1); //get chars* form argv[] variable
  }
  if(modified)
  {
    #ifdef DEBUG
      puts(string); //display string for testing,
    #endif
    change = fopen(argv[1], "w"); //open file for writing, clearing all contents
    long written = fwrite(string, 1, strlen(string), change); //use written variable to store number of written bytes
    if (written == strlen(string)) //check written bytes matches total bytes
    {
      printf("Wrote %li bytes to file %s\n", written, argv[1]);
      fclose(change); //close file
      return 0; //end program here
    } 
    else 
    {
      printf("Error writing to file %s. Wrote %li bytes.\n", argv[1],written);
      fclose(change);
      return -1; //return error
    }
  }
  else 
  {
    printf("Replacement strings not found in file %s\n", argv[1]);
    return 1;
  }
}
