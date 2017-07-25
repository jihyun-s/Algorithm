/* [작성일] 2017.01.17
[문제] 최대 힙 https://www.acmicpc.net/problem/11279
널리 잘 알려진 자료구조 중 최대 힙이라는 것이 있다. 최대 힙을 이용하여 다음과 같은 연산을 지원하는 프로그램을 작성하시오.
배열에 자연수 x를 넣는다.
배열에서 가장 큰 값을 출력하고, 그 값을 배열에서 제거한다.
프로그램은 처음에 비어있는 배열에서 시작하게 된다.
[입력]
첫째 줄에 연산의 개수 N(1≤N≤100,000)이 주어진다. 다음 N개의 줄에는 연산에 대한 정보를 나타내는 정수 x가 주어진다. 
만약 x가 자연수라면 배열에 x라는 값을 넣는(추가하는) 연산이고, x가 0이라면 배열에서 가장 큰 값을 출력하고 그 값을 배열에서 제거하는 경우이다. 
입력되는 자연수는 2^31보다 작다.
[출력]
입력에서 0이 주어진 회수만큼 답을 출력한다. 만약 배열이 비어 있는 경우인데 가장 큰 값을 출력하라고 한 경우에는 0을 출력하면 된다.
*/

//#define PROBLEM_11279
#ifdef PROBLEM_11279
#include<cstdio>

int *data;
int nDataCount;
void upheap(int nIndex)
{
	int tmp, parent;

	while (nIndex > 1) {
		tmp = data[nIndex];
		parent = nIndex / 2;
		if (data[nIndex] > data[parent])
		{
			data[nIndex] = data[parent];
			data[parent] = tmp;
			nIndex = parent;
		}
		else
			break;
	}
}

void downheap(int nEndIndex)
{
	int nIndex = 1;
	int tmp, child;

	while (nIndex <= nEndIndex / 2) {
		tmp = data[nIndex];
		child = nIndex * 2;

		if (data[child]<data[child + 1] && (child + 1) <= nEndIndex)
			child++;

		if (tmp < data[child])
		{
			data[nIndex] = data[child];
			data[child] = tmp;
			nIndex = child;
		}
		else
			break;
	}
}

void deleteroot()
{
	int nIndex = 1;

	if (nDataCount == 0)
	{
		printf("0\n");
		return;
	}
	else
	{
		printf("%d\n", data[nIndex]);
		data[nIndex] = data[nDataCount];
		data[nDataCount] = -1;
		nDataCount--;

		downheap(nDataCount);
	}
}

int main()
{
	int nCount;
	int nCommand;

	scanf("%d", &nCount);
	data = new int[100001];

	nDataCount = 0;
	while (nCount-- > 0)
	{
		scanf("%d", &nCommand);
		if (nCommand == 0)
		{
			deleteroot();
		}
		else
		{
			nDataCount++;
			data[nDataCount] = nCommand;
			upheap(nDataCount);
		}
	}

	return 0;
}
#endif // PROBLEM_11279