#include <stdio.h> 
int celc(int);
int main(int argc, char const *argv[])
{
	int temp;

	printf("\nPlease enter temp F");
	scanf("%d", &temp);

	printf("\n%dF to Centigrade is %dC\n", temp, celc(temp));
	return 0;
}

int celc(int f)
{
	return 5*(f-32)/9;
}