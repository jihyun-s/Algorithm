/* [�ۼ���] 2017.01.28
[����] �ּ� ���д� Ʈ�� https://www.acmicpc.net/problem/1197
�׷����� �־����� ��, �� �׷����� �ּ� ���д� Ʈ���� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
�ּ� ���д� Ʈ����, �־��� �׷����� ��� �������� �����ϴ� �κ� �׷��� �߿��� �� ����ġ�� ���� �ּ��� Ʈ���� ���Ѵ�.
[�Է�]
ù° �ٿ� ������ ���� V(1��V��10,000)�� ������ ���� E(1��E��100,000)�� �־�����. ���� E���� �ٿ��� �� ������ ���� ������ ��Ÿ���� �� ���� A, B, C�� �־�����. 
�̴� A�� ������ B�� ������ ����ġ C�� �������� ����Ǿ� �ִٴ� �ǹ��̴�. C�� ������ ���� ������, ���밪�� 1,000,000�� ���� �ʴ´�.
[���]
ù° �ٿ� �ּ� ���д� Ʈ���� ����ġ�� ����Ѵ�.
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
	// ���� ������ ����-1�� �� ������
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