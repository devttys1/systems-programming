#include <stdio.h>

int main(int argc, char const *argv[])
{
   float n1, n2, n3;
   printf("Enter three numbers: ");
   scanf("%f %f %f", &n1, &n2, &n3);
   if(n1>=n2 && n1>=n3)
      printf("Largest number = %.2f", n1);
   else if(n2>=n1 && n2>=n3)
      printf("Largest number = %.2f", n2);
   else
      printf("Largest number = %.2f", n3);
   printf("\n");
   return 0;
   
}