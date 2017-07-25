/* [�ۼ���] 2017.01.10
[����] �ִܰ�� https://www.acmicpc.net/problem/1753
����׷����� �־����� �־��� ���������� �ٸ� ��� ���������� �ִ� ��θ� ���ϴ� ���α׷��� �ۼ��Ͻÿ�. ��, ��� ������ ����ġ�� 10 ������ �ڿ����̴�.
[�Է�]
ù° �ٿ� ������ ���� V�� ������ ���� E�� �־�����. (1��V��20,000, 1��E��300,000) ��� �������� 1���� V���� ��ȣ�� �Ű��� �ִٰ� �����Ѵ�. 
��° �ٿ��� ���� ������ ��ȣ K(1��K��V)�� �־�����. ��° �ٺ��� E���� �ٿ� ���� �� ������ ��Ÿ���� �� ���� ���� (u, v, w)�� ������� �־�����. 
�̴� u���� v�� ���� ����ġ w�� ������ �����Ѵٴ� ���̴�. u�� v�� ���� �ٸ��� w�� 10 ������ �ڿ����̴�. 
���� �ٸ� �� ���� ���̿� ���� ���� ������ ������ ���� ������ �����Ѵ�.
[���]
ù° �ٺ��� V���� �ٿ� ����, i��° �ٿ� i�� ���������� �ִ� ����� ��ΰ��� ����Ѵ�. 
������ �ڽ��� 0���� ����ϰ�, ��ΰ� �������� �ʴ� ��쿡�� INF�� ����ϸ� �ȴ�.
*/

//#define PROBLEM_1753
#ifdef PROBLEM_1753
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

#define INF 1000000
class Dijkstra
{
private:
	priority_queue<pair<int, int>> queueVertex;
	vector<int> visited;
	vector<int> minDistance;
	vector<pair<int, int>> *graph;
	int nVertexCount;

public:
	Dijkstra()
	{

	}
	~Dijkstra()
	{
		delete[] graph;
	}

	void initDijkstra(int nCount)
	{
		nVertexCount = nCount;
		graph = new vector<pair<int, int>>[nVertexCount]();

		for (int i = 0; i<nVertexCount; i++)
		{
			minDistance.push_back(INF);
		}
	}

	void insertVertex(int nStartVertex, int nEndVertex, int nDistance)
	{
		graph[nStartVertex].push_back(make_pair(nEndVertex, nDistance));
	}

	void runDijkstra(int nStartNode)
	{
		queueVertex.push(make_pair(0, nStartNode));

		do
		{
			int nQueueVertex = queueVertex.top().second;
			int nQueueDistance = -queueVertex.top().first;
			queueVertex.pop();

			// �̹� �湮�� ����� ��� �ٽ� pop
			while (find(visited.begin(), visited.end(), nQueueVertex) != visited.end())
			{
				if (queueVertex.empty()) return;
				nQueueVertex = queueVertex.top().second;
				nQueueDistance = -queueVertex.top().first;
				queueVertex.pop();
			}

			// �湮�� ��� ����
			visited.push_back(nQueueVertex);
			minDistance.at(nQueueVertex) = nQueueDistance;

			for (int i = 0; i<graph[nQueueVertex].size(); i++)
			{
				int nNextVertex = graph[nQueueVertex].at(i).first;
				int nNextDistance = graph[nQueueVertex].at(i).second;

				nNextDistance = minDistance.at(nQueueVertex) + nNextDistance;
				queueVertex.push(make_pair(-nNextDistance, nNextVertex));
			}

		} while (!queueVertex.empty());
	}

	void printDistance()
	{
		for (int i = 0; i<nVertexCount; i++)
		{
			if (minDistance.at(i) == INF)
				printf("INF\n");
			else
				printf("%d\n", minDistance.at(i));
		}
	}

	void modifyMinDistance(int nVertexIndex, int nDistance)
	{
		minDistance.at(nVertexIndex) = nDistance;
	}
};

int main()
{
	int nVertexCount;
	int nEdgeCount;
	scanf("%d%d", &nVertexCount, &nEdgeCount);

	Dijkstra* sort = new Dijkstra;
	sort->initDijkstra(nVertexCount);

	int nStartNode;
	scanf("%d", &nStartNode);
	sort->modifyMinDistance(nStartNode - 1, 0);

	int u, v, w;
	while (nEdgeCount-- > 0)
	{
		scanf("%d%d%d", &u, &v, &w);

		sort->insertVertex(u - 1, v - 1, w);
	}

	sort->runDijkstra(nStartNode - 1);
	sort->printDistance();

	delete sort;

	return 0;
}
#endif