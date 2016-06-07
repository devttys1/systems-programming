#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Stack operations;
PUSH
POP
STACK-EMPTY

push operation
--------------
Algorithm push(newElement)
//increment index to the top element;
topElementIndex <- topElementIndex + 1
stack[topElementIndex] <- newElement

pop operation
-------------
Algorithm pop()
elementToReturn = stack[topElementIndex]
topElementIndex <- topElementIndex - 1
return elementToReturn

isEmpty operation
-----------------
Algorithm isEmpty()
if topElementIndex = -1
return true
else
return false
*/


typedef char stackitem;

struct stack
{
	stackitem d;
	struct stack *next;
};

typedef struct stack ELEMENT;
typedef ELEMENT *POINTER;

void push(POINTER *Top, stackitem a);
void pop(POINTER *Top);
void push_string(POINTER *Top, char *string);
void print_stack(POINTER Top);
void delete_stack(POINTER *Top);

int main(int argc, char const *argv[])
{
	POINTER start=NULL;
	int choice;
    int option = 1;
    int MAX = 20;
    char tmp[MAX];
 	printf("\e[1;1H\e[2J");
    printf ("STACK OPERATION\n");
    while (1)
    {
        printf ("------------------------------------------\n");
        printf ("      1    -->    PUSH STRING              \n");
        printf ("      2    -->    PUSH               \n");
        printf ("      3    -->    POP               \n");
        printf ("      4    -->    DISPLAY               \n");
        printf ("      5    -->    DELETE           \n");
        printf ("      6    -->    EXIT           \n");
        printf ("------------------------------------------\n");
 
        printf ("Enter your choice\n");
        scanf    ("%d", &choice);
        fgets(tmp, MAX, stdin);

        switch (choice)
        {
	        case 1:
	        {
	        	char *buffer = NULL;
    			size_t read;
    			size_t len = 0;
    			printf("Enter your string> ");
    			read = getline(&buffer, &len, stdin);
    			strtok(buffer, "\n");    
    			//printf("Size read: %d\n Len: %lu\n", read, len);
    			push_string(&start, buffer);
    			free(buffer);
	            break;
	        }
	        case 2:
	        {
	        	char mychar;
	            printf("Enter a character\n");
	            fflush (stdin);
        		scanf("%c", &mychar);
        		fgets(tmp, MAX, stdin);
	            push(&start, mychar);
	            break;
	        }
	        case 3:
	            pop(&start);
	            break;
	        case 4:
	            print_stack(start);
	            break;
	        case 5:
	            delete_stack(&start);
	            break;
	        case 6:
	            return 0;
        }
        fflush (stdin);
        //printf ("Do you want to continue(Type 0 or 1)?\n");
        //scanf    ("%d", &option);
        //fgets(tmp, MAX, stdin);
    }
	//return 0;
}

void push(POINTER *Top, stackitem a)
{
	POINTER temp;
	temp = malloc(sizeof(ELEMENT));
	temp->d = a;
	temp->next = *Top;
	*Top = temp;
}

void pop(POINTER *Top)
{
	POINTER Top1 = *Top;
	if (Top != NULL)
	{
		*Top = Top1->next;
		free(Top1);
	} else
		printf("Empty Stack.\n");

}

void push_string(POINTER *Top, char *string)
{
	int i = 0;
	while(string[i])
	{
		push(Top, string[i]);
		i++;
	}
}

void print_stack(POINTER Top)
{
	POINTER copy = Top;
	if (Top == NULL)
		printf("Empty Stack.\n");
	while(copy)
	{
		printf("%c", copy->d);
		copy = copy->next;
	}
	printf("\n");
}

void delete_stack(POINTER *Top)
{
	while(*Top)
	{
		pop(Top);
	}
}