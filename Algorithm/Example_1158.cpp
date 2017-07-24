/*
[�ۼ���] 2016.12.29
[����] �����۽� ���� https://www.acmicpc.net/problem/1158
1������ N������ N���� ����� ���� �̷�鼭 �ɾ��ְ�, ���� ���� M(�� N)�� �־�����. ���� ������� M��° ����� �����Ѵ�. 
�� ����� ���ŵǸ� ���� ������ �̷���� ���� ���� �� ������ ����� ������. �� ������ N���� ����� ��� ���ŵ� ������ ��ӵȴ�. 
������ ������� ���ŵǴ� ������ (N, M)-�����۽� �����̶�� �Ѵ�. ���� ��� (7, 3)-�����۽� ������ <3, 6, 2, 7, 5, 1, 4>�̴�.
N�� M�� �־����� (N,M)-�����۽� ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
[�Է�]
ù° �ٿ� N�� M�� �� ĭ�� ���̿� �ΰ� ������� �־�����. (1 �� M �� N �� 5,000)
[���]
������ ���� �����۽� ������ ����Ѵ�.
*/

#define PROBLEM_1158
#ifdef PROBLEM_1158

#include<stdio.h>
#include<malloc.h>

// ���� ��ũ�帮��Ʈ ���
typedef struct _Node
{
	int nData;
	struct _Node* pNext;
}Node;
Node *head;

// ���� ��ũ�帮��Ʈ �ʱ�ȭ �Լ�
void init_linkedlist()
{
	head = NULL;
}

// ���� ��ũ�帮��Ʈ�� ��� �߰� 
int makeLinkedList(int nCount)
{
	Node* p;

	if ((p = (Node*)malloc(sizeof(Node))) == NULL)
	{
		// �Ҵ� ������ ���
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
	p->pNext = head;	// �� ó���� ����

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

// ���޹��� parameter�� ���� node�� �����ϴ� �Լ�
int deleteNextNode(Node* pNode)
{
	Node* p;
	int nResult;

	p = pNode->pNext;		// p�� Next Node�� ����
	pNode->pNext = p->pNext;	// ��ũ �ٽ� ����
	nResult = p->nData;			// p�� �����Ͱ��� �����ϱ� ���� ����
	free(p);					// p�� ����

	return nResult;
}

// ��� ��带 �����ϴ� �Լ�
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

// �����۽� �˰��� ���� �Լ�
void josephus(int n, int m)
{
	Node* pNode;
	int nCount = n;

	printf("<");
	pNode = head;

	if (m>1)	// ������ 1���� Ŭ ��
	{
		while (nCount > 1/*pNode->pNext != pNode*/)	// ������ �� node�� ���� ������ delete/print ����
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
	else // ������ 1�� ��쿡�� ��� ��� �� �ϰ� ���� 
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