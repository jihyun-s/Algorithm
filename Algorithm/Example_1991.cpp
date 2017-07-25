/* [�ۼ���] 2017.01.02
[����] Ʈ����ȸ https://www.acmicpc.net/problem/1991
���� Ʈ���� �Է¹޾� ���� ��ȸ(preorder traversal), ���� ��ȸ(inorder traversal), ���� ��ȸ(postorder traversal)�� ����� ����ϴ� ���α׷��� �ۼ��Ͻÿ�.
���� ��� ���� ���� ���� Ʈ���� �ԷµǸ�,
���� ��ȸ�� ��� : ABDCEFG // (��Ʈ) (���� �ڽ�) (������ �ڽ�)
���� ��ȸ�� ��� : DBAECFG // (���� �ڽ�) (��Ʈ) (������ �ڽ�)
���� ��ȸ�� ��� : DBEGFCA // (���� �ڽ�) (������ �ڽ�) (��Ʈ)
�� �ȴ�.
[�Է�]
ù° �ٿ��� ���� Ʈ���� ����� ���� N(1��N��26)�� �־�����. ��° �ٺ��� N���� �ٿ� ���� �� ���� ���� ���� �ڽ� ���, ������ �ڽ� ��尡 �־�����. 
����� �̸��� A���� ���ʴ�� ������ �빮�ڷ� �Ű�����, �׻� A�� ��Ʈ ��尡 �ȴ�. �ڽ� ��尡 ���� ��쿡�� .���� ǥ���ȴ�.
[���]
ù° �ٿ� ���� ��ȸ, ��° �ٿ� ���� ��ȸ, ��° �ٿ� ���� ��ȸ�� ����� ����Ѵ�. �� �ٿ� N���� ���ĺ��� ���� ���� ����ϸ� �ȴ�.
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
	NodeEx* pLeft;	// ���� �ڽ�
	NodeEx* pRight;	// ������ �ڽ�
	char data;		// ��
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