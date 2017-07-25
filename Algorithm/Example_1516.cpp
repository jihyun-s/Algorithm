/* [작성일] 2017.01.10
[문제] 게임 개발 https://www.acmicpc.net/problem/1516
숌 회사에서 이번에 새로운 전략 시뮬레이션 게임 세준 크래프트를 개발하기로 하였다. 
핵심적인 부분은 개발이 끝난 상태고, 종족별 균형과 전체 게임 시간 등을 조절하는 부분만 남아 있었다.
게임 플레이에 들어가는 시간은 상황에 따라 다를 수 있기 때문에, 모든 건물을 짓는데 걸리는 최소의 시간을 이용하여 근사하기로 하였다. 
물론, 어떤 건물을 짓기 위해서 다른 건물을 먼저 지어야 할 수도 있기 때문에 문제가 단순하지만은 않을 수도 있다. 
예를 들면 스타크래프트에서 벙커를 짓기 위해서는 배럭을 먼저 지어야 하기 때문에, 배럭을 먼저 지은 뒤 벙커를 지어야 한다.
편의상 자원은 무한히 많이 가지고 있고, 건물을 짓는 명령을 내리기까지는 시간이 걸리지 않는다고 가정하자.
[입력]
첫째 줄에 건물의 종류 수 N(1≤N≤500)이 주어진다. 다음 N개의 줄에는 각 건물을 짓는데 걸리는 시간과 그 건물을 짓기 위해 먼저 지어져야 하는 건물들의 번호가 주어진다. 
건물의 번호는 1부터 N까지로 하고, 각 줄은 -1로 끝난다고 하자.
[출력]
N개의 각 건물이 완성되기까지 걸리는 최소 시간을 출력한다.
*/

// 위상정렬
//#define PROBLEM_1516
#ifdef PROBLEM_1516
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

typedef struct _Vertex
{
	int nVertexNumber;
	vector<int> nextVertexNumber;
	int nTime;
	int nIndegree;
}Vertex;

class Topological
{
private:
	vector<Vertex*> arrayVertex;
	queue<Vertex*> queueVertex;
	int nVertexCount;
	int* arrayTime;

public:
	Topological() {}
	~Topological()
	{
		delete arrayTime;
	}

	void initVertex(int nCount)
	{
		nVertexCount = nCount;
		arrayTime = new int[nCount];
		for (int i = 0; i<nCount; i++)
		{
			Vertex* tmp = new Vertex;
			tmp->nVertexNumber = i;
			tmp->nIndegree = 0;
			tmp->nTime = 0;
			arrayVertex.push_back(tmp);
			arrayTime[i] = 0;
		}

	}

	void addNextVertextNumber(int nCurrNumber, int nNextNumber)
	{
		arrayVertex.at(nCurrNumber)->nextVertexNumber.push_back(nNextNumber);
		arrayVertex.at(nNextNumber)->nIndegree++;
	}

	void setVertexValue(int nCurrNumber, int nValue)
	{
		arrayVertex.at(nCurrNumber)->nTime = nValue;
	}

	void sort()
	{
		do
		{
			Vertex *tmp = queueVertex.front();
			queueVertex.pop();

			if (arrayTime[tmp->nVertexNumber] == 0)
				arrayTime[tmp->nVertexNumber] = tmp->nTime;

			for (int i = 0; i<tmp->nextVertexNumber.size(); i++)
			{
				int nNextNumber = tmp->nextVertexNumber.at(i);
				arrayTime[nNextNumber] = (arrayTime[nNextNumber]<arrayTime[tmp->nVertexNumber] + arrayVertex.at(nNextNumber)->nTime) ? arrayTime[tmp->nVertexNumber] + arrayVertex.at(nNextNumber)->nTime : arrayTime[nNextNumber];

				// 다음 건물의 indegree를 감소시킨 후, indegree가 0인 경우 queue에 넣는다. 
				if (--arrayVertex.at(nNextNumber)->nIndegree == 0)
					queueVertex.push(arrayVertex.at(nNextNumber));
			}
		} while (!queueVertex.empty());
	}

	void insertQueue()
	{
		for (int i = 0; i<nVertexCount; i++)
			if (arrayVertex.at(i)->nIndegree == 0)
				queueVertex.push(arrayVertex.at(i));
	}

	void printTime()
	{
		for (int i = 0; i<nVertexCount; i++)
			printf("%d\n", arrayTime[i]);
	}
};

int main()
{
	Topological* p = new Topological();
	int nCount, nTotalIndex, nNextBuildIndex;
	scanf("%d", &nCount);
	p->initVertex(nCount);

	nTotalIndex = 0;
	nNextBuildIndex = 0;
	int nMinTime;
	int nPrevBuild;
	while (nTotalIndex<nCount)
	{
		scanf("%d", &nMinTime);
		do
		{
			scanf("%d", &nPrevBuild);

			if (nPrevBuild != -1)
			{
				nPrevBuild = nPrevBuild - 1;
				p->addNextVertextNumber(nPrevBuild, nTotalIndex);
			}
			else
				break;
		} while (true);

		// insert
		p->setVertexValue(nTotalIndex, nMinTime);

		nTotalIndex++;
	}

	p->insertQueue();
	p->sort();
	p->printTime();

	delete p;
	return 0;
}

#endif//PROBLEM_1516