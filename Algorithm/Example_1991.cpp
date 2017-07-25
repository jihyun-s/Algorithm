/* [작성일] 2017.01.02
[문제] 트리순회 https://www.acmicpc.net/problem/1991
이진 트리를 입력받아 전위 순회(preorder traversal), 중위 순회(inorder traversal), 후위 순회(postorder traversal)한 결과를 출력하는 프로그램을 작성하시오.
예를 들어 위와 같은 이진 트리가 입력되면,
전위 순회한 결과 : ABDCEFG // (루트) (왼쪽 자식) (오른쪽 자식)
중위 순회한 결과 : DBAECFG // (왼쪽 자식) (루트) (오른쪽 자식)
후위 순회한 결과 : DBEGFCA // (왼쪽 자식) (오른쪽 자식) (루트)
가 된다.
[입력]
첫째 줄에는 이진 트리의 노드의 개수 N(1≤N≤26)이 주어진다. 둘째 줄부터 N개의 줄에 걸쳐 각 노드와 그의 왼쪽 자식 노드, 오른쪽 자식 노드가 주어진다. 
노드의 이름은 A부터 차례대로 영문자 대문자로 매겨지며, 항상 A가 루트 노드가 된다. 자식 노드가 없는 경우에는 .으로 표현된다.
[출력]
첫째 줄에 전위 순회, 둘째 줄에 중위 순회, 셋째 줄에 후위 순회한 결과를 출력한다. 각 줄에 N개의 알파벳을 공백 없이 출력하면 된다.
*/

#define PROBLEM_1991
#ifdef PROBLEM_1991

#include<iostream>
using namespace std;

class NodeEx
{
public:
	NodeEx()
	{
		pLeft = NULL;
		pRight = NULL;
		data = '\0';
	}
	~NodeEx() { }
	NodeEx(NodeEx* pLeft, NodeEx *pRight, char data) { this->pLeft = pLeft; this->pRight = pRight; this->data = data; }
	void SetChildNode(NodeEx* pLeft, NodeEx* pRight) { this->pLeft = pLeft; this->pRight = pRight; }
	void SetLeftNode(NodeEx* pLeft) { this->pLeft = pLeft; }
	void SetRightNode(NodeEx* pRight) { this->pRight = pRight; }
	void SetData(char data) { this->data = data; }
	NodeEx* GetLeftNode() { return pLeft; }
	NodeEx* GetRightNode() { return pRight; }
	char GetData() { return data; }
	void visit() { printf("%c", data); }
public:
	NodeEx* pLeft;	// 왼쪽 자식
	NodeEx* pRight;	// 오른쪽 자식
	char data;		// 값
};

class Tree
{
private:
	NodeEx *pRoot;

	char *pValue;
	void* *pAddr;

	int nIndex;

public:
	Tree() { pRoot = NULL; nIndex = -1; }
	~Tree() {
		delete pValue;
		delete pAddr;
	}
	void SetRootNode(NodeEx *pRoot) { this->pRoot = pRoot; }
	NodeEx* GetRootNode() { return pRoot; }
	void InitData(int nCount) {
		nIndex = nCount;
		pValue = new char[nCount];
		pAddr = new void*[nCount];

		int i = -1;
		int ascii = 0x41;
		NodeEx* pNode = new NodeEx[nCount];

		while (++i <nCount)
		{
			pValue[i] = ascii + i;
			pAddr[i] = (void*)&(pNode[i]);
			pNode[i].SetData(pValue[i]);
			pNode[i].SetChildNode(NULL, NULL);
		}
		pRoot = ((NodeEx*)pAddr[0]);
	}
	void LinkChildNode(char strParent, char strLeft, char strRight)
	{
		int nCount = 0;
		bool bLeft = false, bRight = false;
		if (strLeft != '.') bLeft = true;
		if (strRight != '.') bRight = true;

		NodeEx* pParent = NULL;
		NodeEx* pLeft = NULL;
		NodeEx* pRight = NULL;

		while (nCount <= nIndex)
		{
			if (pValue[nCount] == strParent)
				pParent = (NodeEx*)pAddr[nCount];
			else if (pValue[nCount] == strLeft)
				pLeft = (NodeEx*)pAddr[nCount];
			else if (pValue[nCount] == strRight)
				pRight = (NodeEx*)pAddr[nCount];
			nCount++;
		}

		if (bLeft && pLeft)
			(pParent)->SetLeftNode(pLeft);
		if (bRight && pRight)
			(pParent)->SetRightNode(pRight);

	}
	void DeleteNode()
	{
		for (int i = 0; i<nIndex; i++)
			delete (NodeEx*)pValue[i];
	}
};

class TreeSearch
{
private:
	Tree *pTree;
	//NodeEx *pSearchNode;

public:
	TreeSearch() { this->pTree = NULL; }
	TreeSearch(Tree *pTree) { this->pTree = pTree; }
	~TreeSearch() {}
	Tree* GetTree() { return pTree; }
	void preorder(NodeEx* pNode)
	{
		if (pNode != NULL)
		{
			pNode->visit();

			preorder(pNode->GetLeftNode());

			preorder(pNode->GetRightNode());
		}
	}

	void inorder(NodeEx* pNode)
	{
		if (pNode != NULL)
		{
			inorder(pNode->GetLeftNode());

			pNode->visit();

			inorder(pNode->GetRightNode());
		}
	}

	void postorder(NodeEx* pNode)
	{
		if (pNode != NULL)
		{
			postorder(pNode->GetLeftNode());

			postorder(pNode->GetRightNode());

			pNode->visit();
		}
	}
};


int main()
{
	int nCount;
	scanf("%d", &nCount);
	Tree* pTree = new Tree;
	pTree->InitData(nCount);

	char strParent[3], strLeft[3], strRight[3];
	while (nCount-- > 0)
	{
		scanf("%s", strParent);
		scanf("%s", strLeft);
		scanf("%s", strRight);
		pTree->LinkChildNode(strParent[0], strLeft[0], strRight[0]);
	}

	TreeSearch* pSearch = new TreeSearch(pTree);
	pSearch->preorder(pSearch->GetTree()->GetRootNode());
	printf("\n");
	pSearch->inorder(pSearch->GetTree()->GetRootNode());
	printf("\n");
	pSearch->postorder(pSearch->GetTree()->GetRootNode());
	printf("\n");

	return 0;
}
#endif