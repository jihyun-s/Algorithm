/*
[�ۼ���] 2016.12.28
[����] ���� ���� https://www.acmicpc.net/problem/1874
���� (stack)�� �⺻���� �ڷᱸ�� �� �ϳ���, ��ǻ�� ���α׷��� �ۼ��� �� ���� �̿�Ǵ� �����̴�. 
������ �ڷḦ �ִ� (push) �Ա��� �ڷḦ �̴� (pop) �Ա��� ���� ���� ���� �� �ڷᰡ ���� ���߿� ������ (FILO, first in last out) Ư���� ������ �ִ�.
1���� n������ ���� ���ÿ� �־��ٰ� �̾� �þ�������ν�, �ϳ��� ������ ���� �� �ִ�. �� ��, ���ÿ� push�ϴ� ������ �ݵ�� ���������� ��Ű���� �Ѵٰ� ����. 
������ ������ �־����� �� ������ �̿��� �� ������ ���� �� �ִ��� ������, �ִٸ� � ������ push�� pop ������ �����ؾ� �ϴ����� �˾Ƴ� �� �ִ�. 
�̸� ����ϴ� ���α׷��� �ۼ��϶�.
[�Է�]
ù �ٿ� n(1��n��100,000)�� �־�����. ��° �ٺ��� n���� �ٿ��� ������ �̷�� 1�̻� n������ ������ �ϳ��� ������� �־�����. 
���� ���� ������ �� �� ������ ���� ����.
[���]
�Էµ� ������ ����� ���� �ʿ��� ������ �� �ٿ� �� ���� ����Ѵ�. push������ +��, pop ������ -�� ǥ���ϵ��� �Ѵ�. 
�Ұ����� ��� NO�� ����Ѵ�.
*/

//#define EXAMPLE_1874
#ifdef EXAMPLE_1874 // ���� ����

#include <stdio.h>
#include<malloc.h>

typedef struct _Node
{
	int nData;
	struct _Node* pNext;
}Node;

Node *head, *tail;
// Stack �ʱ�ȭ 
void init_stack()
{
	head = (Node*)malloc(sizeof(Node));
	tail = (Node*)malloc(sizeof(Node));

	head->pNext = tail;
	tail->pNext = tail;
}

int push_stack(int nData)
{
	Node *p;

	if ((p = (Node*)malloc(sizeof(Node))) == NULL)
	{
		// �Ҵ� ������ ���
		printf("fail to alloc memory!\n");
		return 0;
	}

	p->nData = nData;
	p->pNext = head->pNext;
	head->pNext = p;

	return 1;
}

int pop_stack()
{
	Node *p;
	int nResult;

	if (head->pNext == tail)
	{
		printf("stack underflow!!\n");
		return -1;
	}

	p = head->pNext;
	nResult = p->nData;

	head->pNext = p->pNext;
	free(p);

	return nResult;
}

bool empty()
{
	if (head->pNext == tail)
		return true;
	else
		return false;
}

int top()
{
	if (head->pNext == tail)
		return -1;

	Node *p = head->pNext;
	return p->nData;
}

// head, tail�� ������ ������ node�� ��� ���� 
void clear_stack()
{
	Node *p = head->pNext;

	while (p != tail)
	{
		head->pNext = p->pNext;
		free(p);
		p = head->pNext;
	}
}

int main()
{
	int nCount;
	scanf("%d", &nCount);

	init_stack();

	int nNumber = 1;
	bool bEnable = true;

	char nResult[1000000];
	int nCharIndex = -1;

	int nIndex = 0;

	do {
		int nSearchNum; // = nSeq[nIndex];
		scanf("%d", &nSearchNum);

		while (top() != nSearchNum)
		{
			if (nNumber <= nSearchNum && nNumber <= nCount)
			{
				push_stack(nNumber);
				//printf("+\n");
				nResult[++nCharIndex] = '+';
				nNumber++;
			}
			else
			{
				//printf("NO\n");
				bEnable = false;
				break;
			}
		}

		if (bEnable)
		{
			pop_stack();
			nResult[++nCharIndex] = '-';
			//printf("-\n");	
		}

		nIndex++;
	} while (nIndex < nCount);

	if (bEnable)
	{
		for (int i = 0; i <= nCharIndex; i++)
		{
			printf("%c\n", nResult[i]);
		}
	}
	else
	{
		printf("NO\n");
	}
	clear_stack();

	return 0;
}

#endif