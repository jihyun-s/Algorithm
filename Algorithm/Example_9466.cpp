/* [�ۼ���] 2017.06.25
[����] �� ������Ʈ https://www.acmicpc.net/problem/9466
�̹� �����б⿡ '���� �ذ�' ���Ǹ� ��û�� �л����� �� ������Ʈ�� �����ؾ� �Ѵ�. ������Ʈ ���� ������ ������ ����. 
������ ��� �л����� ������ ���� ������ ���� ���� �� ���� ���� ���� �ִ�. 
������Ʈ ���� �����ϱ� ����, ��� �л����� ������Ʈ�� �Բ��ϰ� ���� �л��� �����ؾ� �Ѵ�. (��, �� �Ѹ� ������ �� �ִ�.) 
ȥ�� �ϰ� �;��ϴ� �л��� �ڱ� �ڽ��� �����ϴ� �͵� �����ϴ�.
�л�����(s1, s2, ..., sr)�̶� �� ��, r=1�̰� s1�� s1�� �����ϴ� ��쳪, s1�� s2�� �����ϰ�, s2�� s3�� �����ϰ�,..., sr-1�� sr�� �����ϰ�, 
sr�� s1�� �����ϴ� ��쿡�� �� ���� �� �� �ִ�.
���� ���, �� �ݿ� 7���� �л��� �ִٰ� ����. �л����� 1������ 7������ ǥ���� ��, ������ ����� ������ ����.
1	2	3	4	5	6	7
3	1	3	7	3	4	6
���� ����� ���� (3)�� (4, 7, 6)�� ���� �̷� �� �ִ�. 1, 2, 5�� ��� ������ ������ �ʴ´�.
�־��� ������ ����� ���� ��� ������Ʈ ������ ������ �ʴ� �л����� ���� ����ϴ� ���α׷��� �ۼ��϶�.
[�Է�]
ù° �ٿ� �׽�Ʈ ���̽��� ���� T�� �־�����. �� �׽�Ʈ ���̽��� ù �ٿ��� �л��� ���� ���� n (2 �� n �� 100,000)���� �־�����. 
�� �׽�Ʈ ���̽��� ��° �ٿ��� ���õ� �л����� ��ȣ�� �־�����. (��� �л����� 1���� n���� ��ȣ�� �ο��ȴ�.)
[���]
�� �׽�Ʈ ���̽����� �� �ٿ� ����ϰ�, �� �ٿ��� ������Ʈ ���� ������ ���� �л����� ���� ��Ÿ���� �ȴ�.
*/

//#define PROBLEM_9466
#ifdef PROBLEM_9466
#include<cstdio>

struct student
{
	int nNext;
	int nDepth;
	int nVisited;
};

student *pStd;
int nGroupStudent;
int nDepth = 0;

/*  �л� (startIndex, nextIndex) �� �� 
(4,3)
	(3,2)
		(2,1)
			(1,3) �� ��� 

(3)�� �̹� �湮�����Ƿ� return 3. (48 line) 
(2,1)�� 2�� return�� 3�� ���Ͽ� �ٸ��Ƿ� �ٽ� return 3 ( 58 line)
(3,2)�� 3�� return�� 3�� ���Ͽ� �����Ƿ� �� �׷����� üũ ( 55 line, 56 line)
*/
int dfs(int nStartIdx, int nCurrIdx)
{
	if (pStd[nCurrIdx].nVisited == -1)	// �湮�� ����� ��� ���� �л�index�� ���Ͻ�Ŵ
		return nCurrIdx;
	else
	{
		pStd[nCurrIdx].nVisited = -1;		// �湮�� ��� -1�� ����
		pStd[nCurrIdx].nDepth = nDepth++;	// ���̸� ������Ŵ (���߿� �л��� ����� ���ؼ�)
		int lastNum = dfs(nCurrIdx, pStd[nCurrIdx].nNext); // ����/���� �л� index�� �־ dfs()�� �ٽ� ȣ��. 
		if (nCurrIdx == lastNum)							// ����Ŭ�� ���
			nGroupStudent += nDepth - pStd[nCurrIdx].nDepth; // �ش�Ǵ� �л����ڸ�ŭ ����
		else
			return lastNum;
	}
	return -1;
}

int main()
{
	int testCount, studentCount;
	scanf("%d", &testCount);

	while (testCount-- > 0)
	{
		nGroupStudent = 0;

		scanf("%d", &studentCount);
		pStd = new student[studentCount];

		int tmp;
		for (int i = 0; i < studentCount; i++)
		{
			scanf("%d", &tmp);
			pStd[i].nNext = (tmp - 1);
			pStd[i].nDepth = 0;
			pStd[i].nVisited = 0;
		}

		for (int i = 0; i < studentCount; i++)
		{
			if (pStd[i].nVisited != -1)
				dfs(i, i);

			nDepth = 0;
		}

		printf("%d\n", studentCount - nGroupStudent);
		delete pStd;
	}

	return 0;
}
#endif