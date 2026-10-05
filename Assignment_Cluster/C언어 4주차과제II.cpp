#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10

//최대값 찾기
int main(void)
{
	srand((unsigned int)time(NULL));
	int seq[SIZE] = {};

	printf("---------------------------------\n");
	printf("1 2 3 4 5 6 7 8 9 10\n");
	printf("---------------------------------\n");
	for (int i = 0; i < SIZE; i++)
	{
		seq[i] = rand() % 100;
		printf("%2d ", seq[i]);
	}
	printf("\n\n");

	int max = seq[0];

	for (int i = 1; i < SIZE; i++)
	{

		if (seq[i] >= max)
		{
			max = seq[i];
		}
	}
	printf("\n");
	printf("위의 숫자중 최대값은 %d입니다.\n", max);


	return 0;
}
