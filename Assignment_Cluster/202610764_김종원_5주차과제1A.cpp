#include <stdio.h>

// 함수 선언
static void prac1(void);
static void prac2(void);
static void prac3(void);
static void prac4(void);
static void prac5(void);
static void prac6(void);
static void prac7(void);
static void prac8(void);

int main(void)
{
	int choice;
	while (1)
	{
		printf("실행하고 싶은 실습 번호를 입력하세요. (1~8) (0은 프로그램 종료) ");
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
		case 7:
			prac7();
			break;
		case 8:
			prac8();
			break;
		default:
			printf("잘못된 입력입니다. 다시 입력하세요.\n");
			break;
		}
	}
	return 0;
}

static void prac1(void)
{
	int calc;
	float num1, num2;
	float result = 0.0f;

	printf("\n");
	printf("실습I (If를 활용한 계산기 만들기)\n");
	while (1)
	{
		printf("무슨 연산을 하시겠습니까? 1: 덧셈, 2:뺄셈, 3:곱셈, 4:나눗셈: ");
		scanf_s("%d", &calc);

		printf("연산을 진행할 두 수를 입력해주세요: ");
		scanf_s("%f %f", &num1, &num2);

		if (calc == 1)
		{
			result = num1 + num2;
		}
		if (calc == 2)
		{
			result = num1 - num2;
		}
		if (calc == 3)
		{
			result = num1 * num2;
		}
		if (calc == 4)
		{
			if (num2 == 0)
			{
				printf("0으로 나눌 수는 없습니다.\n\n");
				continue;
			}
			else
				result = num1 / num2;
		}
		printf("결과: %.2f\n", result);
		break;
	}
}

static void prac2(void)
{
	int num;

	printf("\n");
	printf("실습II (if~else문을 이용한 흐름의 분기)\n");

	printf("정수 입력: ");
	scanf_s("%d", &num);

	if (num < 0)
	{
		printf("num은 0보다 작습니다.\n");
	}
	else
	{
		printf("num은 0 이상입니다.\n");
	}
}

// 
static void prac3(void)
{
	int calc;
	float num1, num2;
	float result = 0.0f;
	printf("\n");
	printf("실습III (if-else if-else문의 적용)\n");
	while (1)
	{
		printf("[실습3] 무슨 연산을 하시겠습니까? 1: 덧셈, 2:뺄셈, 3:곱셈, 4:나눗셈: ");
		scanf_s("%d", &calc);

		printf("연산을 진행할 두 수를 입력해주세요: ");
		scanf_s("%f %f", &num1, &num2);

		if (calc == 1)
		{
			result = num1 + num2;
		}
		else if (calc == 2)
		{
			result = num1 - num2;
		}
		else if (calc == 3)
		{
			result = num1 * num2;
		}
		else if (calc == 4)
		{
			if (num2 == 0)
			{
				printf("0으로 나눌 수는 없습니다.\n\n");
				continue;
			}
			else
				result = num1 / num2;
		}
		else
		{
			printf("잘못된 연산 번호입니다.\n\n");
			continue;
		}

		printf("결과: %.2f\n", result);
		break;
	}
}

// 
static void prac4(void)
{
	int N, abs;
	printf("\n");
	printf("실습IV (삼항 연산자)\n");
	printf("[실습4] 정수 입력: ");
	scanf_s("%d", &N);

	abs = (N > 0) ? N : N * (-1);
	printf("절댓값: %d\n", abs);
}

// 
static void prac5(void)
{
	int sigma = 0;
	int Num = 0;
	printf("\n");
	printf("실습V (break)\n");
	while (1)
	{
		sigma += Num;
		if (sigma > 5000)
		{
			break;
		}
		Num++;
	}

	printf("1부터 %d까지의 합: %d\n", Num, sigma);
}

//
static void prac6(void)
{
	printf("\n");
	printf("실습VI continue\n");

	printf("Start! ");
	for (int i = 0; i <= 20; i++)
	{
		if (i % 2 == 0 || i % 3 == 0)
			continue;
		printf("%d", i);
	}
	printf("end!");

}

static void prac7(void)
{
	printf("\n");
	printf("실습VII (break 없는 switch문 구성)\n");

	char sel;
	printf("M: 오전, A: 오후, E: 저녁, D: 새벽 \n");
	scanf_s(" %c", &sel, (unsigned int)sizeof(sel));

	switch (sel)
	{
	case 'M': case 'm':
		printf("Morning \n");
		break;
	case 'A': case 'a':
		printf("Afternoon \n");
		break;
	case 'E': case 'e':
		printf("Evening \n");
		break;
	case 'D': case 'd':
		printf("Dawn \n");
	}


}

static void prac8(void)
{
	int num;
	printf("\n");
	printf("실습VIII (goto문?)\n");

	printf("자연수 입력: ");
	scanf_s("%d", &num);
	
	if (num == 1)
		goto ONE;
	else if (num == 2)
		goto TWO;
	else
		goto OTHER;

ONE:
	printf("1을 입력하셨습니다!\n");
	goto END;
TWO:
	printf("2를 입력하셨습니다!\n");
	goto END;
OTHER:
	printf("3 혹은 다른 값을 입력하셨군요!\n");
	goto END;
END:
	printf("\n");
}