/* [�ۼ���] 2017.01.14
[����] ���� Ž�� Ʈ�� https://www.acmicpc.net/problem/2957
���� Ž�� Ʈ���� ��� ��尡 ���ƾ� 2���� �ڽ� ��带 ������ �ִ� Ʈ���̰�, �� ��忡�� ���ڰ� �ϳ��� �����ִ�. 
���� � ��忡 ���ִ� ���ڰ� X���, �� ����� ���� ����Ʈ������ X���� ���� ��, ������ ����Ʈ������ X���� ū ���� ����Ǿ� �־�� �Ѵ�.
1���� ũ�ų� ����, N���� �۰ų� ���� �� N���� �� ���� �����ϴ� ������ �Է����� �־�����. �� ������ �̿��ؼ� ���� Ž�� Ʈ���� ������� �Ѵ�. 
��, ������ ù��° ���ں���, ������ ���ڱ��� ���� Ž�� Ʈ���� �ִ� ���̸�, �� ���ڿ� ���ؼ� insert(X, root)�� ���ʴ�� ȣ���ϴ� ���̴�.
���� Ž�� Ʈ���� �����ϴ� �Լ��� ������ ����.

insert(number X, node N)
ī���� C���� 1 ������Ų��
if X�� ��� N�� �ִ� ���ں��� �۴ٸ�
if N�� ���� �ڽ��� ���ٸ�
X�� �����ϴ� �� ��带 ���� ��, N�� ���� �ڽ����� �����
else
insert(X, N�� ���� �ڽ�)
else (X�� ��� N�� �ִ� ���ں��� ũ�ٸ�)
if N�� ������ �ڽ��� ���ٸ�
X�� �����ϴ� �� ��带 ���� ��, N�� ������ �ڽ����� �����
else
insert(X, N�� ������ �ڽ�)

�� ���ڸ� ������ �Ŀ� C�� ���� ����ϴ� ���α׷��� �ۼ��Ͻÿ�. ī���� C�� ���� 0���� �ʱ�ȭ�Ǿ� �ִ�.
[�Է�]
ù° �ٿ� ������ ũ�� N�� �־�����. (1 �� N �� 300,000)
���� N���� �ٿ��� ������ ���ڰ� ���ʴ�� �־�����. ���ڴ� ���� [1, N]�� ���ԵǸ�, ��� ���ڴ� �ߺ����� �ʴ´�.
[���]
N���� �ٿ� �� ���ڰ� Ʈ���� ���Ե� �Ŀ� ī���� C���� �� �ٿ� �ϳ��� ����Ѵ�.
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