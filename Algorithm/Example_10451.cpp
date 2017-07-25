/* [작성일] 2017.01.05
[문제] 순열 사이클 https://www.acmicpc.net/problem/10451
1부터 N까지 정수 N개로 이루어진 순열을 나타내는 방법은 여러가지가 있다. 
예를 들어, 8개의 수로 이루어진 순열 (3, 2, 7, 8, 1, 4, 5, 6)을 배열을 이용해 표현하면 (1234567832781456) 와 같다. 
또는, Figure 1과 같이 방향 그래프로 나타낼 수도 있다.
순열을 배열을 이용해 (1…i…nπ1…πi…πn) 로 나타냈다면, i에서 πi로 간선을 이어 그래프로 만들 수 있다.
Figure 1에 나와있는 것 처럼, 순열 그래프 (3, 2, 7, 8, 1, 4, 5, 6) 에는 총 3개의 사이클이 있다. 이러한 사이클을 "순열 사이클" 이라고 한다.
N개의 정수로 이루어진 순열이 주어졌을 때, 순열 사이클의 개수를 구하는 프로그램을 작성하시오.
[입력]
첫째 줄에 테스트 케이스의 개수 T가 주어진다. 각 테스트 케이스의 첫째 줄에는 순열의 크기 N (2 ≤ N ≤ 1,000)이 주어진다. 
둘째 줄에는 순열이 주어지며, 각 정수는 공백으로 구분되어 있다.
[출력]
각 테스트 케이스마다, 입력으로 주어진 순열에 존재하는 순열 사이클의 개수를 출력한다.
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

		// 이미 있는 item은 return 
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
	int nCycleCount = 0;	// 최종 출력할 변수
	int nNextNode;	// 다음에 방문할 노드의 index
	nNextNode = 0;

	for (int i = 0; i <= nGraphIndex + 1; i++)
	{
		// 노드를 방문할 때마다 stack 에 push함
		if (tmp->push(nNextNode) == false)
		{
			nCycleCount++;
			int nStackCount = tmp->size();
			if (i == nGraphIndex + 1) break;

			// 순열사이클이 존재하므로 방문한 노드를 모두 제거
			for (int j = 0; j<nStackCount; j++)
				tmp->pop();

			// 다음에 방문할 노드를 찾음
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
			nNextNode = nGraph[nNextNode];	// 다음 노드 정보 설정
			nGraph[nTmp] = -1;				// 노드에 방문할 때마다 표시 (재방문x)
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