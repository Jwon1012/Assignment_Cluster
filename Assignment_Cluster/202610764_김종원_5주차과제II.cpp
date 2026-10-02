#include <stdio.h>
//최대 최소 구하기
int returnMaxValue(int a, int b, int c);
int returnMinValue(int a, int b, int c);

int main_VII()
{
	int num1, num2, num3, MaxVal, MinVal;
	printf("write down 3 nunmbers to compare. ");
	scanf_s("%d %d %d", &num1, &num2, &num3);
	MaxVal = returnMaxValue(num1, num2, num3);
	MinVal = returnMinValue(num1, num2, num3);

	printf("Maximum is %d and Minimum is %d among %d %d %d.", MaxVal, MinVal, num1, num2, num3);

}

int returnMaxValue(int a, int b, int c)
{
	int max = a;

	if (b > max)
		max = b;

	if (c > max)
		max = c;

	return max;

}

int returnMinValue(int a, int b, int c)
{
	int min = a;

	if (b < min)
		min = b;

	if (c < min)
		min = c;

	return min;

}