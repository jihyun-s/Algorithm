/* [작성일] 2017.07.02
[문제] 숨바꼭질 https://www.acmicpc.net/problem/1697
수빈이는 동생과 숨바꼭질을 하고 있다. 수빈이는 현재 점 N(0 ≤ N ≤ 100,000)에 있고, 동생은 점 K(0 ≤ K ≤ 100,000)에 있다. 
수빈이는 걷거나 순간이동을 할 수 있다. 만약, 수빈이의 위치가 X일 때 걷는다면 1초 후에 X-1 또는 X+1로 이동하게 된다. 
순간이동을 하는 경우에는 1초 후에 2*X의 위치로 이동하게 된다.
수빈이와 동생의 위치가 주어졌을 때, 수빈이가 동생을 찾을 수 있는 가장 빠른 시간이 몇 초 후인지 구하는 프로그램을 작성하시오.
[입력]
첫 번째 줄에 수빈이가 있는 위치 N과 동생이 있는 위치 K가 주어진다.
[출력]
수빈이가 동생을 찾는 가장 빠른 시간을 출력한다.
*/

#define EXAMPLE_1697
#ifdef EXAMPLE_1697
#include<cstdio>
#include<queue>
using namespace std;
queue<pair<int, int>> visited;
int visitedNode[100001];

void pushChild(int x, int nDepth)
{
	if (x >= 0 && x <= 100000 && visitedNode[x] != 1)
	{
		visited.push(make_pair(x, nDepth));
		visitedNode[x] = 1;
	}
}

int bfs(int x, int nStop, int nDepth)
{
	if (x == nStop)  return nDepth;

	do
	{
		pair<int, int> curr = visited.front();
		visited.pop();

		int a = curr.first + 1;
		int b = curr.first - 1;
		int c = 2 * curr.first;
		curr.second++;

		if (a == nStop || b == nStop || c == nStop)
			return curr.second;

		pushChild(a, curr.second);
		pushChild(b, curr.second);
		pushChild(c, curr.second);

	} while (!visited.empty());

	return -1;
}

int main() {
	int nMove, nStop;
	int nFindCount = 0;
	scanf("%d%d", &nMove, &nStop);

	visited.push(make_pair(nMove, 0));
	visitedNode[nMove] = 1;

	printf("%d\n", bfs(nMove, nStop, 0));
	return 0;
}

#endif