#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define YEARS 3
#define PRODUCTS 5
#define STUDENTS 5
#define SIZE 7
#define BIG_SIZE 10
#define BIGGER_SIZE 16
#define ROWS 3
#define cols 3
#define COLS 5
static void prac1();
static void prac2();
static void prac3();
static void prac4();
static void prac5();
static void prac6();
static void prac7();
static void prac8();
static void prac9();
static void prac10();
static void prac11();
//실습I
static int get_avg(int scores[], int n);
//실습II
static void modif_arr(int a[], int size);
static void print_arr(int a[], int size);
//실습V
static int binary_search(int list[], int n, int value);
//실습IX
static int sum(int scores[YEARS][PRODUCTS]);
//실습X
void display_img(int pixels[8][16]);
void inv_img(int pixels[8][16]);
int main(void)
//실습XI

{
	int choice;

	while (1)
	{
		printf("실행하고 싶은 실습 번호를 입력하세요. (프로그램 종료는 0) ");
		scanf_s("%d", &choice);

		if (choice == 0)
		{
			printf("프로그램을 종료합니다.");
			break;
		}

		switch (choice) {
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
		case 7:
			prac7();
			break;
		case 8:
			prac8();
			break;
		case 9:
			prac9();
			break;
		case 10:
			prac10();
			break;
		case 11:
			prac11();
			break;
		default:
			printf("존재하지 않는 실습 번호입니다.");
		}
	}

	return 0;
}

int get_avg(int scores[], int n)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += scores[i];
	}

	return sum / n;
}

static void prac1()
{
	printf("\n");
	printf("실습I: 배열과 함수\n");

	int scores[STUDENTS] = { 1, 2, 3, 4, 5 };
	int avg = 0;

	avg = get_avg(scores, STUDENTS);

	for (int i = 0; i < STUDENTS; i++)
	{
		printf("%d ", scores[i]);
	}

	printf("의 평균은 %d입니다.\n\n", avg);
}

static void modif_arr(int a[], int size)
{
	int i = 0;

	for (i = 0; i < size; i++)
	{
		++a[i];
	}
}
static void print_arr(int a[], int size)
{

	int i = 0;
	for(i = 0; i < size; i++)
	{
		printf("%3d ", a[i]);
	}
	printf("\n");
}

static void prac2()
{
	printf("\n");
	printf("실습II: 배열이 함수의 매개변수인 경우\n");

	int list[SIZE] = { 1,2,3,4,5,6,7 };

	print_arr(list, SIZE);
	modif_arr(list, SIZE);
	print_arr(list, SIZE);

}
static void prac3()
{
	printf("\n");
	printf("실습 III: 선택정렬\n");

	int list[BIG_SIZE] = { 3,2,9,7,1,4,8,0,6,5 };

	int temp1, least, max, temp2;
	for (int i = 0; i < BIG_SIZE-1; i++) //오름차순 정렬 알고리즘
	{
		least = i;
		for (int j = i + 1; j < BIG_SIZE; j++)
		{
			if (list[j] < list[least])
				least = j;
		}

		temp1 = list[i]; //list[i]와 list[least]를 서로 교환
		list[i] = list[least];
		list[least] = temp1;


	}

	for (int i = 0; i < BIG_SIZE; i++)
	{
		printf("%d ", list[i]);
	}
	printf("\n");


	for (int i = 0; i < BIG_SIZE - 1; i++) //내림차순 정렬 알고리즘
	{
		max = i;
		for (int j = i + 1; j < BIG_SIZE; j++)
		{
			if (list[j] > list[max])
				least = j;
		}

		temp2 = list[i]; //list[i]와 list[least]를 서로 교환
		list[i] = list[least];
		list[least] = temp2;
	}

	for (int i = 0; i < BIG_SIZE; i++)
	{
		printf("%d ", list[i]);
	}
	printf("\n");

}
static void prac4()
{
	printf("\n");
	printf("실습 IV: 순차탐색\n");

	int list[SIZE] = { 1, 2, 3, 4, 5, 6, 7 };

	int value;
	int found = 0;
	printf("찾고자 하는 숫자를 입력해주세요.");
	scanf_s("%d", &value);

	for (int i = 0; i < SIZE; i++)
	{
		if (list[i] == value)
		{
			printf("해당 값은 %d번째 배열에 존재합니다. (인덱스: %d)\n", i + 1, i);
			found = 1; 
			break; //찾았으니까 배열 탈출
		}
	}

	if (found == 0)
		printf("해당 값은 배열 내에 존재하지 않습니다.\n"); //값이 없을때 실행하는 코드
}

static int binary_search(int list[], int n, int value)
{
	int low, mid, high;
	low = 0;
	high = n - 1;
	while (low <= high) //아직 숫자들이 남아있다면
	{
		printf("[%d %d]\n", low, high); //하,상한 출력
		mid = (low + high) / 2;
		if (value == list[mid]) //일치하면 탐색 성공
			return mid;
		else if (value > list[mid]) //중간 원소보다 크면 
			low = mid + 1; //새로운 값으로 low설정
		else
			high = mid - 1; //아니면 새로운 값으로 high설정
	}
	return -1;
}
static void prac5()
{

	printf("\n");
	printf("실습 V: 이진탐색\n");

	int key;
	int list[BIGGER_SIZE] = { 2,6,11,13,18,20,22,27,29,30,34,38,41,42,45,47 };
	printf("탐색한 값을 입력하세요.");
	scanf_s("%d", &key);
	printf("탐색결과: %d\n", binary_search(list, BIGGER_SIZE, key));
}
static void prac6()
{
	printf("\n");
	printf("실습 VI: 2차원 배열안에 난수 집어넣기\n");

	int matrix[ROWS][COLS]; //2차원 배열의 선언
	srand((unsigned int)time(NULL));

	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			matrix[i][j] = rand() % 100; //0부터 99까지의 숫자중 랜덤으로 들어감.

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			printf("%02d ", matrix[i][j]);
		}
		printf("\n");
	}

}

