#include <stdio.h>
#define SIZE 5
//for 실습 VIII
static void fake_swap(int x, int y);
//for 실습 IX
static void true_swap(int *x, int *y);
//for 실습 X
int glp(int x1, int x2, int y1, int y2, float* slope, float* yintercept); //기울기와 y절편을 인수로 전달
//for 실습 XIV
static void print(int a[][SIZE]);
static void incr(int a[][SIZE]);
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
static void prac12();
static void prac13();
static void prac14();

int main(void)
{
	int choice = 0;
	int choice2 = 0;

	while (1)
	{
		printf("실행하고싶은 실습 번호를 입력하세요. (0: 프로그램 종료) ");
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
			prac3();
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
		case 12:
			prac12();
			break;
		case 13:
			prac13();
			break;
		case 14:
			prac14();
			break;
		default:
			printf("존재하지 않는 실습입니다. 다시 입력하세요.");
			break;
		}
	}
	return 0;
}

static void prac1()
{
	printf("\n");
	printf("실습I: 포인터변수 선언 및 포인터값 확인\n");
	int i = 10;
	double f = 12.3;
	int* pi = NULL;

	double* pf = NULL;
	pi = &i;
	pf = &f;

	printf("%p %p \n", pi, &i);
	printf("%p %p \n", pf, &f);
	printf("%p %p \n", &pi, &pf);
}
static void prac2()
{
	printf("\n");
	printf("실습II: &(address of)연산자와 *(de-reference)연산자\n");

	int i = 3000;
	int* p = NULL; //int *p = 0과 완전 동일 

	p = &i;
	printf("p = %p\n", p);
	printf("&i = %p\n\n", &i);
	printf("i = %d\n", i);
	printf("p = %d\n", *p);
}
static void prac3()
{
	printf("\n");
	printf("실습III: &(address of)연산자와 *(de-reference)연산자II\n");

	int x = 10;
	int y = 20;
	int* p = NULL;

	p = &x; //p의 R-Value: x의 주소값, p의 L-Value: p의 주소 (*p)
	printf("p = %p\n", p);
	printf("*p = %u\n\n", *p); //p가 가리키는 주소 (&x)로 쳐들어가서 알멩이값 (x = 10)출력

	p = &y;
	printf("p = %p\n", p);
	printf("*p = %u\n", *p);
}
static void prac4()
{
	printf("\n");
	printf("실습IV: 포인터를 통해서 변수의 값 변경하기\n");

	int i = 10;
	int* p = NULL;

	p = &i;
	printf("i = %d\n", i);
	
	*p = 20; //p의 주소 (&i)로 강제로 쳐들어가서 내용물의 값(10)을 20으로 변경
	printf("i = %d\n", i);
}
static void prac5()
{
	printf("\n");
	printf("실습V: 포인터의 증감연산\n");

	char* pc = NULL;
	int* pi= NULL;
	double* pd = NULL;

	pc = (char*)10000; //char 타입: ++연산후 1증가 ※1byte 자료형
	pi = (int*)10000; //int 타입: ++연산후 4증가 ※4byte 자료형
	pd = (double*)10000; //double 타입: ++연산후 8증가 ※8byte 자료형
	printf("pc = %u, pc+1 = %u, pc+2 = %u\n", (unsigned int)pc, (unsigned int)(pc+1), (unsigned int)(pc+2)); 
	printf("pi = %u, pi+1 = %u, pi+2 = %u\n", (unsigned int)pi, (unsigned int)(pi+1), (unsigned int)(pi+2)); 
	printf("pd = %u, pd+1 = %u, pd+2 = %u\n", (unsigned int)pd, (unsigned int)(pd + 1), (unsigned int)(pd + 2));
}
static void prac6()
{
	printf("\n");
	printf("실습VI: 별딱지(간접 참조) 연산자 & 증감연산\n");

	int i = 10;
	int* pi = &i;

	printf("i = %d, pi = %p\n", i, pi);

	*(pi)++; //pi가 가리키는 위치의 값 증가.
	printf("i = %d, pi = %p\n", i, pi);

	*pi++; //pi가 가리키는 위치에서 값을 갖고온 후 pi에 +1
	printf("i = %d, pi = %p\n", i, pi);

	printf("정리: \n");
	printf("1. (*p)++: 일단 현재 값 사용 -> 나중에 알맹이 +1\n");
	printf("2. ++*p: 먼저 알맹이 +1 -> 바뀐 값 사용\n");
	printf("3. *(p++): 일단 현재 주소 값 사용 -> 나중에 주소 이동\n");
	printf("4. *(++p): 먼저 주소 이동 -> 새 주소의 값 사용\n");

}
static void prac7()
{
	printf("\n");
	printf("실습VII: 포인터의 형변환\n");

	int data = 0x0A0B0C0D;
	char* pc;
	pc = (char*)&data; //pc에 4바이트 data의 주소 저장

	//[0D,0C,0B,0A] (리틀 엔디언 방식으로 0D를 pc[0]에 저장)

	for (int i = 0; i < 4; i++)
	{
		printf("*(pc + %d) = %02X\n", i, *(pc + i));
	}
}

