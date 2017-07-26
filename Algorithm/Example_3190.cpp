/* [�ۼ���] 2017.06.09
[����] �� https://www.acmicpc.net/problem/3190
'Dummy' ��� ���������� �ִ�. �� ���ӿ��� ���� ���ͼ� ���ٴϴµ�, ����� ������ �� ���̰� �þ��. 
���� �̸����� ���ٴϴٰ� �� �Ǵ� �ڱ��ڽ��� ���� �΋H���� ������ ������.
������ NxN ���簢 ���������� ����ǰ�, ��� ĭ���� ����� ������ �ִ�. ������ �����¿� ���� ���� �ִ�. 
������ �����Ҷ� ���� ���� �������� ��ġ�ϰ� ���� ���̴� 1 �̴�. ���� ó���� �������� ���Ѵ�.
���� �� �ʸ��� �̵��� �ϴµ� ������ ���� ��Ģ�� ������.
���� ���� �����̸� �÷� �Ӹ��� ����ĭ�� ��ġ��Ų��.
���� �̵��� ĭ�� ����� �ִٸ�, �� ĭ�� �ִ� ����� �������� ������ �������� �ʴ´�.
���� �̵��� ĭ�� ����� ���ٸ�, �����̸� �ٿ��� ������ ��ġ�� ĭ�� ����ش�.(��, �����̴� ������ �ʴ´�.)
����� ��ġ�� ���� �̵���ΰ� �־��� �� �� ������ �� ��(seconds)�Ŀ� �������� ����϶�.
[�Է�]
ù°�ٿ� N�� �־�����. ( 2 �� N �� 100 )
�����ٿ� ����� ���� K�� �־�����.( 0 �� K �� 100 )
�׸��� K���� �ٿ��� ����� ��ġ�� �־����µ�, ù��° ���ڴ� ��(row), �ι�° ���ڴ� ��(column) ��ġ�� �ǹ��Ѵ�. 
������� ��ġ�� ��� �ٸ���, �� �� �� ����(1�� 1��)���� ����� ����.
�׸��� ���� ���⺯ȯ ���� L �� �־�����. ( 1 �� L �� 100 )
�׸��� L���� �ٿ��� ���� ���⺯ȯ ������ �־����µ�,  ���� X�� ���� C�� �̷���� �ִ�. 
X�� �Ŀ� ����(C�� 'L') �Ǵ� ������(C�� 'D')�� ������ ���� �Ѵٴ� ���̴�. 
X�� 10,000 ������ ���� �����̸�, ���� ��ȯ ������ X�� �����ϴ� ������ �־�����.
[���]
������ ����,  �� ��(seconds) �� ù°�ٿ� ����϶�.
*/

#define PROBLEM_3190
#ifdef PROBLEM_3190

#include<stdio.h>
#include<vector>
#include<deque>
using namespace std;

int pMap[101][101] = { 0, };
int nMapSize;
vector<pair<int, int>> moveVector;
deque<pair<int, int>> snake;
int currX = 0;
int currY = 0;
enum { RIGHT, BOTTOM, LEFT, TOP } dir;
int currDir = 0;
bool bFail = true;

int moveStraight(int nTime)
{
	int nResult = 0;

	while (nResult < nTime)	// 1�ʾ� �̵�
	{
		nResult++;

		if (currDir == RIGHT) currY++;
		else if (currDir == LEFT) currY--;
		else if (currDir == BOTTOM) currX++;
		else if (currDir == TOP) currX--;

		// map�� ����� ���
		if (currX <= 0 || currY <= 0) { bFail = false; break; }
		if (currX > nMapSize || currY > nMapSize) { bFail = false; break; }

		// ��� ������ ���
		deque<pair<int, int>>::iterator itr;
		for (itr = snake.begin(); itr != snake.end(); itr++)
		{
			if ((*itr).first == currX && (*itr).second == currY)
			{
				bFail = false;
				return nResult;
			}
		}
		snake.push_back(make_pair(currX, currY));

		if (pMap[currX][currY] != 1)
			snake.pop_front();
		else // ����� �Ծ��� �� 
			pMap[currX][currY] = 0;

	}

	return nResult;
}

void moveDirection(int nDir)
{
	if (nDir == RIGHT) // RIght
	{
		currDir++;
		currDir = currDir % 4;
	}
	else
	{
		currDir--;
		if (currDir < 0)
			currDir = 3;
	}
}

void initGame()
{
	currX++; currY++;
	snake.push_back(make_pair(currX, currY));
}

int startGame()
{
	int nTotalTime = 0;

	vector<pair<int, int>>::iterator itr;
	for (itr = moveVector.begin(); itr != moveVector.end(); itr++)
	{
		int nTime = (*itr).first;
		nTotalTime += moveStraight(nTime - nTotalTime);

		if (bFail == false)
			return nTotalTime;

		moveDirection((*itr).second);
	}

	while (bFail != false)
		nTotalTime += moveStraight(1);

	return nTotalTime;
}

int main()
{
	scanf("%d", &nMapSize);

	int nCount, nAppleX, nAppleY;
	scanf("%d", &nCount);
	while (nCount-- > 0)
	{
		scanf("%d%d", &nAppleX, &nAppleY);
		pMap[nAppleX][nAppleY] = 1;
	}

	scanf("%d", &nCount);
	int nTime, nDir;
	char cDir;
	while (nCount-- > 0)
	{
		scanf("%d %c", &nTime, &cDir);

		if (cDir == 'D')
			nDir = RIGHT; //RIGHT;
		else if (cDir == 'L')
			nDir = LEFT; // LEFT;

		moveVector.push_back(make_pair(nTime, nDir));
	}

	initGame();
	int nTotalTime = startGame();
	printf("%d\n", nTotalTime);

	return 0;
}

#endif