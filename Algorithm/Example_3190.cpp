/* [작성일] 2017.06.09
[문제] 뱀 https://www.acmicpc.net/problem/3190
'Dummy' 라는 도스게임이 있다. 이 게임에는 뱀이 나와서 기어다니는데, 사과를 먹으면 뱀 길이가 늘어난다. 
뱀이 이리저리 기어다니다가 벽 또는 자기자신의 몸과 부딫히면 게임이 끝난다.
게임은 NxN 정사각 보드위에서 진행되고, 몇몇 칸에는 사과가 놓여져 있다. 보드의 상하좌우 끝에 벽이 있다. 
게임이 시작할때 뱀은 맨위 맨좌측에 위치하고 뱀의 길이는 1 이다. 뱀은 처음에 오른쪽을 향한다.
뱀은 매 초마다 이동을 하는데 다음과 같은 규칙을 따른다.
먼저 뱀은 몸길이를 늘려 머리를 다음칸에 위치시킨다.
만약 이동한 칸에 사과가 있다면, 그 칸에 있던 사과가 없어지고 꼬리는 움직이지 않는다.
만약 이동한 칸에 사과가 없다면, 몸길이를 줄여서 꼬리가 위치한 칸을 비워준다.(즉, 몸길이는 변하지 않는다.)
사과의 위치와 뱀의 이동경로가 주어질 때 이 게임이 몇 초(seconds)후에 끝나는지 계산하라.
[입력]
첫째줄에 N이 주어진다. ( 2 ≤ N ≤ 100 )
다음줄에 사과의 개수 K가 주어진다.( 0 ≤ K ≤ 100 )
그리고 K개의 줄에는 사과의 위치가 주어지는데, 첫번째 숫자는 행(row), 두번째 숫자는 열(column) 위치를 의미한다. 
사과들의 위치는 모두 다르며, 맨 위 맨 좌측(1행 1열)에는 사과가 없다.
그리고 뱀의 방향변환 개수 L 이 주어진다. ( 1 ≤ L ≤ 100 )
그리고 L개의 줄에는 뱀의 방향변환 정보가 주어지는데,  숫자 X와 문자 C로 이루어져 있다. 
X초 후에 왼쪽(C가 'L') 또는 오른쪽(C가 'D')로 방향을 변경 한다는 뜻이다. 
X는 10,000 이하의 양의 정수이며, 방향 전환 정보는 X가 증가하는 순으로 주어진다.
[출력]
문제의 정답,  즉 초(seconds) 를 첫째줄에 출력하라.
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

	while (nResult < nTime)	// 1초씩 이동
	{
		nResult++;

		if (currDir == RIGHT) currY++;
		else if (currDir == LEFT) currY--;
		else if (currDir == BOTTOM) currX++;
		else if (currDir == TOP) currX--;

		// map을 벗어나는 경우
		if (currX <= 0 || currY <= 0) { bFail = false; break; }
		if (currX > nMapSize || currY > nMapSize) { bFail = false; break; }

		// 뱀과 만나는 경우
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
		else // 사과를 먹었을 때 
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