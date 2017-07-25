/* [�ۼ���] 2017.01.10
[����] ���� ���� https://www.acmicpc.net/problem/1516
�� ȸ�翡�� �̹��� ���ο� ���� �ùķ��̼� ���� ���� ũ����Ʈ�� �����ϱ�� �Ͽ���. 
�ٽ����� �κ��� ������ ���� ���°�, ������ ������ ��ü ���� �ð� ���� �����ϴ� �κи� ���� �־���.
���� �÷��̿� ���� �ð��� ��Ȳ�� ���� �ٸ� �� �ֱ� ������, ��� �ǹ��� ���µ� �ɸ��� �ּ��� �ð��� �̿��Ͽ� �ٻ��ϱ�� �Ͽ���. 
����, � �ǹ��� ���� ���ؼ� �ٸ� �ǹ��� ���� ����� �� ���� �ֱ� ������ ������ �ܼ��������� ���� ���� �ִ�. 
���� ��� ��Ÿũ����Ʈ���� ��Ŀ�� ���� ���ؼ��� �跰�� ���� ����� �ϱ� ������, �跰�� ���� ���� �� ��Ŀ�� ����� �Ѵ�.
���ǻ� �ڿ��� ������ ���� ������ �ְ�, �ǹ��� ���� ����� ����������� �ð��� �ɸ��� �ʴ´ٰ� ��������.
[�Է�]
ù° �ٿ� �ǹ��� ���� �� N(1��N��500)�� �־�����. ���� N���� �ٿ��� �� �ǹ��� ���µ� �ɸ��� �ð��� �� �ǹ��� ���� ���� ���� �������� �ϴ� �ǹ����� ��ȣ�� �־�����. 
�ǹ��� ��ȣ�� 1���� N������ �ϰ�, �� ���� -1�� �����ٰ� ����.
[���]
N���� �� �ǹ��� �ϼ��Ǳ���� �ɸ��� �ּ� �ð��� ����Ѵ�.
*/

// ��������
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

				// ���� �ǹ��� indegree�� ���ҽ�Ų ��, indegree�� 0�� ��� queue�� �ִ´�. 
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