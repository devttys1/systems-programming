#include <stdio.h>
int fib(int);
int main(int argc, char const *argv[])
{
	int n = 10, i;

	for (i = 1; i<=n; i++)
	{
		printf("%d\n", fib(i));
	}
	
	return 0;
}

int fib (int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return (fib(n-1) + fib(n-2));
}