static void fake_swap(int x, int y)
{
	int tmp;
	printf("x = %d, y = %d\n", x, y);

	tmp = x;
	x = y;
	y = tmp;

	printf("x = %d, y = %d\n", x, y);
}
static void prac8()
{
	printf("\n");
	printf("실습VIII: Call by Value (모델하우스, 서로 위치를 바꾸면 원래 있던 집은 때려 부숴짐)\n");

	int a = 100;
	int b = 200;
	printf("a = %d, b = %d\n", a, b); //100, 200
	fake_swap(a, b); //fake_swap함수에서 x,y,temp가 아무리 wlfkf해도 a,b변수에는 미동 X 
	printf("a = %d, b = %d\n", a, b);
}

static void true_swap(int *x, int *y)
{
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}
static void prac9()
{
	printf("\n");
	printf("실습IX: Call by Reference (이사, 서로 위치를 바꾸면 원래 있던 집은 그대로 유지됨)\n");
	int a = 100, b = 200;
	printf("a = %d, b = %d\n", a, b);
	true_swap(&a, &b);
	printf("a = %d, b = %d\n", a, b);
}

int glp(int x1, int x2, int y1, int y2, float* slope, float* yintercept) //기울기와 y절편을 인수로 전달
{
	if (x1 == x2)
		return -1; //x의 위치가 같으면 x축에 수직인 직선
	else
	{
		*slope = (float)(y2 - y1) / float(x2 - x1); //좌표 인자는 정수고 slope인자는 실수이기 때문에 앞에 float을 붙여서 전환
		*yintercept = y1 - (*slope) *x1; // y = mx + b  =>  b = y - mx (x자리에다가 x1 대입)
		return 0;
	}
}
static void prac10()
{
	printf("\n");
	printf("실습X: 2개 이상의 결과 반환\n");
	float s, y;
	if (glp(3,3,6,6, &s, &y) == -1)
		printf("해당 직선은 x축에 수직인 직선\n");
	else
		printf("기울기는 %f, y절편은 %f\n", s, y);
}
static void prac11()
{
	printf("\n");
	printf("실습XI: Pointer & Array\n");

	int a[] = { 10,20,30,40,50 };
	printf("&a[0] = %u\n", &a[0]);
	printf("&a[1] = %u\n", &a[1]);
	printf("&a[2] = %u\n", &a[2]);	
	printf("a = %u\n\n", a);
	printf("a[i] = *(a+i)\n");
}
static void prac12()
{
	printf("\n");
	printf("실습XII: Pointer & ArrayII\n");

	int a[] = {10,20,30,40,50};
	printf("a = %u\n", a);
	printf("a + 1 = %u\n", a + 1);
	printf("*a = %d\n", *a);
	printf("*(a+1) = %d\n", *(a+1));
}
static void prac13()
{
	printf("\n");
	printf("실습XIII: 포인터를 배열처럼 사용\n");

	int a[] = { 10,20,30,40,50 };
	int* p = NULL;
	p = a;
	printf("a[0]=%d, a[1]=%d, a[2]=%d \n", a[0], a[1], a[2]);
	printf("p[0]=%d, p[1]=%d, p[2]=%d \n\n", p[0], p[1], p[2]); //배열도 결국 포인터로 구현 가능

	p[0] = 60; //*(a), *(p), p[0] 모두 동일
	p[1] = 70;// p[i], a[i], *(p+i), *(a+i) 모두 접근 가능
	p[2] = 80; //포인터를 통하여 배열을 변경 가능

	printf("a[0]=%d, a[1]=%d, a[2]=%d \n", a[0], a[1], a[2]);
	printf("p[0]=%d, p[1]=%d, p[2]=%d \n", p[0], p[1], p[2]);
}

static void print(int a[][SIZE])
{
	for (int r = 0; r < SIZE; r++)
	{
		for (int c = 0; c < SIZE; c++)
		{
			printf("%03d ", a[r][c]);
		}
		printf("\n");
	}
	printf("\n");
}
static void incr(int img[][SIZE])
{
	int* p;
	p = &img[0][0];
	for (int r = 0; r < SIZE; r++)
	{
		for (int c = 0; c < SIZE; c++)
		{	
			*p += 10;
			p++;
		}
	}
}
static void prac14()
{
	printf("\n");
	printf("실습XIV: 포인터를 활용한 영상처리\n");

	int image[5][5] = {
		{10,20,30,40,50},
		{10,20,30,40,50},
		{10,20,30,40,50},
		{10,20,30,40,50},
		{10,20,30,40,50},
	};

	print(image);
	incr(image);
	print(image);
}

