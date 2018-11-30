#include <stdio.h>

void printHello()
{
	printf("Hello, world!\n");
	return 0; // should find error here
}

int add(int a, int b)
{
	return 2+3;
}

double pi()
{
	return 22.0/7.0;
}

float f()
{
	return 'c';
}

long lightspeed()
{
	return 299792458;
}

int main()
{
	printHello();
	printf("2+3 = %d\n", add(2,3));
	printf("pi = %lf\n", pi);
	printf("%f\n", f());

	return 0;
}
