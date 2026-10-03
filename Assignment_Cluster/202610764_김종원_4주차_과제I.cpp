#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS
#define SIZE 10
#define STUDENTS 10

// 함수 선언
static void prac1(void);
static void prac2(void);
static void prac3(void);
static void prac4(void);
static void prac5(void);
static void prac6(void);

int main(void)
{
	srand((unsigned int)time(NULL));
	int choice;
	while (1)
	{
		printf("실행하고 싶은 실습의 번호를 선택하세요. (1~6, 0은 종료) ");
		scanf_s("%d", &choice);

		if (choice == 0)
		{
			printf("프로그램을 종료합니다.");
			break;
		}

		switch (choice)
		{
		case 1:
			prac1();
			break;
		case 2:
			prac2();
			break;
		case 3:
			prac3();
			break;
		case 4:
			prac4();
			break;
		case 5:
			prac5();
			break;
		case 6:
			prac6();
			break;
		default:
			printf("존재하지 않는 실습입니다. 다시 입력해주세요.\n");
			break;
		 }
	}


	return 0;
}

static void prac1(void)
{
	int arr[5] = { 10, 20, 30, 40, 50 };
	int sum = 0;

	printf("\n");
	printf("실습 I (선언된 1차원 배열의 접근)\n");

	for (int i = 0; i < 5; i++)
	{
		sum += arr[i];
	}

	printf("배열의 합: %d\n\n", sum);
}


static void prac2(void)
{
	int arr1[5] = { 1, 2, 3, 4, 5 };
	int arr2[] = { 1, 2, 3, 4, 5, 6, 7 };
	int arr3[5] = { 1, 2 };

	int ar1Len = (unsigned int)(sizeof(arr1) / sizeof(arr1[0]));
	int ar2Len = (unsigned int)(sizeof(arr2) / sizeof(arr2[0]));
	int ar3Len = (unsigned int)(sizeof(arr3) / sizeof(arr3[0]));

	printf("\n");
	printf("실습 II (1차원 배열의 선언, 초기화 및 접근 관련 예제)\n");

	printf("arr1의 크기: %zu\n", sizeof(arr1));
	printf("arr2의 크기: %zu\n", sizeof(arr2));
	printf("arr3의 크기: %zu\n\n", sizeof(arr3));

	for (int i = 0; i < ar1Len; i++)
	{
		printf("%d ", arr1[i]);
	}
	printf("\n");

	for (int i = 0; i < ar2Len; i++)
	{
		printf("%d ", arr2[i]);
	}
	printf("\n");

	for (int i = 0; i < ar3Len; i++)
	{
		printf("%d ", arr3[i]);
	}
	printf("\n\n");
}

static void prac3(void)
{
	int scores[SIZE];

	for (int i = 0; i < SIZE; i++)
	{
		scores[i] = rand() % 100;
	}

	printf("\n");
	printf("실습 III (배열의 값을 난수로 채워보기)\n");

	printf("생성된 난수 점수 목록:\n");
	for (int i = 0; i < SIZE; i++)
	{
		printf("scores[%d] = %d\n", i, scores[i]);
	}
	printf("\n");
}

static void prac4(void)
{
	int scores[STUDENTS];
	int sum = 0; // 지역 변수로 독립 초기화

	printf("\n");
	printf("실습 IV (배열을 이용하여 성적평균 계산하기)\n");

	printf("학생들의 점수를 입력하세요.\n");
	for (int i = 0; i < STUDENTS; i++)
	{
		printf("%d번 학생 점수: ", i + 1);
		scanf_s("%d", &scores[i]);
	}

	for (int i = 0; i < STUDENTS; i++)
	{
		sum += scores[i];
	}

	printf("점수의 평균: %d\n\n", sum / STUDENTS);
}

// 실습 V (극장 예약 시스템)
static void prac5(void)
{
	char answer;
	int seatNum;
	int seats[SIZE] = { 0 };

	printf("\n");
	printf("실습 V (극장 예약 시스템)\n");

	while (1)
	{
		printf("[실습 V] 좌석을 예약하시겠습니까? (Y/N) ");
		scanf_s(" %c", &answer, (unsigned int)sizeof(answer));

		if (answer == 'N' || answer == 'n')
		{
			printf("예약 시스템을 종료합니다.\n\n");
			break;
		}

		printf("-------------------------\n");
		printf("1 2 3 4 5 6 7 8 9 10\n");
		printf("-------------------------\n");
		for (int i = 0; i < SIZE; i++)
		{
			printf("%d ", seats[i]);
		}
		printf("\n");

		printf("몇 번째 좌석을 예약하시겠습니까? ");
		scanf_s("%d", &seatNum);

		if (seatNum < 1 || seatNum > SIZE)
		{
			printf("1~%d 사이의 번호를 입력해주세요.\n\n", SIZE);
			continue;
		}

		if (seats[seatNum - 1] == 0)
		{
			seats[seatNum - 1] = 1; // 오타 수정: == (비교) -> = (대입)
			printf("%d번 좌석이 성공적으로 예약되었습니다.\n\n", seatNum);
		}
		else
		{
			printf("이미 예약된 좌석입니다.\n\n");
		}
	}
}

static void prac6(void)
{
	int seq[SIZE] = { 0 };

	printf("\n");
	printf("실습 VI (최솟값 찾기)\n");

	printf("---------------------------------\n");
	printf("1  2  3  4  5  6  7  8  9 10\n");
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

	printf("위의 숫자 중 최솟값은 %d입니다.\n\n", min);
}