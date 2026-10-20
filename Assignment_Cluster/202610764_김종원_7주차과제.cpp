#include <stdio.h>
#include <string.h>
#include <math.h>
#define SIZE 3
static void prac1();
static void prac2();
static void prac3();
static void prac4();
static void prac5();

//구조체 선언부
//실습I
struct student { //와플 기계
	int number; //System Defined Data Type (원래 있던 자료형)
	char name[10];
	double grade;
};

//실습III
struct point {
	int x;
	int y;
};

//실습IV
struct rect { //구조체 안에 구조체
	struct point p1;
	struct point p2;
};

int main_VII(void)
{
	int choice;

	while (1)
	{
		printf("실행할 실습 번호를 입력하세요(프로그램 종료: 0): ");
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
		default:
			printf("없는 실습 번호입니다. 다시 입력하세요.");
		}

	}
	

	return 0;
}

static void prac1()
{
	printf("\n");
	printf("실습I: 구조체 멤버 참조I\n"); 

	struct student s;

	s.number = 20030001;
	strcpy_s(s.name, sizeof(s.name), "홍길동"); //문자열 복사
	s.grade = 4.3;

	printf("학번: %d\n", s.number);
	printf("이름: %s\n", s.name);
	printf("학점: %.2lf\n", s.grade);

}
static void prac2()
{
	printf("\n");
	printf("실습II: 구조체 멤버 참조II\n");

	struct student s; //학번, 이름, 학점
	printf("학번을 입력하세요.\n");
	scanf_s("%d", &s.number);

	printf("이름을 입력하세요.\n");
	scanf_s("%9s", s.name, (unsigned int)sizeof(s.name));

	printf("학점을 입력하세요.\n");
	scanf_s("%lf", &s.grade);

	printf("학번: %d\n",s.number);
	printf("이름: %s\n", s.name);
	printf("학점: %.2lf\n", s.grade);

}
static void prac3()
{
	printf("\n");
	printf("실습III: 평면상의 점을 구조체로 표현\n");
	
	struct point p1, p2;
	int xdiff, ydiff;
	double dist;

	printf("점의 좌표를 입력하세요 (x,y): ");
	scanf_s("%d %d", &p1.x, &p1.y);

	printf("두번째 점의 좌표를 입력하세요 (x,y): ");
	scanf_s("%d %d", &p2.x, &p2.y);

	xdiff = p1.x - p2.x;
	ydiff = p1.y - p2.y;
	dist = sqrt((double)(xdiff * xdiff + ydiff * ydiff));
	printf("거리는 %lf입니다.\n", dist);

}

static void prac4()
{
	printf("\n");
	printf("실습IV: 구조체 안에 구조체(사각형 넓이 구하기)\n");

	struct rect r;
	int w, h, a, peri;

	printf("좌측 상단의 좌표를 입력하세요: ");
	scanf_s("%d %d", &r.p1.x, &r.p1.y);

	printf("우측 상단의 좌표를 입력하세요. ");
	scanf_s("%d %d", &r.p2.x, &r.p2.y);

	w = abs(r.p2.x - r.p1.x);
	h = abs(r.p2.y - r.p1.y);

	a = w * h;
	peri = 2 * (w + h);

	printf("면적은 %d이고, 둘레는 %d입니다.", a, peri);

}
static void prac5()
{
	struct student list[SIZE];
	
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d번째 학생, 본인의 학번/이름/학점을 입력하세요.\n", i+1);
		scanf_s("%d %s %lf", 
		&list[i].number, 
		list[i].name, (unsigned int)sizeof(list[i].name), 
		&list[i].grade);
	}


}