#include <stdio.h>
#include <stdlib.h>

int fibonacci(int);
int main(int argc, char const *argv[])
{

	
	int n = atoi(argv[1]);
	
	printf("The first %d terms of fibonacci are:\n", n);
	for (int i = 1; i<=n; i++)
	{
		printf("%d\n", fibonacci(i));
	}
	return 0;
}
int fibonacci(int n)
{
	int f;
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		f = fibonacci(n-1) + fibonacci(n-2);
	return f;
}