/* [작성일] 2016.12.29
[문제] 에디터 https://www.acmicpc.net/problem/1406
한 줄로 된 간단한 에디터를 구현하려고 한다. 이 편집기는 영어 소문자만을 기록할 수 있는 편집기로, 최대 600,000글자까지 입력할 수 있다.
이 편집기에는 '커서'라는 것이 있는데, 커서는 문장의 맨 앞(첫 번째 문자의 왼쪽), 문장의 맨 뒤(마지막 문자의 오른쪽), 또는 문장 중간 임의의 곳(모든 연속된 두 문자 사이)에 위치할 수 있다. 
즉 길이가 L인 문자열이 현재 편집기에 입력되어 있으면, 커서가 위치할 수 있는 곳은 L+1가지 경우가 있다.
이 편집기가 지원하는 명령어는 다음과 같다.
L	커서를 왼쪽으로 한 칸 옮김 (커서가 문장의 맨 앞이면 무시됨)
D	커서를 오른쪽으로 한 칸 옮김 (커서가 문장의 맨 뒤이면 무시됨)
B	커서 왼쪽에 있는 문자를 삭제함 (커서가 문장의 맨 앞이면 무시됨)
삭제로 인해 커서는 한 칸 왼쪽으로 이동한 것처럼 나타나지만, 실제로 커서의 오른쪽에 있던 문자는 그대로임
P $	$라는 문자를 커서 왼쪽에 추가함
초기에 편집기에 입력되어 있는 문자열이 주어지고, 그 이후 입력한 명령어가 차례로 주어졌을 때, 모든 명령어를 수행하고 난 후 편집기에 입력되어 있는 문자열을 구하는 프로그램을 작성하시오. 단, 명령어가 수행되기 전에 커서는 문장의 맨 뒤에 위치하고 있다고 한다.
[입력]
첫째 줄에는 초기에 편집기에 입력되어 있는 문자열이 주어진다. 이 문자열은 영어 소문자로만 이루어져 있으며, 길이는 100,000을 넘지 않는다. 둘째 줄에는 입력할 명령어의 개수를 나타내는 정수 N(1≤N≤500,000)이 주어진다. 
셋째 줄부터 N개의 줄에 걸쳐 입력할 명령어가 순서대로 주어진다. 명령어는 위의 네 가지 중 하나의 형태로만 주어진다.
[출력]
첫째 줄에 모든 명령어를 수행하고 난 후 편집기에 입력되어 있는 문자열을 출력한다.
*/

//#define PROBLEM_1406
#ifdef PROBLEM_1406
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct _dnode
{
	char str;
	struct _dnode *prev;
	struct _dnode *next;
}DNode;

DNode *head, *tail;
DNode *cursor;

void init_dnode()
{
	head = (DNode*)malloc(sizeof(DNode));
	tail = (DNode*)malloc(sizeof(DNode));
	cursor = (DNode*)malloc(sizeof(DNode));

	head->prev = head;
	head->next = cursor; //tail;

	cursor->prev = head;
	cursor->next = tail;

	tail->prev = cursor; //head;
	tail->next = tail;
}

// 노드를 출력하는 함수
void print_dnode()
{
	DNode* p = head->next;
	int nCount = 0;

	while (p != tail)
	{
		nCount++;

		if (p != cursor)
			printf("%c", p->str);
		//else
		//printf("[cur]");

		p = p->next;
	}

	printf("\n");
}

int insert_dnode_after_cursor(char c)
{
	DNode* p;

	p = (DNode*)malloc(sizeof(DNode));

	if (p == NULL)
		return 0;

	p->str = c;
	p->next = cursor->next;
	p->prev = cursor;

	cursor->next->prev = p;
	cursor->next = p;


	//print_dnode();
	return 1;
}

// 커서를 왼쪽으로 한칸 이동시키는 함수
int move_cursor_to_left()
{
	DNode* p = cursor->prev;			// 이전 node를 저장

	if (p == head)						// 커서가 문장의 맨 앞인 경우
		return 0;

	// p 커서 q => 커서 p q
	cursor->prev = p->prev;				// 커서의 이전은 p의 이전 node이다.

	p->next = cursor->next;				// 이전 node의 다음은 커서 다음 node이다.
	p->prev = cursor;					// 커서를 p의 이전으로 이동

	cursor->next = p;					// 커서의 다음은 이전 node이다.
	cursor->prev->next = cursor;

	p->next->prev = p;

	return 1;
}

// 커서를 오른쪽으로 한칸 이동시키는 함수
int move_cursor_to_right()
{
	DNode* p = cursor->next;			// 다음 node를 저장

	if (p == tail)						// 커서가 문장의 맨 뒤인 경우
		return 0;

	// 커서 p q => p 커서 q
	cursor->next = p->next;

	p->next = cursor;
	p->prev = cursor->prev;
	p->prev->next = p;

	cursor->prev = p;
	cursor->next->prev = cursor;

	//print_dnode();

	return 1;
}

// 커서의 왼쪽 문자를 삭제하는 함수 
int delete_dnode_left_cursor()
{
	DNode* p = cursor->prev;		// 삭제할 node

	if (p == head)					// 문장의 맨 앞인 경우 무시
		return 0;

	// p 커서 q => 커서 p q
	cursor->prev = p->prev;				// 커서의 이전은 p의 이전 node이다.
	cursor->prev->next = cursor;

	free(p);

	return 1;
}

int main()
{
	char ch;
	int nCount;
	char commend[10] = { 0, };

	init_dnode();

	while ((ch = getchar()) != EOF && ch != '\n')	// 한 문자씩 입력받음
	{
		insert_dnode_after_cursor(ch);
		move_cursor_to_right();
	}

	scanf("%d\n", &nCount);

	while (nCount > 0)
	{
		scanf("%s", &commend);

		if (strcmp(commend, "L") == 0)
			move_cursor_to_left();
		else if (strcmp(commend, "D") == 0)
			move_cursor_to_right();
		else if (strcmp(commend, "B") == 0)
			delete_dnode_left_cursor();
		else if (strcmp(commend, "P") == 0)
		{
			scanf("%s", &commend);
			ch = commend[0];
			insert_dnode_after_cursor(ch);
			move_cursor_to_right();
		}
		//print_dnode();
		//printf("\n");

		nCount--;
	}

	print_dnode();

	free(cursor);
	free(head);
	free(tail);

	//scanf("%d", &nCount);

	return 0;
}

#endif