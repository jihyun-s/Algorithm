/* [작성일] 2017.01.14
[문제] 이진 탐색 트리 https://www.acmicpc.net/problem/2957
이진 탐색 트리는 모든 노드가 많아야 2개의 자식 노드를 가지고 있는 트리이고, 각 노드에는 숫자가 하나씩 쓰여있다. 
만약 어떤 노드에 써있는 숫자가 X라면, 그 노드의 왼쪽 서브트리에는 X보다 작은 수, 오른쪽 서브트리에는 X보다 큰 수만 저장되어 있어야 한다.
1보다 크거나 같고, N보다 작거나 같은 수 N개가 한 번씩 등장하는 수열이 입력으로 주어진다. 이 수열을 이용해서 이진 탐색 트리를 만드려고 한다. 
즉, 수열의 첫번째 숫자부터, 마지막 숫자까지 이진 탐색 트리에 넣는 것이며, 각 숫자에 대해서 insert(X, root)를 차례대로 호출하는 것이다.
이진 탐색 트리에 삽입하는 함수는 다음과 같다.

insert(number X, node N)
카운터 C값을 1 증가시킨다
if X가 노드 N에 있는 숫자보다 작다면
if N의 왼쪽 자식이 없다면
X를 포함하는 새 노드를 만든 뒤, N의 왼쪽 자식으로 만든다
else
insert(X, N의 왼쪽 자식)
else (X가 노드 N에 있는 숫자보다 크다면)
if N의 오른쪽 자식이 없다면
X를 포함하는 새 노드를 만든 뒤, N의 오른쪽 자식으로 만들기
else
insert(X, N의 오른쪽 자식)

각 숫자를 삽입한 후에 C의 값을 출력하는 프로그램을 작성하시오. 카운터 C의 값은 0으로 초기화되어 있다.
[입력]
첫째 줄에 수열의 크기 N이 주어진다. (1 ≤ N ≤ 300,000)
다음 N개의 줄에는 수열의 숫자가 차례대로 주어진다. 숫자는 구간 [1, N]에 포함되며, 모든 숫자는 중복되지 않는다.
[출력]
N개의 줄에 각 숫자가 트리에 삽입된 후에 카운터 C값을 한 줄에 하나씩 출력한다.
*/

#define PROBLEM_2957
#ifdef PROBLEM_2957
#include<cstdio>
#include<map>
#include<iterator>
#include<algorithm>
using namespace std;
map<int, int> treemap;
signed long long int count = -1;
void insertNumber(int nNumber)
{
	int upper = 0, lower = 0, depth;
	pair<int, int> tmp;
	map<int, int>::iterator itr = treemap.upper_bound(nNumber);

	if (itr != treemap.end())
		upper = itr->second;

	itr = treemap.lower_bound(nNumber);

	//if( itr != treemap.end() )  
	{
		itr--;

		if (itr != treemap.end())
		{
			lower = itr->second;
		}
	}

	depth = max(upper, lower) + 1;
	count += depth;
	treemap.insert(make_pair(nNumber, depth));
	printf("%lld\n", count);
}
int main()
{
	int nCount, nNumber;
	scanf("%d", &nCount);
	scanf("%d", &nNumber);
	treemap.insert(make_pair(nNumber, 0));
	printf("%d\n", ++count);
	nCount--;

	while (nCount-- > 0)
	{
		scanf("%d", &nNumber);
		insertNumber(nNumber);
	}
	return 0;
}
#endif