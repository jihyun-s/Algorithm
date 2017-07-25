/* [�ۼ���] 2016.12.29
[����] ������ https://www.acmicpc.net/problem/1406
�� �ٷ� �� ������ �����͸� �����Ϸ��� �Ѵ�. �� ������� ���� �ҹ��ڸ��� ����� �� �ִ� �������, �ִ� 600,000���ڱ��� �Է��� �� �ִ�.
�� �����⿡�� 'Ŀ��'��� ���� �ִµ�, Ŀ���� ������ �� ��(ù ��° ������ ����), ������ �� ��(������ ������ ������), �Ǵ� ���� �߰� ������ ��(��� ���ӵ� �� ���� ����)�� ��ġ�� �� �ִ�. 
�� ���̰� L�� ���ڿ��� ���� �����⿡ �ԷµǾ� ������, Ŀ���� ��ġ�� �� �ִ� ���� L+1���� ��찡 �ִ�.
�� �����Ⱑ �����ϴ� ��ɾ�� ������ ����.
L	Ŀ���� �������� �� ĭ �ű� (Ŀ���� ������ �� ���̸� ���õ�)
D	Ŀ���� ���������� �� ĭ �ű� (Ŀ���� ������ �� ���̸� ���õ�)
B	Ŀ�� ���ʿ� �ִ� ���ڸ� ������ (Ŀ���� ������ �� ���̸� ���õ�)
������ ���� Ŀ���� �� ĭ �������� �̵��� ��ó�� ��Ÿ������, ������ Ŀ���� �����ʿ� �ִ� ���ڴ� �״����
P $	$��� ���ڸ� Ŀ�� ���ʿ� �߰���
�ʱ⿡ �����⿡ �ԷµǾ� �ִ� ���ڿ��� �־�����, �� ���� �Է��� ��ɾ ���ʷ� �־����� ��, ��� ��ɾ �����ϰ� �� �� �����⿡ �ԷµǾ� �ִ� ���ڿ��� ���ϴ� ���α׷��� �ۼ��Ͻÿ�. ��, ��ɾ ����Ǳ� ���� Ŀ���� ������ �� �ڿ� ��ġ�ϰ� �ִٰ� �Ѵ�.
[�Է�]
ù° �ٿ��� �ʱ⿡ �����⿡ �ԷµǾ� �ִ� ���ڿ��� �־�����. �� ���ڿ��� ���� �ҹ��ڷθ� �̷���� ������, ���̴� 100,000�� ���� �ʴ´�. ��° �ٿ��� �Է��� ��ɾ��� ������ ��Ÿ���� ���� N(1��N��500,000)�� �־�����. 
��° �ٺ��� N���� �ٿ� ���� �Է��� ��ɾ ������� �־�����. ��ɾ�� ���� �� ���� �� �ϳ��� ���·θ� �־�����.
[���]
ù° �ٿ� ��� ��ɾ �����ϰ� �� �� �����⿡ �ԷµǾ� �ִ� ���ڿ��� ����Ѵ�.
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

// ��带 ����ϴ� �Լ�
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

// Ŀ���� �������� ��ĭ �̵���Ű�� �Լ�
int move_cursor_to_left()
{
	DNode* p = cursor->prev;			// ���� node�� ����

	if (p == head)						// Ŀ���� ������ �� ���� ���
		return 0;

	// p Ŀ�� q => Ŀ�� p q
	cursor->prev = p->prev;				// Ŀ���� ������ p�� ���� node�̴�.

	p->next = cursor->next;				// ���� node�� ������ Ŀ�� ���� node�̴�.
	p->prev = cursor;					// Ŀ���� p�� �������� �̵�

	cursor->next = p;					// Ŀ���� ������ ���� node�̴�.
	cursor->prev->next = cursor;

	p->next->prev = p;

	return 1;
}

// Ŀ���� ���������� ��ĭ �̵���Ű�� �Լ�
int move_cursor_to_right()
{
	DNode* p = cursor->next;			// ���� node�� ����

	if (p == tail)						// Ŀ���� ������ �� ���� ���
		return 0;

	// Ŀ�� p q => p Ŀ�� q
	cursor->next = p->next;

	p->next = cursor;
	p->prev = cursor->prev;
	p->prev->next = p;

	cursor->prev = p;
	cursor->next->prev = cursor;

	//print_dnode();

	return 1;
}

// Ŀ���� ���� ���ڸ� �����ϴ� �Լ� 
int delete_dnode_left_cursor()
{
	DNode* p = cursor->prev;		// ������ node

	if (p == head)					// ������ �� ���� ��� ����
		return 0;

	// p Ŀ�� q => Ŀ�� p q
	cursor->prev = p->prev;				// Ŀ���� ������ p�� ���� node�̴�.
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

	while ((ch = getchar()) != EOF && ch != '\n')	// �� ���ھ� �Է¹���
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