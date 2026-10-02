#include <stdio.h>
//최대 최소 구하기
int returnMaxValue(int a, int b, int c);
int returnMinValue(int a, int b, int c);

int main_III()
{
	int num1, num2, num3, MaxVal, MinVal;
	printf("세개의 수를 입력하시오. ");
	scanf_s("%d %d %d", &num1, &num2, &num3);
	MaxVal = returnMaxValue(num1, num2, num3);
	MinVal = returnMinValue(num1, num2, num3);

	printf("%d %d %d중 최댓값은 %d이고, 최솟값은 %d입니다.", num1, num2, num3, MaxVal, MinVal);
	return 0;
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