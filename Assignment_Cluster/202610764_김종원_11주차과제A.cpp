#define _CRT_SECURE_NO_WARNINGS // 안전하지 않은 함수 경고 무시
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
//for 예제15 응용
typedef enum {
	SEQ_FIRST,
	SEQ_SECOND,
	SEQ_THIRD,
	SEQ_FOURTH,
	SEQ_FIFTH,
	SEQ_XIXTH,
	SEQ_SEVENTH,
	SEQ_EIGHTH,
	SEQ_NINTH,
	SEQ_TENTH,
	SEQ_COUNT //제미나이 왈: 총 개수를 세주는 실무 꿀팁 ※ 이미 이 값은 5라고 저장되어 있기 때문.
}KorSeq;

const char* kor_seq[SEQ_COUNT]
{
	"첫", "두", "세", "네", "다섯", "여섯", "일곱", "여덟", "아홉", "열"
};

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

int main_XI(void)
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

static void example1() 
{
	printf("\n");
	printf("예제I: ");

	int i = 0;
	char str[4] = { 0, };
	char* pStr = NULL;

	pStr = str;
	const char* Hello_str = "Welcome to Korea"; 
	//welcome to korea라는 문자열이
	//어딘가에 저장되어 있는데 상수인 놈을 못바꿈
	char Hello_str2[100]; //이놈은 공간을 만들어서 처리하기 떄문에 수정할 수 있음.

	Hello_str2[0] = 'W';
	Hello_str2[1] = 'e';
	
	str[0] = 'a';
	str[1] = 'b';
	str[2] = 'c';
	str[3] = '\0'; //이 문자열의 끝을 알려주는 문자

	while (str[i] != '\0')
	{
		printf("%c", str[i]);
		i++;
	}

	pStr[0] = 'A';
	pStr[1] = 'B';
	pStr[2] = 'C';
	pStr[3] = '\0';

	while (str[i] != '\0')
	{
		printf("%c", str[i]);
		i++;
	}
}
static void example2() 
{
	printf("\n");
	printf("예제II: ");

	char str1[6] = "Seoul";
	char str2[3] = { 'i','s','\0' };
	char str3[] = "the capital city of Korea";

	printf("%s %s %s.\n", str1, str2, str3);
}
static void example3() 
{
	printf("\n");
	printf("예제III: Source & Destination ");

	char src[] = "Action speaks louder than words";
	char dst[100];

	int i;
	printf("원본 문자열=%s\n", src);
	for (i = 0; src[i] != '\0'; i++)
	{
		dst[i] = src[i];
	}

	dst[i] = '\0';
	printf("복사된 문자열=%s\n", dst);

}
static void example4() 
{
	printf("\n");
	printf("예제IV: ");

	const char* p = "HelloWorld";
	printf("%s\n", p);

	p = "Welcome to C World!"; //가능
	printf("%s\n", p);

	p = "Goodbye"; //이것도 가능
	printf("%s\n", p);
	//p[0] = a 이건 불가능, ※배열은 변경 불가능한 포인터이기 때문.
}
static void example5() 
{
	printf("\n");
	printf("예제V: scanf_s\n");

	char name[100];
	char address[100];

	printf("이름을 입력하시오. ");
	scanf_s("%s", name,(unsigned int)sizeof(name));
	printf("현재 거주하는 주소를 입력하시오. ");
	scanf_s("%s", address, (unsigned int)sizeof(address));

	printf("안녕하세요. %s에 사는 %s씨.\n\n", address, name);

}

static void example6() 
{
	printf("\n");
	printf("예제VI: gets_s\n");

	char name[100];
	char address[100];

	printf("이름을 입력하세요. ");
	gets_s(name, sizeof(name));
	printf("현재 거주하는 주소를 입력하세요. ");
	gets_s(address, sizeof(address));

	printf("안녕하세요. %s에 사는 %s씨.\n", address, name);

	printf("cf) scanf_s는 공백을 인식 못하지만 gets_s는 쌉가능.\n");
	printf("대신 get_s위에 scanf_s를 입력하면 다음 줄에다가 while (getchar() != '\n'); 입력 필수\n");
}
static void example7() 
{
	printf("\n");
	printf("예제 VII: 소문자 -> 대문자\n");

	int c = 0;
	while ((c = getchar()) != EOF) //End of File의 약자
	{
		if (islower(c))
			c = toupper(c);
		putchar(c);
	}

}
static void example8() 
{
	printf("\n");
	printf("예제 VIII: strcpy & strcat\n");

	char str[80];

	strcpy_s(str, "Hello World From "); //문자열 복사
	strcat_s(str, "strcpy"); //끝에 붙여넣기
	strcat_s(str, "and "); //끝에 붙여넣기
	strcat_s(str, "strcat!"); //끝에 붙여넣기
	printf("string = %s\n", str);
}
static void example9() 
{
	printf("\n");
	printf("예제 IX: strcmp\n");

	char s1[80];
	char s2[80];
	int result;

	printf("첫번째 단어를 입력하세요. ");
	gets_s(s1, sizeof(s1));
	printf("두번째 단어를 입력하세요. ");
	gets_s(s2, sizeof(s2));

	result = strcmp(s1, s2);

	if (result < 0) printf("%s이 %s앞에 있습니다.", s1, s2);
	else if (result == 0) printf("두 문자열이 완전히 같습니다.");
	else printf("%s이 %s뒤에 있습니다.", s1, s2);
}

