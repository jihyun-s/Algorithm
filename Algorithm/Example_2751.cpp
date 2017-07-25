/* [�ۼ���] 2017.01.17
[����] �� �����ϱ� 2  https://www.acmicpc.net/problem/2751
N���� ���� �־����� ��, �̸� ������������ �����ϴ� ���α׷��� �ۼ��Ͻÿ�.
[�Է�]
ù° �ٿ� ���� ���� N(1<=N<=1,000,000)�� �־�����. ��° �ٺ��� N���� �ٿ��� ���ڰ� �־�����. �� ���� ���밪�� 1,000,000���� �۰ų� ���� �����̴�. 
���� �ߺ����� �ʴ´�.
[���]
ù° �ٺ��� N���� �ٿ� ������������ ������ ����� �� �ٿ� �ϳ��� ����Ѵ�.
*/

// ������
//#define PROBLEM_2751
#ifdef PROBLEM_2751

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
	int nEndIndex = nDataCount;
	//int nExternalNodeCount = nDataCount/2;
	int tmp;

	while (nEndIndex > nIndex) {
		// root�� ������ ���� ��ȯ
		tmp = data[nIndex];
		data[nIndex] = data[nEndIndex];
		data[nEndIndex] = tmp;
		nEndIndex--;

		downheap(nEndIndex);
	}
}

void printheap()
{
	for (int i = 1; i<(nDataCount + 1); i++)
		printf("%d\n", data[i]);
}

int main()
{
	int nIndex;
	scanf("%d", &nDataCount);
	data = new int[nDataCount + 1];

	nIndex = 1;
	while (nIndex < nDataCount + 1)
	{
		scanf("%d", &data[nIndex]);
		upheap(nIndex);
		nIndex++;
	}
	deleteroot();
	printheap();
	return 0;
}
#endif // PROBLEM_2751