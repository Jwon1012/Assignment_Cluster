#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS​
#define SIZE 10 //for 실습III, VI
#define STUDENTS 10 //for 실습IV

int main_I(void)
{
	srand((unsigned int)time(NULL));
	//실습 I (선언된 1차원 배열의 접근)
	int arr[5] = { 10,20,30,40,50 };
	int sum = 0, i;

	for (int i = 0; i < 5; i++)
	{
		sum += arr[i];
	}

	printf("배열의 합: %d\n\n", sum); //결과: 150

	//실습 II (1차원 배열의 선언, 초기화 및 접근 관련 예제)
	int arr1[5] = { 1,2,3,4,5 };
	int arr2[] = { 1,2,3,4,5,6,7 };
	int arr3[5] = { 1,2 };
	int ar1Len, ar2Len, ar3Len;

	ar1Len = (unsigned int)(sizeof(arr1) / sizeof(arr1[0]));
	ar2Len = (unsigned int)(sizeof(arr2) / sizeof(arr2[0]));
	ar3Len = (unsigned int)(sizeof(arr3) / sizeof(arr3[0]));

	printf("arr1의 크기: %d\n", (unsigned int)(sizeof(arr1))); //20
	printf("arr2의 크기: %d\n", (unsigned int)(sizeof(arr2))); //28
	printf("arr3의 크기: %d\n\n", (unsigned int)(sizeof(arr3))); //20

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
		printf("학생들의 점수를 작성하시오.");
		scanf_s("%d", &Scores[i]);
	}

	for (int i = 0; i < STUDENTS; i++)
	{
		sum += Scores[i];
	}

	printf("점수의 평균: %d\n\n", sum / STUDENTS);

	//실습 V (극장 예약 시스템)

	char answer;
	int answer_II;
	int seats[SIZE] = { 0 };


	while (1)
	{
		printf("좌석을 예약하시겠습니까? (Y/N) ");
		scanf_s(" %c", &answer, (unsigned int)sizeof(answer));
		if (answer == 'N' || answer == 'n')
		{
			break;
		}

		printf("-------------------------\n");
		printf("1 2 3 4 5 6 7 8 9 10\n");
		printf("-------------------------\n");
		for (int i = 0; i < (unsigned int)(sizeof(seats) / sizeof(seats[0]));i++)
		{
			printf("%d ", seats[i]);
		}
		printf("\n");
		printf("몇번째 좌석을 예약하시겠습니까? ");
		scanf_s("%d", &answer_II);
		if (answer_II < 1 || answer_II > 10)
		{
			printf("현재 입력하신 번호의 좌석이 없습니다. 1~%d사이의 수를 입력해주세요.\n", SIZE);
			continue;
		}

		if (seats[answer_II - 1] == 0)
		{
			seats[answer_II - 1] == 1;
			printf("%d번 좌석이 성공적으로 예약되었습니다.\n", answer_II);
		}
		else
			printf("이미 예약되었습니다.\n");
		

	}

	//실습 VI (최소값 찾기)

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

	int min = seq[0];

	for (int i = 1; i < SIZE; i++)
	{

		if (seq[i] <= min)
		{
		   min = seq[i];
		}
	}
	printf("\n");
	printf("위의 숫자중 최솟값은 %d입니다.\n", min);


	return 0;



}