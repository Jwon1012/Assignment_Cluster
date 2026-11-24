#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

static void example1();
static void example2();
static void example3();
static void example4();
int main(void)
{
	int choice = 0;
	while (1)
	{
		printf("실행하고싶은 연습 번호를 입력하세요. (0: 프로그램 종료, 1~4) ");
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
		default: printf("존재하지 않는 실습 번호입니다. 다시 입력하세요."); break;
		}
	}
	return 0;
}

static void example1(){
	printf("\n");
	printf("예제1: 지역 변수\n");
	int i;
	for (i = 0; i < 5; i++)
	{
		int temp = 1; //블록이 생성될때마다 초기화
		printf("temp = %d\n", temp);
		temp++;
	}
}
static void example2(){
	printf("\n");
	printf("예제2: 난수 생성기");


}
static void example3(){
}
static void example4(){
}