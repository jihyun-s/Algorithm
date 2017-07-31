/* [�ۼ���] 2017.06.19
[����] �̺� �׷��� https://www.acmicpc.net/problem/1707
�׷����� ������ ������ �ѷ� �����Ͽ�, �� ���տ� ���� ���������� ���� �������� �ʵ��� ������ �� ���� ��, 
�׷��� �׷����� Ư���� �̺� �׷��� (Bipartite Graph) �� �θ���.
�׷����� �Է����� �־����� ��, �� �׷����� �̺� �׷������� �ƴ��� �Ǻ��ϴ� ���α׷��� �ۼ��Ͻÿ�.
[�Է�]
�Է��� ���� ���� �׽�Ʈ ���̽��� �����Ǿ� �ִµ�, ù° �ٿ� �׽�Ʈ ���̽��� ���� K(2��K��5)�� �־�����. 
�� �׽�Ʈ ���̽��� ù° �ٿ��� �׷����� ������ ���� V(1��V��20,000)�� ������ ���� E(1��E��200,000)�� �� ĭ�� ���̿� �ΰ� ������� �־�����. 
�� �������� 1���� N���� ���ʷ� ��ȣ�� �پ� �ִ�. 
�̾ ��° �ٺ��� E���� �ٿ� ���� ������ ���� ������ �־����µ�, �� �ٿ� ������ �� ������ ��ȣ�� �� ĭ�� ���̿� �ΰ� �־�����.
[���]
K���� �ٿ� ���� �Է����� �־��� �׷����� �̺� �׷����̸� YES, �ƴϸ� NO�� ������� ����Ѵ�.
*/

//#define PROBLEM_1707
#ifdef PROBLEM_1707
#include<cstdio>
#include<string.h>
#include<vector>
using namespace std;
enum GROUP { NONE = 0, A = 1, B = -1 };
#define MAX 20010

vector<int> edgeVector[MAX];
vector<int> nGroup(MAX, 0);

bool dfs(int nIndex, int nG)
{
	nGroup[nIndex] = nG;
	for (int i = 0; i < edgeVector[nIndex].size(); i++)	// ������� Ȯ��
	{
		int nNextVector = edgeVector[nIndex][i];
		if ((nGroup[nNextVector] == nGroup[nIndex]) && (nNextVector != nIndex))	// ���������� �׷� üũ
			return false;

		if (nGroup[nNextVector] == NONE && !dfs(nNextVector, -nG))	// ������尡 ���� �湮���� ���� ����� ���
		{
			return false;
		}
	}
	return true;
}

int main()
{
	int nTestCount;
	scanf("%d", &nTestCount);

	int nVertexCount;
	int nEdgeCount;
	int nVertex1;
	int nVertex2;

	while (nTestCount-- > 0)
	{
		scanf("%d%d", &nVertexCount, &nEdgeCount);

		while (nEdgeCount-- > 0)
		{
			scanf("%d%d", &nVertex1, &nVertex2);

			edgeVector[nVertex1 - 1].push_back(nVertex2 - 1);
			edgeVector[nVertex2 - 1].push_back(nVertex1 - 1);
		}

		bool bResult = true;
		for (int i = 0; i < nVertexCount; i++)
		{
			if (nGroup[i] == NONE)
			{
				if (!dfs(i, A))
				{
					bResult = false;
					break;
				}
			}
		}

		printf("%s\n", (bResult == 1) ? "YES" : "NO");
		for (int i = 0; i < nVertexCount; ++i) edgeVector[i].clear();
		for (int i = 0; i < nVertexCount; ++i) nGroup[i] = 0;
	}

	return 0;
}

#endif