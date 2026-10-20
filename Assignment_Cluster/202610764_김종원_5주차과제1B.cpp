#include <stdio.h>

// 함수 선언부
//실습에 사용되는 함수 모음집
//for prac10,11
static int add(int a, int b);
static void ShowAddResult(int num);
static int ReadNum(void);
static void HowToUseThisProg(void);
//for prac12
static int Numpare(int num1, int num2);
//for prac13
static double AbsoComp(double num1, double num2);
static double AbsVal(double num);

//실습 호출 함수
static void prac9(void);
static void prac10(void);
static void prac11(void);
static void prac12(void);
static void prac13(void);
static void prac14(void);
static void prac15(void);
static void prac16(void);
static void prac17(void);



int main_V(void)
{
	int choice;
	while (1)
	{
		printf("실행하고 싶은 실습 번호를 입력하세요. (9~17) (0은 프로그램 종료) ");
		scanf_s("%d", &choice);

		if (choice == 0)
		{
			printf("프로그램을 종료합니다.");
			break;
		}

		switch (choice)
		{
		case 9:
			prac9();
			break;
		case 10:
			prac10();
			break;
		case 11:
			prac11();
			break;
		case 12:
			prac12();
			break;
		case 13:
			prac13();
			break;
		case 14:
			prac14();
			break;
		case 15:
			prac15();
			break;
		case 16:
			prac16();
			break;
		case 17:
			prac17();
			break;
		default:
			printf("잘못된 입력입니다. 다시 입력하세요.\n");
			break;
		}
	}
	return 0;
}

static int add(int a, int b) 
{
	return a + b;
}

static void ShowAddResult(int num)
{
	printf("덧셈결과 출력: %d \n", num);
}

static int ReadNum(void)
{
	int num;
	scanf_s("%d", &num);
	return num;
}

void HowToUseThisProg(void)
{
	printf("두개의 정수를 입력하면 덧셈결과가 출력됩니다!\n");
	printf("자! 그럼 두개의 정수를 입력하세요! ");
}

static int Numpare(int num1, int num2)
{
	if (num1 > num2)
		return num1;
	else if (num1 < num2)
		return num2;
}

static double AbsVal(double num)
{
	return (num > 0) ? num :  num * (-1);
}

static double AbsoComp(double num1, double num2)
{
	if (AbsVal(num1) > AbsVal(num2))
		return num1;
	else
		return num2;
}

static void prac9(void)
{
	int n1, n2;
	printf("\n");
	printf("실습 IX (printf도 반환이 있는 함수)\n");
	n1 = printf("12345\n");
	n2 = printf("I love SMU\n");
	printf("%d %d \n", n1, n2); //6 11
	//문자 개수와 서식문자 \n을 포함해서 출력
	//n1 = 6. n2 = 11 (공백 포함, \n(줄바꿈 탈출문자)은 하나의 문자로 취급)
}

static void prac10(void)
{
	printf("\n");
	printf("실습 X (매개변수, 반환값 둘다 있는 함수)\n");

	int result;
	result = add(4, 3);
	printf("덧셈 결과1: %d\n", result);
	result = add(5, 8);
	printf("덧셈 결과2: %d\n", result);
}

static void prac11(void)
{
	printf("\n");
	printf("실습 XI (4가지 함수의 짬뽕)\n");

	int result, num1, num2;
	HowToUseThisProg();
	num1 = ReadNum();
	num2 = ReadNum();
	result = add(num1, num2);
	ShowAddResult(result);
}
static void prac12(void)
{
	printf("\n");
	printf("실습 XII (다양한 종류의 함수 정의I)\n");
	printf("3과 4중 더 큰수는 %d이고, 7과 2중 더 큰수는 %d이다. \n", Numpare(3, 4), Numpare(7,2));
}
static void prac13(void)
{
	float num1, num2;
	printf("\n");
	printf("실습 XIII (다양한 종류의 함수 정의II)\n");
	printf("실수 2개를 입력하세요.");
	scanf_s("%f %f", &num1, &num2);
	printf("첫번째와 두번째에 입력한중 절댓값이 더 큰 수는 %f입니다. \n", AbsoComp(num1, num2));
}
static void prac14(void)
{
	printf("\n");
	printf("실습 XIV (다양한 종류의 함수 정의II)\n");
}
static void prac15(void)
{

}
static void prac16(void)
{

}
static void prac17(void)
{

}

