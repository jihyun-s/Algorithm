/* [�ۼ���] 2017.02.14
[����] Ÿ�Ӹӽ� https://www.acmicpc.net/problem/11657
N���� ���ð� �ִ�. �׸��� �� ���ÿ��� ����Ͽ� �ٸ� ���ÿ� �����ϴ� ������ M�� �ִ�. 
�� ������ A, B, C�� ��Ÿ�� �� �ִµ�, A�� ���۵���, B�� ��������, C�� ������ Ÿ�� �̵��ϴµ� �ɸ��� �ð��̴�. �ð� C�� ����� �ƴ� ��찡 �ִ�. 
C = 0�� ���� ���� �̵��� �ϴ� ���, C < 0�� ���� Ÿ�Ӹӽ����� �ð��� �ǵ��ư��� ����̴�.
1�� ���ÿ��� ����ؼ� ������ ���÷� ���� ���� ���� �ð��� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
[�Է�]
ù° �ٿ� ������ ���� N (1 �� N �� 500), ���� �뼱�� ���� M (1 �� M �� 6,000)�� �־�����. 
��° �ٺ��� M���� �ٿ��� ���� �뼱�� ���� A, B, C (1 �� A, B �� N, -10,000 �� C �� 10,000)�� �־�����.
[���]
ù° �ٿ��� 2�� ���ñ��� ���� ���� ���� �ð�, ..., N-1��° �ٿ��� N�� ���ñ��� ���� ���� ���� �ð��� ����Ѵ�. 
� ���÷� ���� ���� ���� �ð��� ���� ��쿡�� -1�� ����Ѵ�.
����, ���������� ���� ������ Ÿ�Ӹӽ����� �Ǿ��ִ� ����Ŭ�� ������ 1�� ���ÿ��� ������ ���÷� ���� ���� ���� �ð��� �������� �ʴ� ��쿡�� -1�� ����Ѵ�.
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
	// ù �������� distance ����
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
		minDistance.push_back(INF); // ���� �ִܰŸ� �ʱ�ȭ (���Ѵ�)

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