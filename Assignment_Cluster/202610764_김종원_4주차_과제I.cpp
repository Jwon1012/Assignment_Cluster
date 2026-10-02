#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5 //for 실습III
#define STUDENTS 10 //for 실습IV
int main_IVI(void)
{
	srand((unsigned int)time(NULL));
	//실습 I (선언된 1차원 배열의 접근)
	int arr[5] = { 10,20,30,40,50 };
	int sum = 0, i;

	for (int i = 0; i < 5; i++)
	{
		sum += arr[i];
	}

	printf("sum of arr: %d\n\n", sum); //결과: 150

	//실습 II (1차원 배열의 선언, 초기화 및 접근 관련 예제)
	int arr1[5] = { 1,2,3,4,5 };
	int arr2[] = { 1,2,3,4,5,6,7 };
	int arr3[5] = { 1,2 };
	int ar1Len, ar2Len, ar3Len;

	ar1Len = (unsigned int)(sizeof(arr1) / sizeof(arr1[0]));
	ar2Len = (unsigned int)(sizeof(arr2) / sizeof(arr2[0]));
	ar3Len = (unsigned int)(sizeof(arr3) / sizeof(arr3[0]));

	printf("size of arr1: %d\n", (unsigned int)(sizeof(arr1))); //20
	printf("size of arr2: %d\n", (unsigned int)(sizeof(arr2))); //28
	printf("size of arr3: %d\n\n", (unsigned int)(sizeof(arr3))); //20

	for (i = 0; i < ar1Len; i++)
	{
		printf("%d ", arr1[i]); //1 2 3 4 5
	}
	printf("\n");

	for (i = 0; i < ar2Len; i++)
	{
		printf("%d ", arr2[i]); //1 2 3 4 5 6 7
	}
	printf("\n");

	for (i = 0; i < ar3Len; i++)
	{
		printf("%d ", arr3[i]); //1 2 0 0 0
	}
	printf("\n\n");

	//실습 III (배열의 값을 난수로 채워보기)
	int scores[SIZE];

	for (int i = 0; i < SIZE; i++)
	{
		scores[i] = rand() % 100; //0~99의 숫자중 하나씩 배열 안에 들어갈 예정.
	}

	for (int i = 0; i < SIZE; i++)
	{
		printf("scores[%d] = %d\n\n", i, scores[i]);
	}

	//실습IV (배열을 이용하여 성적평균 계산하기)
	int Scores[STUDENTS];
	int Sum = 0;

	for (int i = 0; i < STUDENTS; i++)
	{
		printf("Write down students' score ");
		scanf_s("%d", &Scores[i]);
	}

	for (int i = 0; i < STUDENTS; i++)
	{
		sum += Scores[i];
	}

	printf("Average score of students: %d\n\n", sum / STUDENTS);

	//실습 V (극장 예약 시스템)

	return 0;



}