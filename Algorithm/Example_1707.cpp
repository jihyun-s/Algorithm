/* [작성일] 2017.06.19
[문제] 이분 그래프 https://www.acmicpc.net/problem/1707
그래프의 정점의 집합을 둘로 분할하여, 각 집합에 속한 정점끼리는 서로 인접하지 않도록 분할할 수 있을 때, 
그러한 그래프를 특별히 이분 그래프 (Bipartite Graph) 라 부른다.
그래프가 입력으로 주어졌을 때, 이 그래프가 이분 그래프인지 아닌지 판별하는 프로그램을 작성하시오.
[입력]
입력은 여러 개의 테스트 케이스로 구성되어 있는데, 첫째 줄에 테스트 케이스의 개수 K(2≤K≤5)가 주어진다. 
각 테스트 케이스의 첫째 줄에는 그래프의 정점의 개수 V(1≤V≤20,000)와 간선의 개수 E(1≤E≤200,000)가 빈 칸을 사이에 두고 순서대로 주어진다. 
각 정점에는 1부터 N까지 차례로 번호가 붙어 있다. 
이어서 둘째 줄부터 E개의 줄에 걸쳐 간선에 대한 정보가 주어지는데, 각 줄에 인접한 두 정점의 번호가 빈 칸을 사이에 두고 주어진다.
[출력]
K개의 줄에 걸쳐 입력으로 주어진 그래프가 이분 그래프이면 YES, 아니면 NO를 순서대로 출력한다.
*/

#define PROBLEM_1707
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
	for (int i = 0; i < edgeVector[nIndex].size(); i++)	// 인접노드 확인
	{
		int nNextVector = edgeVector[nIndex][i];
		if ((nGroup[nNextVector] == nGroup[nIndex]) && (nNextVector != nIndex))	// 인접노드와의 그룹 체크
			return false;

		if (nGroup[nNextVector] == NONE && !dfs(nNextVector, -nG))	// 인접노드가 아직 방문하지 않은 노드인 경우
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