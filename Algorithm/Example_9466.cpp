/* [작성일] 2017.06.25
[문제] 텀 프로젝트 https://www.acmicpc.net/problem/9466
이번 가을학기에 '문제 해결' 강의를 신청한 학생들은 텀 프로젝트를 수행해야 한다. 프로젝트 팀원 수에는 제한이 없다. 
심지어 모든 학생들이 동일한 팀의 팀원인 경우와 같이 한 팀만 있을 수도 있다. 
프로젝트 팀을 구성하기 위해, 모든 학생들은 프로젝트를 함께하고 싶은 학생을 선택해야 한다. (단, 단 한명만 선택할 수 있다.) 
혼자 하고 싶어하는 학생은 자기 자신을 선택하는 것도 가능하다.
학생들이(s1, s2, ..., sr)이라 할 때, r=1이고 s1이 s1을 선택하는 경우나, s1이 s2를 선택하고, s2가 s3를 선택하고,..., sr-1이 sr을 선택하고, 
sr이 s1을 선택하는 경우에만 한 팀이 될 수 있다.
예를 들어, 한 반에 7명의 학생이 있다고 하자. 학생들을 1번부터 7번으로 표현할 때, 선택의 결과는 다음과 같다.
1	2	3	4	5	6	7
3	1	3	7	3	4	6
위의 결과를 통해 (3)과 (4, 7, 6)이 팀을 이룰 수 있다. 1, 2, 5는 어느 팀에도 속하지 않는다.
주어진 선택의 결과를 보고 어느 프로젝트 팀에도 속하지 않는 학생들의 수를 계산하는 프로그램을 작성하라.
[입력]
첫째 줄에 테스트 케이스의 개수 T가 주어진다. 각 테스트 케이스의 첫 줄에는 학생의 수가 정수 n (2 ≤ n ≤ 100,000)으로 주어진다. 
각 테스트 케이스의 둘째 줄에는 선택된 학생들의 번호가 주어진다. (모든 학생들은 1부터 n까지 번호가 부여된다.)
[출력]
각 테스트 케이스마다 한 줄에 출력하고, 각 줄에는 프로젝트 팀에 속하지 못한 학생들의 수를 나타내면 된다.
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

/*  학생 (startIndex, nextIndex) 일 때 
(4,3)
	(3,2)
		(2,1)
			(1,3) 인 경우 

(3)은 이미 방문했으므로 return 3. (48 line) 
(2,1)의 2와 return된 3을 비교하여 다르므로 다시 return 3 ( 58 line)
(3,2)의 3과 return된 3을 비교하여 같으므로 한 그룹으로 체크 ( 55 line, 56 line)
*/
int dfs(int nStartIdx, int nCurrIdx)
{
	if (pStd[nCurrIdx].nVisited == -1)	// 방문한 노드인 경우 현재 학생index를 리턴시킴
		return nCurrIdx;
	else
	{
		pStd[nCurrIdx].nVisited = -1;		// 방문한 경우 -1로 설정
		pStd[nCurrIdx].nDepth = nDepth++;	// 깊이를 증가시킴 (나중에 학생수 계산을 위해서)
		int lastNum = dfs(nCurrIdx, pStd[nCurrIdx].nNext); // 현재/다음 학생 index를 넣어서 dfs()를 다시 호출. 
		if (nCurrIdx == lastNum)							// 사이클인 경우
			nGroupStudent += nDepth - pStd[nCurrIdx].nDepth; // 해당되는 학생숫자만큼 더함
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