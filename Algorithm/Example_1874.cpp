/*
[작성일] 2016.12.28
[문제] 스택 수열 https://www.acmicpc.net/problem/1874
스택 (stack)은 기본적인 자료구조 중 하나로, 컴퓨터 프로그램을 작성할 때 자주 이용되는 개념이다. 
스택은 자료를 넣는 (push) 입구와 자료를 뽑는 (pop) 입구가 같아 제일 먼저 들어간 자료가 제일 나중에 나오는 (FILO, first in last out) 특성을 가지고 있다.
1부터 n까지의 수를 스택에 넣었다가 뽑아 늘어놓음으로써, 하나의 수열을 만들 수 있다. 이 때, 스택에 push하는 순서는 반드시 오름차순을 지키도록 한다고 하자. 
임의의 수열이 주어졌을 때 스택을 이용해 그 수열을 만들 수 있는지 없는지, 있다면 어떤 순서로 push와 pop 연산을 수행해야 하는지를 알아낼 수 있다. 
이를 계산하는 프로그램을 작성하라.
[입력]
첫 줄에 n(1≤n≤100,000)이 주어진다. 둘째 줄부터 n개의 줄에는 수열을 이루는 1이상 n이하의 정수가 하나씩 순서대로 주어진다. 
물론 같은 정수가 두 번 나오는 일은 없다.
[출력]
입력된 수열을 만들기 위해 필요한 연산을 한 줄에 한 개씩 출력한다. push연산은 +로, pop 연산은 -로 표현하도록 한다. 
불가능한 경우 NO를 출력한다.
*/

//#define EXAMPLE_1874
#ifdef EXAMPLE_1874 // 스택 수열

#include <stdio.h>
#include<malloc.h>

typedef struct _Node
{
	int nData;
	struct _Node* pNext;
}Node;

Node *head, *tail;
// Stack 초기화 
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
		// 할당 실패한 경우
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

// head, tail을 제외한 나머지 node를 모두 제거 
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