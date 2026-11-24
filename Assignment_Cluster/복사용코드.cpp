#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

static void example1();
static void example2();
static void example3();
static void example4();
static void example5();
static void example6();
static void example7();
static void example8();
static void example9();
static void example10();
static void example11();
static void example12();
static void example13();
static void example14();
static void example15();
static void example16();

int main_s(void)
{
	int choice = 0;
	while (1)
	{
		printf("실행하고싶은 연습 번호를 입력하세요. (0: 프로그램 종료, 1~16) ");
		scanf_s("%d", &choice);
		while (getchar() != '\n');
		//위의 scanf_s에서 생긴 \n 제거

		if (choice == 0)
		{
			printf("프로그램을 종료합니다.");
			break;
		}

		switch (choice)
		{
		case 1: example1(); break;
		case 2: example2(); break;
		case 3: example3(); break;
		case 4: example4(); break;
		case 5: example5(); break;
		case 6: example6(); break;
		case 7: example7(); break;
		case 8: example8(); break;
		case 9: example9(); break;
		case 10: example10(); break;
		case 11: example11(); break;
		case 12: example12(); break;
		case 13: example13(); break;
		case 14: example14(); break;
		case 15: example15(); break;
		case 16: example16(); break;
		default: printf("존재하지 않는 실습 번호입니다. 다시 입력하세요."); break;
		}
	}
	return 0;
}

static void example1() {}
static void example2() {}
static void example3() {}
static void example4() {}
static void example5() {}
static void example6() {}
static void example7() {}
static void example8() {}
static void example9() {}
static void example10() {}
static void example11() {}
static void example12() {}
static void example13() {}
static void example14() {}
static void example15() {}
static void example16() {}
