/* [�ۼ���] 2017.01.17
[����] �ִ� �� https://www.acmicpc.net/problem/11279
�θ� �� �˷��� �ڷᱸ�� �� �ִ� ���̶�� ���� �ִ�. �ִ� ���� �̿��Ͽ� ������ ���� ������ �����ϴ� ���α׷��� �ۼ��Ͻÿ�.
�迭�� �ڿ��� x�� �ִ´�.
�迭���� ���� ū ���� ����ϰ�, �� ���� �迭���� �����Ѵ�.
���α׷��� ó���� ����ִ� �迭���� �����ϰ� �ȴ�.
[�Է�]
ù° �ٿ� ������ ���� N(1��N��100,000)�� �־�����. ���� N���� �ٿ��� ���꿡 ���� ������ ��Ÿ���� ���� x�� �־�����. 
���� x�� �ڿ������ �迭�� x��� ���� �ִ�(�߰��ϴ�) �����̰�, x�� 0�̶�� �迭���� ���� ū ���� ����ϰ� �� ���� �迭���� �����ϴ� ����̴�. 
�ԷµǴ� �ڿ����� 2^31���� �۴�.
[���]
�Է¿��� 0�� �־��� ȸ����ŭ ���� ����Ѵ�. ���� �迭�� ��� �ִ� ����ε� ���� ū ���� ����϶�� �� ��쿡�� 0�� ����ϸ� �ȴ�.
*/

//#define PROBLEM_11279
#ifdef PROBLEM_11279
#include<cstdio>

int *data;
int nDataCount;
void upheap(int nIndex)
{
	int tmp, parent;

	while (nIndex > 1) {
		tmp = data[nIndex];
		parent = nIndex / 2;
		if (data[nIndex] > data[parent])
		{
			data[nIndex] = data[parent];
			data[parent] = tmp;
			nIndex = parent;
		}
		else
			break;
	}
}

void downheap(int nEndIndex)
{
	int nIndex = 1;
	int tmp, child;

	while (nIndex <= nEndIndex / 2) {
		tmp = data[nIndex];
		child = nIndex * 2;

		if (data[child]<data[child + 1] && (child + 1) <= nEndIndex)
			child++;

		if (tmp < data[child])
		{
			data[nIndex] = data[child];
			data[child] = tmp;
			nIndex = child;
		}
		else
			break;
	}
}

void deleteroot()
{
	int nIndex = 1;

	if (nDataCount == 0)
	{
		printf("0\n");
		return;
	}
	else
	{
		printf("%d\n", data[nIndex]);
		data[nIndex] = data[nDataCount];
		data[nDataCount] = -1;
		nDataCount--;

		downheap(nDataCount);
	}
}

int main()
{
	int nCount;
	int nCommand;

	scanf("%d", &nCount);
	data = new int[100001];

	nDataCount = 0;
	while (nCount-- > 0)
	{
		scanf("%d", &nCommand);
		if (nCommand == 0)
		{
			deleteroot();
		}
		else
		{
			nDataCount++;
			data[nDataCount] = nCommand;
			upheap(nDataCount);
		}
	}

	return 0;
}
#endif // PROBLEM_11279