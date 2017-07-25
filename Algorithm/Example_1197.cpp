/* [작성일] 2017.01.28
[문제] 최소 스패닝 트리 https://www.acmicpc.net/problem/1197
그래프가 주어졌을 때, 그 그래프의 최소 스패닝 트리를 구하는 프로그램을 작성하시오.
최소 스패닝 트리는, 주어진 그래프의 모든 정점들을 연결하는 부분 그래프 중에서 그 가중치의 합이 최소인 트리를 말한다.
[입력]
첫째 줄에 정점의 개수 V(1≤V≤10,000)와 간선의 개수 E(1≤E≤100,000)가 주어진다. 다음 E개의 줄에는 각 간선에 대한 정보를 나타내는 세 정수 A, B, C가 주어진다. 
이는 A번 정점과 B번 정점이 가중치 C인 간선으로 연결되어 있다는 의미이다. C는 음수일 수도 있으며, 절대값이 1,000,000을 넘지 않는다.
[출력]
첫째 줄에 최소 스패닝 트리의 가중치를 출력한다.
*/

//#define PROBLEM_1197
#ifdef PROBLEM_1197

#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;

priority_queue<pair<int, pair<int, int>>> q;
int nSum = 0;
int parent[10001];
void unionVertex(int a, int b)
{
	if (a == b)
		return;
	parent[a] = b;
}
int find(int a)
{
	if (parent[a] == -1)
		return a;
	return parent[a] = find(parent[a]);
}

void kruskal(int nEdgeMaxCount)
{
	int nDistance;
	int nCount = 0;
	memset(parent, -1, sizeof(parent));
	pair<int, pair<int, int>> tmp;
	// 간선 갯수가 정점-1이 될 때까지
	while (nCount < nEdgeMaxCount)
	{
		tmp = q.top();
		q.pop();

		nDistance = -tmp.first;

		int v1 = find(tmp.second.first);
		int v2 = find(tmp.second.second);

		if (v1 != v2)
		{
			unionVertex(v1, v2);
			nSum += nDistance;
			nCount++;
		}
	}
}

int main()
{
	int nVertex, nEdge;
	scanf("%d", &nVertex);
	scanf("%d", &nEdge);

	int nTotalCount = nVertex - 1;

	int v1, v2, d;
	while (nEdge-- > 0)
	{
		scanf("%d", &v1);
		scanf("%d", &v2);
		scanf("%d", &d);
		q.push(make_pair(-d, make_pair(v1, v2)));
	}
	kruskal(nTotalCount);
	printf("%d", nSum);
	return 0;
}

#endif