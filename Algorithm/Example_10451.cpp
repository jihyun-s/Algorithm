/* [�ۼ���] 2017.01.05
[����] ���� ����Ŭ https://www.acmicpc.net/problem/10451
1���� N���� ���� N���� �̷���� ������ ��Ÿ���� ����� ���������� �ִ�. 
���� ���, 8���� ���� �̷���� ���� (3, 2, 7, 8, 1, 4, 5, 6)�� �迭�� �̿��� ǥ���ϸ� (1234567832781456) �� ����. 
�Ǵ�, Figure 1�� ���� ���� �׷����� ��Ÿ�� ���� �ִ�.
������ �迭�� �̿��� (1��i��n��1����i����n) �� ��Ÿ�´ٸ�, i���� ��i�� ������ �̾� �׷����� ���� �� �ִ�.
Figure 1�� �����ִ� �� ó��, ���� �׷��� (3, 2, 7, 8, 1, 4, 5, 6) ���� �� 3���� ����Ŭ�� �ִ�. �̷��� ����Ŭ�� "���� ����Ŭ" �̶�� �Ѵ�.
N���� ������ �̷���� ������ �־����� ��, ���� ����Ŭ�� ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
[�Է�]
ù° �ٿ� �׽�Ʈ ���̽��� ���� T�� �־�����. �� �׽�Ʈ ���̽��� ù° �ٿ��� ������ ũ�� N (2 �� N �� 1,000)�� �־�����. 
��° �ٿ��� ������ �־�����, �� ������ �������� ���еǾ� �ִ�.
[���]
�� �׽�Ʈ ���̽�����, �Է����� �־��� ������ �����ϴ� ���� ����Ŭ�� ������ ����Ѵ�.
*/
#define PROBLEM_10451
#ifdef PROBLEM_10451
#include<stdio.h>

#define STACK_MAX_SIZE 1000
int nGraph[STACK_MAX_SIZE];
int nGraphIndex = -1;
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

		// �̹� �ִ� item�� return 
		for (int i = 0; i <= nTop; i++)
			if (nStack[i] == nX)
				return false;

		nStack[++nTop] = nX;
		return true;
	}

	int pop()
	{
		if (nTop == -1)
			return -1;

		int nResult = nStack[nTop];
		nStack[nTop--] = 0;

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

void depth_first_search(Stack** pStack)
{
	Stack* tmp = *pStack;
	int nCycleCount = 0;	// ���� ����� ����
	int nNextNode;	// ������ �湮�� ����� index
	nNextNode = 0;

	for (int i = 0; i <= nGraphIndex + 1; i++)
	{
		// ��带 �湮�� ������ stack �� push��
		if (tmp->push(nNextNode) == false)
		{
			nCycleCount++;
			int nStackCount = tmp->size();
			if (i == nGraphIndex + 1) break;

			// ��������Ŭ�� �����ϹǷ� �湮�� ��带 ��� ����
			for (int j = 0; j<nStackCount; j++)
				tmp->pop();

			// ������ �湮�� ��带 ã��
			for (int j = 0; j <= nGraphIndex; j++)
				if (nGraph[j] != -1)
				{
					nNextNode = j;
					i--;
					break;
				}
		}
		else
		{
			int nTmp;
			nTmp = nNextNode;
			nNextNode = nGraph[nNextNode];	// ���� ��� ���� ����
			nGraph[nTmp] = -1;				// ��忡 �湮�� ������ ǥ�� (��湮x)
		}
	}

	printf("%d\n", nCycleCount);
}

int main()
{
	int nCount;
	scanf("%d", &nCount);
	Stack* aStack;

	while (nCount-- > 0)
	{
		int nNumberCount;
		scanf("%d", &nNumberCount);

		aStack = new Stack;

		// make array
		while (nNumberCount-- > 0)
		{
			int nNext;
			nGraphIndex++;
			scanf("%d", &nNext);
			nGraph[nGraphIndex] = nNext - 1;
		}

		// start search
		depth_first_search(&aStack);

		delete aStack;
		nGraphIndex = -1;
	}

	return 0;
}

#endif