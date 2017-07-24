/*
[작성일]
2016.12.28

[문제] 스택 https://www.acmicpc.net/problem/10828
정수를 저장하는 스택을 구현한 다음, 입력으로 주어지는 명령을 처리하는 프로그램을 작성하시오.
명령은 총 다섯 가지이다.
push X: 정수 X를 스택에 넣는 연산이다.
pop: 스택에서 가장 위에 있는 정수를 빼고, 그 수를 출력한다. 만약 스택에 들어있는 정수가 없는 경우에는 -1을 출력한다.
size: 스택에 들어있는 정수의 개수를 출력한다.
empty: 스택이 비어있으면 1, 아니면 0을 출력한다.
top: 스택의 가장 위에 있는 정수를 출력한다. 만약 스택에 들어있는 정수가 없는 경우에는 -1을 출력한다.
[입력]
첫째 줄에 주어지는 명령의 수 N (1 ≤ N ≤ 10,000)이 주어진다. 둘째 줄부터 N개의 줄에는 명령이 하나씩 주어진다. 
주어지는 정수는 1보다 크거나 같고, 100,000보다 작거나 같다. 문제에 나와있지 않은 명령이 주어지는 경우는 없다.
[출력]
출력해야하는 명령이 주어질 때마다, 한 줄에 하나씩 출력한다.
*/

#define EXAMPLE_10828
#ifdef EXAMPLE_10828 // 스택

#include <iostream>
#include <string.h>
using namespace std;

#define STACK_MAX_SIZE 10000
class Stack
{
	int nStack[STACK_MAX_SIZE];
	int nTop;

public:
	Stack()
	{
		nTop = -1;
	}
	~Stack()
	{

	}
	bool push(int nX)
	{
		if (nTop == STACK_MAX_SIZE - 1)
			return false;

		nStack[++nTop] = nX;
		return true;
	}

	int pop()
	{
		if (nTop == -1)
			return -1;

		int nResult = nStack[nTop--];
		return nResult;
	}

	int size()
	{
		return nTop + 1;
	}

	bool empty()
	{
		if (nTop == -1)
			return true;
		else
			return false;
	}
	int top()
	{
		if (nTop == -1)
			return -1;

		return nStack[nTop];
	}
};


int main()
{
	int nCount;
	scanf("%d", &nCount);

	Stack* aStack = new Stack;

	char commend[10] = { 0, };
	int nData;

	while (nCount > 0)
	{
		nData = -1;
		scanf("%s", &commend);

		if (strcmp(commend, "push") == 0)
		{
			scanf("%d", &nData);
			if (nData != -1)
				aStack->push(nData);
		}
		else if (strcmp(commend, "top") == 0)
		{
			printf("%d\n", aStack->top());
		}
		else if (strcmp(commend, "size") == 0)
		{
			printf("%d\n", aStack->size());
		}
		else if (strcmp(commend, "empty") == 0)
		{
			printf("%d\n", aStack->empty());
		}
		else if (strcmp(commend, "pop") == 0)
		{
			printf("%d\n", aStack->pop());
		}
		else
		{
			printf("command error!!");
		}
		nCount--;
	}

	delete aStack;

	return 0;
}

#endif