/* [�ۼ���] 2017.02.19
[����] ������ https://www.acmicpc.net/problem/2580
������� 18���� ������ �����ڰ� ���� '��ƾ �簢��'�̶� ���񿡼� ������ ������ ���� ���� �α⸦ ������ �ִ�. 
�� ������ �Ʒ� �׸��� ���� ����, ���� ���� 9���� �� 81���� ���� ĭ���� �̷���� ���簢�� �� ������ �̷����µ�, ���� ���� �� �� �� ĭ���� 1���� 9������ ���� �� �ϳ��� ���� �ִ�.
������ �� ĭ�� ä��� ����� ������ ����.

������ �����ٰ� �����ٿ��� 1���� 9������ ���ڰ� �� ������ ��Ÿ���� �Ѵ�.
���� ������ ���еǾ� �ִ� 3x3 ���簢�� �ȿ��� 1���� 9������ ���ڰ� �� ������ ��Ÿ���� �Ѵ�.
���� ���� ���, ù° �ٿ��� 1�� ������ ������ 2���� 9������ ���ڵ��� �̹� ��Ÿ�� �����Ƿ� ù° �� ��ĭ���� 1�� ���� �Ѵ�.

���� ���� ��� ��ġ�� 3x3 ���簢���� ��쿡�� 3�� ������ ������ ���ڵ��� �̹� ���������Ƿ� ��� �� ĭ���� 3�� ���� �Ѵ�.
�̿� ���� �� ĭ�� ���ʷ� ä�� ���� ������ ���� ���� ����� ���� �� �ִ�.
���� ���� �� ������ �ǿ� ���� �ִ� ���ڵ��� ������ �־��� �� ��� �� ĭ�� ä���� ���� ����� ����ϴ� ���α׷��� �ۼ��Ͻÿ�.
[�Է�]
��ȩ �ٿ� ���� �� �ٿ� 9���� ���� ���� �� �������� �� �ٿ� ���� �ִ� ���ڰ� �� ĭ�� ����� ���ʷ� �־�����. ������ ���� �� ĭ�� ��쿡�� 0�� �־�����. 
������ ���� ��Ģ��� ä�� �� ���� ����� �Է��� �־����� �ʴ´�.
[���]
��� �� ĭ�� ä���� ������ ���� ���� ����� ��ȩ�ٿ� ���� �� �ٿ� 9���� �� ĭ�� ����� ����Ѵ�.
������ ���� ä��� ����� ������ ���� �� �� �ϳ����� ����Ѵ�.
*/

#define PROBLEM_2580
#ifdef PROBLEM_2580
#include<iostream>
using namespace std;

int value[9][9];

bool checkVertical(int nX, int nNum)
{
	for (int i = 0; i < 9; i++)
	{
		if (nNum == value[i][nX])
			return true;
	}
	return false;
}

bool checkHori(int nY, int nNum)
{
	for (int i = 0; i < 9; i++)
	{
		if (nNum == value[nY][i])
			return true;
	}
	return false;
}

bool checkSquare(int nX, int nY, int nNum)
{
	nX = nX / 3 * 3;
	nY = nY / 3 * 3;

	for (int i = nX; i < (3 + nX); i++)
		for (int j = nY; j < (3 + nY); j++)
			if (nNum == value[j][i])
				return true;
	return false;
}

void solveProblem(int nX, int nY, int nNum)
{
	int nOldX = nX;
	int nOldY = nY;

	if (nNum != -1)
	{
		if (checkHori(nY, nNum))	return;
		if (checkVertical(nX, nNum)) return;
		if (checkSquare(nX, nY, nNum)) return;

		// �� setting 
		value[nY][nX] = nNum;
	}

	do {
		if (nX == 8)
		{
			nX = 0;
			nY++;
		}
		else
			nX++;

		if (nY >= 9) return;
	} while (value[nY][nX] != 0);

	for (int i = 1; i <= 9; i++)
	{
		solveProblem(nX, nY, i);
		if (value[nY][nX] != 0)
			return;
	}

	if (value[nY][nX] == 0)
	{
		value[nOldY][nOldX] = 0;
		return;
	}
}

void printResult()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			printf("%d ", value[i][j]);

		printf("\n");
	}
}

int main()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			scanf("%d", &value[i][j]);
		}
	}

	solveProblem(-1, 0, -1);

	printResult();

	return 0;
}

#endif