static void prac7()
{
	printf("\n");
	printf("실습 VII: 2차원 배열의 활용\n");

	// 학번 중간(30) 기말(40) 기말과제(20) 퀴즈점수(10) 결석횟수
	double final_scores[ROWS] = {};
	double scores[ROWS][COLS + 1] = {
		{ 1, 87, 98, 80, 76, 3 },
		{ 2, 99, 89, 90, 90, 0 },
		{ 3, 65, 68, 50, 49, 0 }
	};

	for (int i = 0; i < ROWS; i++)
	{
		final_scores[i] = scores[i][1] * 0.3 + scores[i][2] * 0.4 + scores[i][3] * 0.2 + scores[i][4] * 0.1 - scores[i][5];
	}

	for (int i = 0; i < ROWS; i++)
	{
		printf("%d번 학생의 최종점수: %.2lf점\n", i, final_scores[i]);
	}

}
static void prac8()
{
	printf("\n");
	printf("실습 VIII: 다차원 배열을 이용한 행렬 표현\n");

	int A[ROWS][cols] =
	{
		{2,3,0},
		{8,9,1},
		{7,0,5}
	};
	int B[ROWS][cols] =
	{
		{1,0,0},
		{ 1,0,0 },
		{ 1,0,0 }
	};
	int C[ROWS][cols];

	//A + B = C
	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < cols; c++)
			C[r][c] = A[r][c] + B[r][c];

	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			printf("%d ", C[r][c]);
		}
		printf("\n");
	}


}

static int sum(int scores[YEARS][PRODUCTS])
{
	int sum = 0;
	for (int r = 0; r < YEARS; r++)
	{
		for (int c = 0; c < PRODUCTS; c++)
		{
			sum += scores[r][c];
		}
	}

	return sum;
}
static void prac9()
{
	printf("\n");
	printf("실습 IX: 2차원 배열을 함수로 전달\n");

	int sales[YEARS][PRODUCTS] = {
		{ 1,2,3 },
		{ 4,5,6 },
		{ 7,8,9 }
	};
	int total_sales;

	printf("총 매출은 %d입니다.\n", sum(sales));
}

void display_img(int pixels[8][16])
{
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 16; c++)
		{
			printf("%s", pixels[r][c] == 1 ? "_" : "*");
		}
		printf("\n");
	}
}

void inv_img(int pixels[8][16])
{
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 16; c++)
		{
			printf("%s", pixels[r][c] == 1 ? "*" : "_");
		}
		printf("\n");
	}
}
static void prac10()
{
	printf("\n");
	printf("실습 X: 영상처리\n");

	int image[8][16] =
	{
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1 },
		{ 1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	};

	printf("기존의 이미지\n");
	display_img(image);

	printf("반전된 이미지\n");
	inv_img(image);

}
static void prac11()
{
	printf("\n");
	printf("실습 XI: 틱택토\n");

	char board[3][3];
	int x, y, k, i;

	//보드 초기화
	for (x = 0; x < 3; x++)
		for (y = 0; y < 3; y++)
			board[x][y] = ' ';

	//사용자에게 위치를 받아서 보드에 표시
	for (k = 0; k < 9; k++)
	{
		printf("(x,y) 좌표: ");
		scanf_s("%d %d", &x, &y);

		//1. 범위 밖 예외처리
		if (x < 0 || x > 2 || y < 0 || y > 2)
		{
			printf("잘못된 숫자 입력입니다. 0~2사이의 숫자를 입력해주세요.\n");
			k--;
			continue;
		}

		//2. 중복 위치 예외처리
		if (board[x][y] != ' ')
		{
			printf("이미 놓인 위치입니다. 다시 입력하세요.");
			k--;
			continue;
		}


		board[x][y] = (k % 2 == 0) ? 'X' : 'O'; //현재의 순번에 따라 X, O중 하나 선택 (K가 짝수면 X, 홀수면 O)
		//보드를 화면에 그리기
		for (i = 0; i < 3; i++)
		{
			printf("---|---|---| \n");
			printf(" %c | %c | %c |\n", board[i][0], board[i][1], board[i][2]);
		}
		printf("---|---|---| \n");

		//승리조건 I. 가로/세로에 같은 기호
		// 같은 행 -> 다른 열, 같은 열 -> 다른 행
		for (int x = 0; x < 3; x++)
		{
			if (board[x][0] == 'X' && board[x][1] == 'X' && board[x][2] == 'X') { printf("P1 승리!"); return;}
			else if (board[x][0] == 'O' && board[x][1] == 'O' && board[x][2] == 'O') { printf("P2 승리!"); return; }
			else if (board[0][x] == 'X' && board[1][x] == 'X' && board[2][x] == 'X') { printf("P1 승리!"); return; }
			else if (board[0][x] == 'O' && board[1][x] == 'O' && board[2][x] == 'O') { printf("P2 승리!"); return; }
		}
		//승리조건 II. 행번호와 열번호가 같은 칸에 같은 기호
		if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X') {printf("P1 승리!"); return; }
		else if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O') { printf("P2 승리!"); return; }

		//승리조건 III. 행번호와 열번호의 합이 2인 같에 같은 기호
		if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X') { printf("P1 승리!"); return; }
		else if (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O') { printf("P2 승리!"); return; }

		if (k == 8) printf("무승부!");
	}
}