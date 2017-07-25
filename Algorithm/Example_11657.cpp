/* [작성일] 2017.02.14
[문제] 타임머신 https://www.acmicpc.net/problem/11657
N개의 도시가 있다. 그리고 한 도시에서 출발하여 다른 도시에 도착하는 버스가 M개 있다. 
각 버스는 A, B, C로 나타낼 수 있는데, A는 시작도시, B는 도착도시, C는 버스를 타고 이동하는데 걸리는 시간이다. 시간 C가 양수가 아닌 경우가 있다. 
C = 0인 경우는 순간 이동을 하는 경우, C < 0인 경우는 타임머신으로 시간을 되돌아가는 경우이다.
1번 도시에서 출발해서 나머지 도시로 가는 가장 빠른 시간을 구하는 프로그램을 작성하시오.
[입력]
첫째 줄에 도시의 개수 N (1 ≤ N ≤ 500), 버스 노선의 개수 M (1 ≤ M ≤ 6,000)이 주어진다. 
둘째 줄부터 M개의 줄에는 버스 노선의 정보 A, B, C (1 ≤ A, B ≤ N, -10,000 ≤ C ≤ 10,000)가 주어진다.
[출력]
첫째 줄에는 2번 도시까지 가는 가장 빠른 시간, ..., N-1번째 줄에는 N번 도시까지 가는 가장 빠른 시간을 출력한다. 
어떤 도시로 가는 가장 빠른 시간이 없는 경우에는 -1을 출력한다.
만약, 시작점에서 도달 가능한 타임머신으로 되어있는 사이클이 존재해 1번 도시에서 나머지 도시로 가는 가장 빠른 시간이 존재하지 않는 경우에는 -1을 출력한다.
*/

#define PROBLEM_11657
#ifdef PROBLEM_11657

#include<iostream>
#include<vector>
using namespace std;

vector<int> minDistance;
vector<vector<pair<int, int>>> busInfo;
int nVertexCount, nEdgeCount;
bool bCycle = false;

#define INF		100000

void BellmanFord()
{
	// 첫 시작점의 distance 설정
	minDistance.at(0) = 0;

	int nTotalCount = nVertexCount;
	while (nTotalCount-- > 0)
	{
		bool bChange = false;
		for (int i = 0; i < nVertexCount; i++)
		{
			vector<pair<int, int>> tmp = busInfo.at(i);
			for (int j = 0; j < tmp.size(); j++)
			{
				int nEndV = tmp.at(j).first;
				int nTime = tmp.at(j).second;

				if (minDistance.at(i) == INF)
					continue;

				else
				{
					int sum = minDistance.at(i) + nTime;
					if (sum < minDistance.at(nEndV))
					{
						minDistance.at(nEndV) = sum;
						bChange = true;
					}
				}
			}
		}

		if (nTotalCount == 0 && bChange)
			bCycle = true;
	}
}

void printMinDistance()
{
	if (bCycle)
	{
		printf("-1\n");
		return;
	}

	for (int i = 1; i < nVertexCount; i++)
	{
		int nDistance = minDistance.at(i);
		if (nDistance == INF)
			nDistance = -1;
		printf("%d\n", nDistance);
	}

}

int main()
{
	int nBusCount;
	scanf("%d", &nVertexCount);
	scanf("%d", &nBusCount);

	nEdgeCount = nBusCount;

	for (int i = 0; i < nVertexCount; i++)
	{
		minDistance.push_back(INF); // 정점 최단거리 초기화 (무한대)

		vector<pair<int, int>> tmp;
		busInfo.push_back(tmp);
	}

	while (nBusCount-- > 0)
	{
		int nStartV, nEndV, nTime;
		scanf("%d", &nStartV);
		scanf("%d", &nEndV);
		scanf("%d", &nTime);

		busInfo.at(nStartV - 1).push_back(make_pair(nEndV - 1, nTime));
	}

	BellmanFord();
	printMinDistance();

	return 0;
}

#endif