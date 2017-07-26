/* [�ۼ���] 2017.06.05
[����] ȸ���ϴ� ť https://www.acmicpc.net/problem/1021
�����̴� N���� ���Ҹ� �����ϰ� �ִ� ����� ��ȯ ť�� ������ �ִ�. �����̴� �� ť���� �� ���� ���Ҹ� �̾Ƴ����� �Ѵ�.
�����̴� �� ť���� ������ ���� 3���� ������ ������ �� �ִ�.
ù��° ���Ҹ� �̾Ƴ���. �� ������ �����ϸ�, ���� ť�� ���Ұ� a1, ..., ak�̾��� ���� a2, ..., ak�� ���� �ȴ�.
�������� �� ĭ �̵���Ų��. �� ������ �����ϸ�, a1, ..., ak�� a2, ..., ak, a1�� �ȴ�.
���������� �� ĭ �̵���Ų��. �� ������ �����ϸ�, a1, ..., ak�� ak, a1, ..., ak-1�� �ȴ�.
ť�� ó���� ���ԵǾ� �ִ� �� N�� �־�����. �׸��� �����̰� �̾Ƴ����� �ϴ� ������ ��ġ�� �־�����. (�� ��ġ�� ���� ó�� ť������ ��ġ�̴�.) 
�� ��, �� ���Ҹ� �־��� ������� �̾Ƴ��µ� ��� 2��, 3�� ������ �ּڰ��� ����ϴ� ���α׷��� �ۼ��Ͻÿ�.
[�Է�]
ù° �ٿ� ť�� ũ�� N�� �̾Ƴ����� �ϴ� ���� ���� M�� �־�����. N�� 50���� �۰ų� ���� �ڿ����̰�, M�� N���� �۰ų� ���� �ڿ����̴�. 
��° �ٿ��� �����̰� �̾Ƴ����� �ϴ� ���� ��ġ�� ������� �־�����. ��ġ�� 1���� ũ�ų� ����, N���� �۰ų� ���� �ڿ����̴�.
[���] 
ù° �ٿ� ������ ������ ����Ѵ�.
*/

#define PROBLEM_1021
#ifdef PROBLEM_1021

#include <cstdio>

void DeleteIndexAt(int* queue, int& nQSize, int nIndex)
{
	nQSize--;

	for (int i = nIndex; i < nQSize; i++)
		queue[i] = queue[i + 1];
}

int PopQueue(int* queue, int* pop_queue, int nQSize, int nQPopSize)
{
	int nQueueIndex = 0;
	int nPopQueueIndex = 0;
	int nTotal = 0;

	do
	{
		int nPopNumber = pop_queue[nPopQueueIndex];

		if (queue[nQueueIndex] == nPopNumber)
		{
			DeleteIndexAt(queue, nQSize, nQueueIndex);

			nPopQueueIndex++;
			continue;
		}

		int lCount = 0;

		for (int i = 0; i < nQSize; i++)
		{
			if (queue[(i + nQueueIndex) % nQSize] == nPopNumber)
			{
				nQueueIndex = (i + nQueueIndex) % nQSize;

				if (i >(nQSize / 2))
					lCount = (nQSize - i);
				else
					lCount = i;

				DeleteIndexAt(queue, nQSize, nQueueIndex);
				break;
			}
		}

		nTotal += lCount;
		nPopQueueIndex++;

	} while (nPopQueueIndex < nQPopSize);

	return nTotal;
}

int main()
{
	int nSize, nPopCount;

	scanf("%d%d", &nSize, &nPopCount);

	int *queue = new int[nSize];
	int *pop_queue = new int[nPopCount];

	for (int i = 0; i < nSize; i++)
		queue[i] = i + 1;

	for (int i = 0; i < nPopCount; i++)
		scanf("%d", &pop_queue[i]);

	printf("%d\n", PopQueue(queue, pop_queue, nSize, nPopCount));

	return 0;
}
#endif