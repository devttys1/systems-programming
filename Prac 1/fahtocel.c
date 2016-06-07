#include <stdio.h> /*Print Fahrenhiet-Celcius table for fah=0,10...,200*/

int main(int argc, char const *argv[])
{
	int fah,  cel;
	int lower, upper, step;
	lower = 0; /*lower limit of the temperature table */
	upper = 200; /*upper limit of the temperature table */
	step = 10; /*step size */

	fah=lower;
	do
	{
		cel=5*(fah-32)/9;
		printf("%d\t%d\n", fah, cel);
		fah+=step;
	} while (fah<=upper);
	return 0;
}