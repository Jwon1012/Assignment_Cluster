//코딩을 못하면 디버깅이라도 잘하고, 디버깅도 못하면 주석이라도 잘 달자.
#include <stdio.h>
#include <string.h>
#define STU_NUM 1
#define REG_NUM 2
#define SIZE 100

//for 실습II
struct date
{
	int m;
	int d;
	int y;
};

struct student
{
	int snum;
	char name[20];
	double grade;
	struct date *dob; //date에 있는 멤버변수를 포인트
};

//for 실습III
struct vector
{
	double x; 
	double y;
};

struct vector get_vec_sum(struct vector a, struct vector b);

//for 실습V
union example
{
	int i;
	char c;
};

//for 실습VI
struct learner {
	int type;
	union {
		int stu_num; //학번
		char reg_num[15]; //주민등록번호
	} id;
	char name[20];
};

void print(struct learner s);

//for 실습VII

enum days { SUN, MON, TUE, WED, THR, FRI, SAT }; 
//중괄호 안에서 쓰면 #define과 같은 원리로 작동
//일일히 맨 위로 올라가서 #define SIZE 3 이런거 안해도 된다는 의미
//그리고 중괄호 안에 문자열만 있으면 자동적으로 {0, 1, 2, ...} 이런식으로 할당됨
const char* days_name[] = {
	"sunday",
	"monday",
	"tuesday",
	"wednesday",
	"thursday",
	"friday",
	"saturday"
}; //C++에선 문자열이 있는 배열의 개수작질(?)을 엄금 -> 앞에다가 const를 붙임.

//for 실습VIII
typedef struct point {
	int x;
	int y;
}PNT;

PNT translate(PNT p, PNT delta);

//for 실습IX
typedef struct {
	char question[SIZE];
	char item1[SIZE];
	char item2[SIZE];
	char item3[SIZE];
	char item4[SIZE];
	int sol;
} QST;

QST bank[100] = {
	{ "임베디드 장치에 가장 적합한 프로그래밍 언어는?", "1. Python", "2. Java", "3. C", "4. Javascript", 3 },
	{ "서로 다른 자료형을 모을 수 있는 구조는?", "1. array", "2. variable", "3. struct", "4. point", 3 }
};

static void prac2();
static void prac3();
static void prac5();
static void prac6();
static void prac7();
static void prac8();
static void prac9();

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
		case 2:
			prac2();
			break;
		case 3:
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
		default:
			printf("존재하지 않는 실습입니다. 다시 입력하세요.");
			break;
		}
	}

}

static void prac2()
{
	printf("\n");
	printf("실습 II: 포인터를 멤버로 갖는 구조체\n");

	struct date d = { 10, 12, 2026 };
	struct student s = { 202610764, "Kim", 4.3};

	s.dob = &d; 

	printf("학번: %d, 이름: %s, 학점: %lf\n", s.snum, s.name, s.grade);
	printf("생년월일: %d년 %d월 %d일\n", s.dob->y, s.dob->m, s.dob->d);
}
struct vector get_vec_sum(struct vector a, struct vector b)
{
	struct vector result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;

	return result;
}

static void prac3()
{
	printf("\n");
	printf("실습 III: 벡터의 합 구하기");

	struct vector a = { 2.0, 3.0 };
	struct vector b = { 5.0, 6.0 };
	struct vector sum;

	sum = get_vec_sum(a, b);
	printf("두 벡터 (%0.lf, %.0lf) (%.0lf, %.0lf)의 합은 (%.0lf, %.0lf)입니다. \n", a.x, a.y, b.x, b.y, sum.x, sum.y);
}

static void prac5()
{
	printf("\n");
	printf("실습 V: Union \n");

	union example v;
	v.c = 'A';
	printf("v.c = %c, v.i = %d\n", v.c, v.i);

	v.i = 2;
	printf("v.c = %c, v.i = %d\n",v.c, v.i);

	printf("\nstruct는 한 집에 각방, union은 한 방에 같이 사는 꼴.\n");
}
void print(struct learner s)
{
	switch (s.type)
	{
	case STU_NUM:
		printf("학번: %d, 이름: %s\n", s.id.stu_num, s.name);
		break;
	case REG_NUM:
		printf("주민등록번호: %s, 이름: %s\n", s.id.reg_num, s.name);
		break;
	default:
		printf("타입 오류\n");
	}

}
static void prac6()
{
	printf("\n");
	printf("실습 VI: 학번이름주민등록번호\n");
	
	struct learner s1, s2;
	s1.type = STU_NUM;
	strcpy_s(s1.name, "홍길동");
	s1.id.stu_num = 20190001;

	s2.type = REG_NUM;
	strcpy_s(s2.id.reg_num, "860101-1056076");
	strcpy_s(s2.name, "김철수");

	print(s1);
	print(s2);
}

static void prac7()
{
	printf("\n");
	printf("실습 VI: enum(열거형) \n");
	enum days d;
	d = WED;
	printf("%d번째 요일은 %s입니다.\n", d, days_name[d]);
	printf("cf. 정수 사용: 컴퓨터는 알기 쉽지만 사용자는 어려움.");
	printf("#define을 통한 기호 상수 : 쓸때 오류를 저지를 수도 있고 함수 안에서 써야할때마다 굳이굳이 위로 올라가서 다른 변수로 정의해야함 \n");
	printf("enum을 이용한 열거형: 컴파일러가 중복여부를 확인하고 main위에다가 쓰면 #define처럼 쓸 수 있음. \n");

}
PNT translate(PNT p, PNT delta)
{
	PNT result = {};
	result.x = p.x + delta.x;
	result.y = p.y + delta.y;
	return result;
}
static void prac8()
{
	printf("\n");
	printf("실습 VII: typedef (2차원 공간상의 점을 PNT로 정의)\n");

	PNT p = { 2, 3 };
	PNT delta = { 10, 10 };
	PNT result; //하나하나 앞에 struct 안붙여도 됨 (개꿀)

	result = translate(p, delta);

	printf("(%d %d) + (%d %d) -> (%d %d)\n", p.x, p.y, delta.x, delta.y, result.x, result.y);

}

static void prac9()
{
	printf("\n");
	printf("실습 IX: 4지선다 퀴즈 프로그램\n");

	int select, cnt = 0;
	for (int i = 0; i < 2; i++)
	{
		printf("%s \n", bank[i].question);
		printf("%s ", bank[i].item1);
		printf("%s ", bank[i].item2);
		printf("%s ", bank[i].item3);
		printf("%s ", bank[i].item4);
		scanf_s("%d", &select);
		if (select == bank[i].sol)
		{
			printf("정답입니다!. \n");
			cnt++;
		}
		else
			printf("오답입니다.\n");
	}

	printf("문제의 총 정답개수: %d, 오답개수: %d\n", cnt, 2 - cnt);
}