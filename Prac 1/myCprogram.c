#include <stdio.h>

float max3(float, float, float);
float max2(float, float);

int main(int argc, char const *argv[])
{
	float n1, n2, n3;
	printf("Enter 3 numbers: ");
	scanf("%f %f %f", &n1, &n2, &n3);
	printf("The largest number is: %.2f", max3(n1, n2, n3));
	printf("\n");
	return 0;
}

inline float max2(float n1, float n2)
{
    return n1 > n2 ? n1 : n2; 
}

float max3(float n1, float n2, float n3)
{
    return max2(max2(n1,n2), max2(n2,n3));
}