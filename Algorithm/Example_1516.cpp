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

// �� �ǹ����� ����ü
typedef struct _Vertex
{
	int nVertexNumber;				// �ǹ� ��ȣ
	vector<int> nextVertexNumber;	// ������ ���� �� �ִ� �ǹ� ��ȣ
	int nTime;						// �ǹ� �ϼ� �ð�
	int nIndegree;					// ���� �������� �� �ǹ� ����
}Vertex;

class Topological					// �������� class
{
private:
	vector<Vertex*> arrayVertex;	// �Է¹��� �ǹ��鿡 ���� ������ ����
	queue<Vertex*> queueVertex;		// ���� ���� �� �ִ� �ǹ� ������ ���� (���� �ǹ��� �ϳ��� ���� ���)
	int nVertexCount;				// �ǹ��� �� ����
	int* arrayTime;					// �� �ǹ��� �ҿ�Ǵ� �ּ� �ð� (Output) - ���� 0 

public:
	Topological() {}
	~Topological()
	{
		delete arrayTime;
	}

	// ����ü���� ����ϴ� ������ �ʱ�ȭ
	void initVertex(int nCount)
	{
		nVertexCount = nCount;				// �ǹ��� �� ���� ����
		arrayTime = new int[nCount];		// �ǹ��� �� ������ŭ �迭 �ʱ�ȭ
		for (int i = 0; i<nCount; i++)			// �ǹ� �� ������ŭ �ǹ��� �̸� ����� ���� (�� ������) 
		{
			Vertex* tmp = new Vertex;
			tmp->nVertexNumber = i;
			tmp->nIndegree = 0;
			tmp->nTime = 0;
			arrayVertex.push_back(tmp);
			arrayTime[i] = 0;
		}

	}

	// ������ ���� �� �ִ� �ǹ� ��ȣ�� ������ �� ����ϴ� �Լ�
	void addNextVertextNumber(int nCurrNumber, int nNextNumber)
	{
		arrayVertex.at(nCurrNumber)->nextVertexNumber.push_back(nNextNumber);
		arrayVertex.at(nNextNumber)->nIndegree++;
	}

	// �� �ǹ����� ���� �� �ɸ��� �ð��� �����ϴ� �Լ�
	void setVertexValue(int nCurrNumber, int nValue)
	{
		arrayVertex.at(nCurrNumber)->nTime = nValue;
	}

	// ���� �����ϴ� �Լ�
	void sort()
	{
		do
		{
			// ���� ���� �� �ִ� �ǹ��� ������ �޾� �´�. 
			Vertex *tmp = queueVertex.front();
			queueVertex.pop();

			if (arrayTime[tmp->nVertexNumber] == 0)				// �ǹ� �ϼ� �ּ� �ð� ���� ���� ���
				arrayTime[tmp->nVertexNumber] = tmp->nTime;		// ���� �ǹ��� �ϼ� �ð����� ����

			for (int i = 0; i<tmp->nextVertexNumber.size(); i++)	// ������ ����� �� �ǹ��� �̵�
			{
				int nNextNumber = tmp->nextVertexNumber.at(i);
				// ������ ����� �� �ǹ�(A)�� �ּ� �ð��� �����ϴ� �κ�
				// "Output�迭[A�ǹ�] < Output�迭[����ǹ�]+ A�ǹ� ���� �ϼ� �ð�" ���� ū ���� Output�迭�� �����Ѵ�.
				// "arrayTime[nNextNumber] < arrayTime[tmp->nVertexNumber] + arrayVertex.at(nNextNumber)->nTime"
				arrayTime[nNextNumber] = (arrayTime[nNextNumber]<arrayTime[tmp->nVertexNumber] + arrayVertex.at(nNextNumber)->nTime) ? arrayTime[tmp->nVertexNumber] + arrayVertex.at(nNextNumber)->nTime : arrayTime[nNextNumber];

				// ���� �ǹ��� indegree�� ���ҽ�Ų ��, indegree�� 0�� ��� queue�� �ִ´�. 
				if (--arrayVertex.at(nNextNumber)->nIndegree == 0)
					queueVertex.push(arrayVertex.at(nNextNumber));
			}
		} while (!queueVertex.empty());
	}

	// ���� �� ���� �����ϴ� �Լ� : �̸� ����� �� �ǹ��� ���� �ǹ����� queue�� �ִ´�. (ó�� ������ �ǹ��� �����ϴ� ����)
	void insertQueue()
	{
		for (int i = 0; i<nVertexCount; i++)
			if (arrayVertex.at(i)->nIndegree == 0)
				queueVertex.push(arrayVertex.at(i));
	}

	// �� �ǹ� �ϼ� �ּ� �ð��� ����ϴ� �Լ�
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
	p->initVertex(nCount);				// �ǹ��� �ʱ�ȭ 

	nTotalIndex = 0;
	nNextBuildIndex = 0;
	int nMinTime;
	int nPrevBuild;

	// ����ִ� �ǹ��� ������ ä���� 
	while (nTotalIndex<nCount)			// �ǹ� ������ŭ loop
	{
		scanf("%d", &nMinTime);			// �� �ǹ�(A) �ϼ� �ð� �Է¹���
		do
		{
			scanf("%d", &nPrevBuild);	// �̸� ����� �ϴ� �ǹ�(B) �Է� ����

			if (nPrevBuild != -1)
			{
				nPrevBuild = nPrevBuild - 1;							// �迭�� 0���� �����ϹǷ� ���ǻ� ��� �ǹ� ��ȣ�� -1�� ����
				p->addNextVertextNumber(nPrevBuild, nTotalIndex);	//  �̸� ������ϴ� �ǹ�(B) -> ���� �ǹ�(A) ������ �������� 
			}
			else
				break;
		} while (true);

		// insert
		p->setVertexValue(nTotalIndex, nMinTime);			// �Է� ���� �ǹ� �ϼ� �ð��� ����

		nTotalIndex++;
	}

	p->insertQueue();			// ���� indegree(����Ǿ�� �� �ǹ�)�� 0�� �ǹ����� queue�� ����
	p->sort();					// ���� ���� ����
	p->printTime();				// ����� ���

	delete p;
	return 0;
}

#endif//PROBLEM_1516