static void example10() 
{
	printf("\n");
	printf("예제 X: strchr\n");

	char s[] = "language";
	char c = 'g';
	char* p = NULL;
	int loc;

	p = strchr(s, c);
	if (p == NULL) printf("%c가 발견되지 않았음.", c);
	else
	{
		loc = int(p - s);
		printf("%s에서 첫번째 %c가 %d에서 발견되었음.\n", s, c, loc);
	}
}
static void example11() 
{
	printf("\n");
	printf("예제 XI: strstr\n");

	char s[] = "A bird in hand is worth two in the bush";
	const char* sub = "bird";
	char* p = NULL;
	int loc;

	p = strstr(s, sub);
	if (p == NULL) printf("%s가 발견되지 않았음.\n", sub);
	else
	{
		loc = int(p - s);
		printf("%s에서 첫번째 %s가 %d에서 발견되었음.\n", s, sub, loc);
	}
}
static void example12() 
{
	printf("\n");
	printf("예제 XII: strtok\n");
	char* context = NULL; //자르고 남은 주소를 보관할 변수, strtok만 쓴다면 이건 필요 X
	char s[] = "Man is immortal, because he has a soul.\n";
	char* t1 = strtok_s(s, " ", &context); //Man
	char* t2 = strtok_s(NULL, " ", &context); //is
	char* t3 = strtok_s(NULL, " ", &context); //immortal
	char* t4 = strtok_s(NULL, " ", &context); //because
}
static void example13() 
{
	printf("\n");
	printf("예제 XIII: strtok을 이용한 분리\n");

	char s[] = "Man is immortal, because he has a soul.\n";
	char seps[] = " ,\t\n"; //문자열 분리자, 공백/콤마/탭/엔터 단위로 토큰 분리
	char* context = NULL; //자르고 남은 주소를 보관할 변수

	char* token = strtok_s(s, seps, &context); //s라는 문자열에서 공백/콤마/탭/엔터를 만나면 쪼개라는 명령
	while (token != NULL)
	{
		//문자열 s에 토큰이 있는동안 반복.
		printf("토큰: %s\n", token);
		//다음 토큰 획득
		token = strtok_s(NULL, seps, &context);
	}
}
static void example14() 
{
	printf("\n");
	printf("예제 XIV:sscanf, snprintf\n");

	char instring[] = "file 12";
	char name[10];
	char buffer[50];
	int x = 10, y = 20, result = 0;
	int num = 0;
	(void)sscanf(instring, "%s %d", name, &num); //반환값이 무시되었다는 경고 무시하기 위해 앞에 (void)

	result = x + y;
	snprintf(buffer, sizeof(buffer), "%d + %d = %d", x, y, result);

	printf("name = %s \n", name);
	printf("number = %d\n", num);

	printf("%s\n", buffer);

}
static void example15() 
{
	printf("\n");
	printf("예제 XV: array cubic(?)\n");

	char menu[5][10]
	{
		"init",
		"open",
		"close",
		"read",
		"write"
	};

	printf("포인터 응용해서 1,2,3번째를 각각 첫,두,세번째로 바꾸기\n");
	
	for (int i = 0; i < 5; i++)
	{
		printf("%s번째 메뉴: %s\n", kor_seq[i], menu[i]);
	}
}

static void example16() 
{
	printf("\n");
	printf("예제 XVI: 2차원 배열로 입력\n");

	char fruits[3][20];
	for (int i = 0; i < 3; i++)
	{
		printf("과일 이름을 입력하세요.");
		gets_s(fruits[i], sizeof(fruits[i]));
	}

	for (int i = 0; i < 3; i++) (void)printf("%d번째 과일: %s\n", kor_seq[i], fruits[i]);
}