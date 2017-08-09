/* [�ۼ���] 2017.07.02
[����] ���ٲ��� https://www.acmicpc.net/problem/1697
�����̴� ������ ���ٲ����� �ϰ� �ִ�. �����̴� ���� �� N(0 �� N �� 100,000)�� �ְ�, ������ �� K(0 �� K �� 100,000)�� �ִ�. 
�����̴� �Ȱų� �����̵��� �� �� �ִ�. ����, �������� ��ġ�� X�� �� �ȴ´ٸ� 1�� �Ŀ� X-1 �Ǵ� X+1�� �̵��ϰ� �ȴ�. 
�����̵��� �ϴ� ��쿡�� 1�� �Ŀ� 2*X�� ��ġ�� �̵��ϰ� �ȴ�.
�����̿� ������ ��ġ�� �־����� ��, �����̰� ������ ã�� �� �ִ� ���� ���� �ð��� �� �� ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
[�Է�]
ù ��° �ٿ� �����̰� �ִ� ��ġ N�� ������ �ִ� ��ġ K�� �־�����.
[���]
�����̰� ������ ã�� ���� ���� �ð��� ����Ѵ�.
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