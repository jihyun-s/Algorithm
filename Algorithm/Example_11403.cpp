/* [�ۼ���] 2017.02.25
[����] ���ã�� https://www.acmicpc.net/problem/11403
����ġ ���� ���� �׷��� G�� �־����� ��, ��� ���� (i, j)�� ���ؼ�, i���� j�� ���� ��ΰ� �ִ��� ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
[�Է�]
ù° �ٿ� ������ ���� N (1 �� N �� 100)�� �־�����. ��° �ٺ��� N�� �ٿ��� �׷����� ���� ����� �־�����. 
i��° ���� j��° ���ڰ� 1�� ��쿡�� i���� j�� ���� ������ �����Ѵٴ� ���̰�, 0�� ���� ���ٴ� ���̴�. i��° ���� i��° ���ڴ� �׻� 0�̴�.
[���]
�� N���� �ٿ� ���ļ� ������ ������ ������� �������� ����Ѵ�. ���� i���� j�� ���� ��ΰ� ������ i��° ���� j��° ���ڸ� 1��, ������ 0���� ����ؾ� �Ѵ�.
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