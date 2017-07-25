/* [작성일] 2017.02.25
[문제] 경로찾기 https://www.acmicpc.net/problem/11403
가중치 없는 방향 그래프 G가 주어졌을 때, 모든 정점 (i, j)에 대해서, i에서 j로 가는 경로가 있는지 없는지 구하는 프로그램을 작성하시오.
[입력]
첫째 줄에 정점의 개수 N (1 ≤ N ≤ 100)이 주어진다. 둘째 줄부터 N개 줄에는 그래프의 인접 행렬이 주어진다. 
i번째 줄의 j번째 숫자가 1인 경우에는 i에서 j로 가는 간선이 존재한다는 뜻이고, 0인 경우는 없다는 뜻이다. i번째 줄의 i번째 숫자는 항상 0이다.
[출력]
총 N개의 줄에 걸쳐서 문제의 정답을 인접행렬 형식으로 출력한다. 정점 i에서 j로 가는 경로가 있으면 i번째 줄의 j번째 숫자를 1로, 없으면 0으로 출력해야 한다.
*/

//#define PROBLEM_11403
#ifdef PROBLEM_11403
#include<cstdio>

#define MAX_VERTEX_COUNT 501
#define NIL				10000
int nearMatrix[MAX_VERTEX_COUNT][MAX_VERTEX_COUNT];
int nVertexCount;

void Floyd()
{
	for (int i = 0; i < nVertexCount; i++)
	{
		for (int j = 0; j < nVertexCount; j++)
		{
			int nTmp = nearMatrix[j][i];
			if (nTmp == NIL)
				continue;

			for (int m = 0; m < nVertexCount; m++)
			{
				if (nearMatrix[i][m] == NIL)
					continue;
				nearMatrix[j][m] = i;
			}
		}
	}
}

void printMatrix()
{
	for (int i = 0; i < nVertexCount; i++)
	{
		for (int j = 0; j < nVertexCount; j++)
		{
			int nValue = nearMatrix[i][j];
			if (nValue != NIL)
				nValue = 1;
			else
				nValue = 0;

			printf("%d ", nValue);
		}
		printf("\n");
	}
}
int main()
{
	scanf("%d", &nVertexCount);

	int tmp;
	for (int i = 0; i < nVertexCount; i++)
	{
		for (int j = 0; j < nVertexCount; j++)
		{
			scanf("%d", &tmp);

			if (tmp == 0)
				nearMatrix[i][j] = NIL;
			else
				nearMatrix[i][j] = i;
		}
	}

	Floyd();
	printMatrix();

	return 0;
}
#endif