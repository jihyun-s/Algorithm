/* [작성일] 2017.01.17
[문제] 수 정렬하기 2  https://www.acmicpc.net/problem/2751
N개의 수가 주어졌을 때, 이를 오름차순으로 정렬하는 프로그램을 작성하시오.
[입력]
첫째 줄에 수의 개수 N(1<=N<=1,000,000)이 주어진다. 둘째 줄부터 N개의 줄에는 숫자가 주어진다. 이 수는 절대값이 1,000,000보다 작거나 같은 정수이다. 
수는 중복되지 않는다.
[출력]
첫째 줄부터 N개의 줄에 오름차순으로 정렬한 결과를 한 줄에 하나씩 출력한다.
*/

// 힙정렬
//#define PROBLEM_2751
#ifdef PROBLEM_2751

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
	int nEndIndex = nDataCount;
	//int nExternalNodeCount = nDataCount/2;
	int tmp;

	while (nEndIndex > nIndex) {
		// root를 마지막 노드와 교환
		tmp = data[nIndex];
		data[nIndex] = data[nEndIndex];
		data[nEndIndex] = tmp;
		nEndIndex--;

		downheap(nEndIndex);
	}
}

void printheap()
{
	for (int i = 1; i<(nDataCount + 1); i++)
		printf("%d\n", data[i]);
}

int main()
{
	int nIndex;
	scanf("%d", &nDataCount);
	data = new int[nDataCount + 1];

	nIndex = 1;
	while (nIndex < nDataCount + 1)
	{
		scanf("%d", &data[nIndex]);
		upheap(nIndex);
		nIndex++;
	}
	deleteroot();
	printheap();
	return 0;
}
#endif // PROBLEM_2751