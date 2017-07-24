/*
[작성일] 2016.12.29
[문제] 조세퍼스 문제 https://www.acmicpc.net/problem/1158
1번부터 N번까지 N명의 사람이 원을 이루면서 앉아있고, 양의 정수 M(≤ N)이 주어진다. 이제 순서대로 M번째 사람을 제거한다. 
한 사람이 제거되면 남은 사람들로 이루어진 원을 따라 이 과정을 계속해 나간다. 이 과정은 N명의 사람이 모두 제거될 때까지 계속된다. 
원에서 사람들이 제거되는 순서를 (N, M)-조세퍼스 순열이라고 한다. 예를 들어 (7, 3)-조세퍼스 순열은 <3, 6, 2, 7, 5, 1, 4>이다.
N과 M이 주어지면 (N,M)-조세퍼스 순열을 구하는 프로그램을 작성하시오.
[입력]
첫째 줄에 N과 M이 빈 칸을 사이에 두고 순서대로 주어진다. (1 ≤ M ≤ N ≤ 5,000)
[출력]
예제와 같이 조세퍼스 순열을 출력한다.
*/

#define PROBLEM_1158
#ifdef PROBLEM_1158

#include<stdio.h>
#include<malloc.h>

// 원형 링크드리스트 사용
typedef struct _Node
{
	int nData;
	struct _Node* pNext;
}Node;
Node *head;

// 원형 링크드리스트 초기화 함수
void init_linkedlist()
{
	head = NULL;
}

// 원형 링크드리스트에 노드 추가 
int makeLinkedList(int nCount)
{
	Node* p;

	if ((p = (Node*)malloc(sizeof(Node))) == NULL)
	{
		// 할당 실패한 경우
		printf("fail to alloc memory!\n");
		return 0;
	}

	p->nData = 1;
	p->pNext = p;
	head = p;

	for (int i = 2; i <= nCount; i++)
	{
		p->pNext = (Node*)malloc(sizeof(Node));
		p = p->pNext;
		p->nData = i;
	}
	p->pNext = head;	// 맨 처음에 연결

	return 1;
}

void printNode()
{
	Node *p;

	p = head;
	while (p->pNext != head)
	{
		printf("%5d", p->nData);
		p = p->pNext;
	}
	printf("%5d", p->nData);
}

// 전달받은 parameter의 다음 node를 삭제하는 함수
int deleteNextNode(Node* pNode)
{
	Node* p;
	int nResult;

	p = pNode->pNext;		// p에 Next Node를 저장
	pNode->pNext = p->pNext;	// 링크 다시 연결
	nResult = p->nData;			// p의 데이터값을 리턴하기 위해 저장
	free(p);					// p를 지움

	return nResult;
}

// 모든 노드를 삭제하는 함수
void deleteAllNode(int nCount)
{
	Node* p;
	Node* tmp;
	p = head;
	for (int i = 0; i<nCount; i++)
	{
		tmp = p->pNext;
		p->pNext = tmp->pNext;
		free(tmp);
	}
	head = NULL;
}

// 조세퍼스 알고리즘 실행 함수
void josephus(int n, int m)
{
	Node* pNode;
	int nCount = n;

	printf("<");
	pNode = head;

	if (m>1)	// 간격이 1보다 클 때
	{
		while (nCount > 1/*pNode->pNext != pNode*/)	// 마지막 한 node가 남을 때까지 delete/print 수행
		{
			if (nCount != n)
				printf(", ");

			for (int i = 1; i<m - 1; i++)
				pNode = pNode->pNext;

			printf("%d", deleteNextNode(pNode));

			pNode = pNode->pNext;

			nCount--;
		}

		if (n != 1)
			printf(", ");
		printf("%d>", pNode->nData);
		free(pNode);
		head = NULL;
	}
	else // 간격이 1인 경우에는 모두 출력 후 일괄 삭제 
	{
		printf("1");
		for (int i = 2; i <= nCount; i++)
			printf(", %d", i);
		printf(">");
		deleteAllNode(nCount);
	}

	return;
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);

	makeLinkedList(n);

	//printNode();

	josephus(n, m);

	return 0;
}

#endif