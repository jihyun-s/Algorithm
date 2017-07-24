/*
[�ۼ���]
2016.12.28

[����] ���� https://www.acmicpc.net/problem/10828
������ �����ϴ� ������ ������ ����, �Է����� �־����� ����� ó���ϴ� ���α׷��� �ۼ��Ͻÿ�.
����� �� �ټ� �����̴�.
push X: ���� X�� ���ÿ� �ִ� �����̴�.
pop: ���ÿ��� ���� ���� �ִ� ������ ����, �� ���� ����Ѵ�. ���� ���ÿ� ����ִ� ������ ���� ��쿡�� -1�� ����Ѵ�.
size: ���ÿ� ����ִ� ������ ������ ����Ѵ�.
empty: ������ ��������� 1, �ƴϸ� 0�� ����Ѵ�.
top: ������ ���� ���� �ִ� ������ ����Ѵ�. ���� ���ÿ� ����ִ� ������ ���� ��쿡�� -1�� ����Ѵ�.
[�Է�]
ù° �ٿ� �־����� ����� �� N (1 �� N �� 10,000)�� �־�����. ��° �ٺ��� N���� �ٿ��� ����� �ϳ��� �־�����. 
�־����� ������ 1���� ũ�ų� ����, 100,000���� �۰ų� ����. ������ �������� ���� ����� �־����� ���� ����.
[���]
����ؾ��ϴ� ����� �־��� ������, �� �ٿ� �ϳ��� ����Ѵ�.
*/

#define EXAMPLE_10828
#ifdef EXAMPLE_10828 // ����

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