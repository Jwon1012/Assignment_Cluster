#define _CRT_SECURE_NO_WARNINGS // 안전하지 않은 함수 경고 무시
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static void Lab1();
int cnt_word(char* s);
static void Lab2();
char check_pw(char* s);
static void Lab3();
static void Lab4();
static void Lab5();
static void Lab6();
//for Lab5
typedef struct {
	char eng[30];
	char kor[50];
} Word; //빵틀 (밀가루고 뭐고 없는 그냥 쇠통)
Word dict[] =
{
	{ "apple", "사과" },
	{ "boy", "소년" },
	{ "candy", "사탕" }
}; //쟁반에 올려놓을 진짜 빵틀

//for Lab6
void encrypt(char chiper[], int shift);

int main(void)
{
	int choice = 0;
	while (1)
	{
		printf("실행하고싶은 실험 번호를 입력하세요. (0: 프로그램 종료, 1~6) ");
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
		case 1: Lab1(); break;
		case 2: Lab2(); break;
		case 3: Lab3(); break;
		case 4: Lab4(); break;
		case 5: Lab5(); break;
		case 6: Lab6(); break;
		default: printf("존재하지 않는 실습 번호입니다. 다시 입력하세요."); break;
		}
	}
	return 0;
}

int cnt_word(char* s)
{
	int cnt = 0;
	int waiting = 1;
	for (int i = 0; s[i] != NULL; i++) //s의 각 글자 조사
	{
		if (isalpha(*(s + i))) //단어의 글자가 알파벳이면
		{
			if (waiting) //단어를 기다리는 중이라면
			{
				cnt++;
				waiting = 0; //단어를 처리하는 중
			}
		}
		else if (!waiting && s[i] == '\'')
			waiting = 0;
		else
			waiting = 1;
	}

	return cnt;
}
static void Lab1() 
{
	printf("\n");
	printf("Lab I: Word Counter\n");
	printf("영문장을 입력하세요. ");
	char c[100];
	gets_s(c, sizeof(c));
	int cnt = cnt_word(c);
	printf("단어의 개수: %d\n", cnt);
}

char check_pw(char* s)
{
	int i = 0;
	int upper_count = 0;
	int lower_count = 0;
	int num_count = 0;
	for (i = 0; *(s + i) != '\0'; i++)
	{
		if (isupper(s[i])) upper_count++;
		if (islower(s[i])) lower_count++;
		if (isdigit(s[i])) num_count++;
	}

	if (upper_count == 0 || lower_count == 0 || num_count == 0)
		return 1;
	else if (i < 7 || i > 30)
		return 1;
	else
		return 0;
}

static void Lab2() 
{
	printf("\n");
	printf("Lab II: Password Setting.\n");
	char set_pw[100];
	printf("Conditions:\n\n");
	printf("1. Your Password len should be 7~30 Words\n\n");
	printf("2. You should maintain at least one upper/lower letter & number.\n\n");
	printf("Now write down your password. ");
	while (1)
	{
		gets_s(set_pw, sizeof(set_pw));
		if (check_pw(set_pw) == 1)
			printf("It is Weak Password, write again. ");
		if (check_pw(set_pw) == 0)
		{
			printf("It's a strong password. saved.\n");
			break;
		}
	}

}
static void Lab3() 
{
	printf("\n");
	printf("Lab III: Write down answer. \n");

	char key[] = "C";
	char buffer[80] = "";
	do
	{
		printf("임베디드 장치에 가장 많이 사용되는 언어는? ");
		gets_s(buffer, sizeof(buffer));
	} while (strcmp(key, buffer) != 0);

	printf("정답입니다! \n");
}

static void Lab4() 
{
	printf("\n");
	printf("Lab IV: 파일이름 양산 프로그램 \n");

	char img[50];
	char exten[] = ".jpg";
	int amount = 0;

	printf("몇개의 이미지 파일을 생성하시겠습니까? ");
	(void)scanf("%d", &amount);

	for (int i = 0; i < amount; i++)
	{
		snprintf(img, sizeof(img), "%s%03d%s", "image", i, exten);
		printf("%s \n", img);
	}
}
static void Lab5() 
{
	char input[30];
	int found = 0;
	printf("\n");
	printf("Lab V: 한영사전 \n");
	printf("단어를 입력하세요. ");

	Word* p = dict; //쟁반의 첫번째빵 dict[0]을 가리키는 집게

	while (1)
	{
		gets_s(input, sizeof(input));
		for (int i = 0; i < sizeof(dict) / sizeof(dict[0]); i++)
		{
			if (strcmp(input, (p + i)->eng) == 0) { printf("%s: %s\n", input, (p + i)->kor); found = 1; break; }
			//만약 input과 i번째 빵에 있는 재료인 eng과 같다면/그 빵을 갈라서 kor라는 재료를 뱉어낸 다음 쟁반 뒤지기 멈춰!
		}

		if (found == 1) break;
		else printf("없는 단어입니다. 다시 찾아보세요. ");
	}
}

void encrypt(char chiper[], int shift)
{
	int i = 0;
	//char* p= chiper를 쓰면 i안붙여도 상관 X ※chiper[i] = *(p + i)
	while (chiper[i] != '\0')
	{
		if (chiper[i] >= 'a' && chiper[i] <= 'z')
		{
			chiper[i] += shift; // 문자열이 a,b,c형식이면 세칸 이동해서 d,e,f로 출력
			if (chiper[i] > 'z') chiper[i] -= 26; //문자열에 x,y,z면 다시 돌아가서 a,b,c로 출력
		}
		i++;
	}

	printf("암호화된 문자열: %s", chiper);
}
static void Lab6() 
{
	printf("\n");
	printf("Lab VI: 메시지 암호화 \n");

	char cipher[100];
	int shift = 3;

	printf("문자열을 입력하시오. ");
	gets_s(cipher, sizeof(cipher)); //한줄 전체 입력

	encrypt(cipher, shift);
}