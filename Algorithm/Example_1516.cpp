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

// 각 건물들의 구조체
typedef struct _Vertex
{
	int nVertexNumber;				// 건물 번호
	vector<int> nextVertexNumber;	// 다음에 지을 수 있는 건물 번호
	int nTime;						// 건물 완성 시간
	int nIndegree;					// 먼저 지어져야 할 건물 갯수
}Vertex;

class Topological					// 위상정렬 class
{
private:
	vector<Vertex*> arrayVertex;	// 입력받은 건물들에 대한 정보를 저장
	queue<Vertex*> queueVertex;		// 현재 지을 수 있는 건물 정보를 저장 (선행 건물이 하나도 없는 경우)
	int nVertexCount;				// 건물의 총 갯수
	int* arrayTime;					// 각 건물당 소요되는 최소 시간 (Output) - 최초 0 

public:
	Topological() {}
	~Topological()
	{
		delete arrayTime;
	}

	// 구조체에서 사용하는 변수들 초기화
	void initVertex(int nCount)
	{
		nVertexCount = nCount;				// 건물의 총 갯수 설정
		arrayTime = new int[nCount];		// 건물의 총 갯수만큼 배열 초기화
		for (int i = 0; i<nCount; i++)			// 건물 총 갯수만큼 건물을 미리 만들어 놓음 (빈 껍데기) 
		{
			Vertex* tmp = new Vertex;
			tmp->nVertexNumber = i;
			tmp->nIndegree = 0;
			tmp->nTime = 0;
			arrayVertex.push_back(tmp);
			arrayTime[i] = 0;
		}

	}

	// 다음에 지을 수 있는 건물 번호를 설정할 때 사용하는 함수
	void addNextVertextNumber(int nCurrNumber, int nNextNumber)
	{
		arrayVertex.at(nCurrNumber)->nextVertexNumber.push_back(nNextNumber);
		arrayVertex.at(nNextNumber)->nIndegree++;
	}

	// 각 건물들을 짓는 데 걸리는 시간을 설정하는 함수
	void setVertexValue(int nCurrNumber, int nValue)
	{
		arrayVertex.at(nCurrNumber)->nTime = nValue;
	}

	// 위상 정렬하는 함수
	void sort()
	{
		do
		{
			// 현재 지을 수 있는 건물의 정보를 받아 온다. 
			Vertex *tmp = queueVertex.front();
			queueVertex.pop();

			if (arrayTime[tmp->nVertexNumber] == 0)				// 건물 완성 최소 시간 설정 전인 경우
				arrayTime[tmp->nVertexNumber] = tmp->nTime;		// 현재 건물의 완성 시간으로 설정

			for (int i = 0; i<tmp->nextVertexNumber.size(); i++)	// 다음에 지어야 할 건물로 이동
			{
				int nNextNumber = tmp->nextVertexNumber.at(i);
				// 다음에 지어야 할 건물(A)의 최소 시간을 변경하는 부분
				// "Output배열[A건물] < Output배열[현재건물]+ A건물 단일 완성 시간" 에서 큰 값을 Output배열에 저장한다.
				// "arrayTime[nNextNumber] < arrayTime[tmp->nVertexNumber] + arrayVertex.at(nNextNumber)->nTime"
				arrayTime[nNextNumber] = (arrayTime[nNextNumber]<arrayTime[tmp->nVertexNumber] + arrayVertex.at(nNextNumber)->nTime) ? arrayTime[tmp->nVertexNumber] + arrayVertex.at(nNextNumber)->nTime : arrayTime[nNextNumber];

				// 다음 건물의 indegree를 감소시킨 후, indegree가 0인 경우 queue에 넣는다. 
				if (--arrayVertex.at(nNextNumber)->nIndegree == 0)
					queueVertex.push(arrayVertex.at(nNextNumber));
			}
		} while (!queueVertex.empty());
	}

	// 최초 한 번만 동작하는 함수 : 미리 지어야 할 건물이 없는 건물들을 queue에 넣는다. (처음 시작할 건물을 설정하는 과정)
	void insertQueue()
	{
		for (int i = 0; i<nVertexCount; i++)
			if (arrayVertex.at(i)->nIndegree == 0)
				queueVertex.push(arrayVertex.at(i));
	}

	// 각 건물 완성 최소 시간을 출력하는 함수
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
	p->initVertex(nCount);				// 건물들 초기화 

	nTotalIndex = 0;
	nNextBuildIndex = 0;
	int nMinTime;
	int nPrevBuild;

	// 비어있는 건물들 정보를 채워줌 
	while (nTotalIndex<nCount)			// 건물 갯수만큼 loop
	{
		scanf("%d", &nMinTime);			// 각 건물(A) 완성 시간 입력받음
		do
		{
			scanf("%d", &nPrevBuild);	// 미리 지어야 하는 건물(B) 입력 받음

			if (nPrevBuild != -1)
			{
				nPrevBuild = nPrevBuild - 1;							// 배열은 0부터 시작하므로 편의상 모든 건물 번호에 -1을 해줌
				p->addNextVertextNumber(nPrevBuild, nTotalIndex);	//  미리 지어야하는 건물(B) -> 현재 건물(A) 순으로 연결해줌 
			}
			else
				break;
		} while (true);

		// insert
		p->setVertexValue(nTotalIndex, nMinTime);			// 입력 받은 건물 완성 시간을 저장

		nTotalIndex++;
	}

	p->insertQueue();			// 현재 indegree(선행되어야 할 건물)이 0인 건물들을 queue에 넣음
	p->sort();					// 위상 정렬 진행
	p->printTime();				// 결과를 출력

	delete p;
	return 0;
}

#endif//PROBLEM_1516