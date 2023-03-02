#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// softeer - 교차로
// simulation
// q 4개 (A,B,C,D)
// 런타임 에러 => vector나 큐 잘못 참조인듯 (비었을 때)
// 일단 차가 뒤에 나올 수 있을 때 대기하는 코드 X
// 끝나면 바로 나가버림
// 별 3

int n;
long long int t;
char w;

struct car
{
	long long int time;
	int idx;
};

queue<car> q[4];
vector<long long int> vec; // 나간 시간 기록
int flag[4]; // 2 : 시간 안 돼서 나갈 수 없음, 1 : 오른쪽에 차 있어서 나갈 수 없음, 0 : 나갈 수 있음

int chkCar(long long int now_time)
{
	int empty_flag = 0;
	int next; // 오른쪽 도로
	for (int i = 0; i < 4; i++)
	{
		if (q[i].empty())
		{
			flag[i] = 1;
			continue;
		}
		next = i - 1;
		if (next == -1) next = 3;

		empty_flag = 1;

		if (!q[next].empty() && q[next].front().time <= now_time) flag[i] = 1; // 옆에 차 있음
		else if (q[i].front().time > now_time) flag[i] = 2; // 차 없는데 시간이 안 됨
		else flag[i] = 0; // 차 없고 나갈 수 있음
	}
	if (empty_flag == 0) return -1; // 차가 전부 없다면

	// 차 있어서 교착 상태
	if (flag[0] == 1 && flag[1] == 1 && flag[2] == 1 && flag[3] == 1) return -1;

	// 나갈 수 있는 애들 있다면
	if (flag[0] == 0 || flag[1] == 0 || flag[2] == 0 || flag[3] == 0) return 0;

	// 옆에 차 있어서 나갈 수 없는 상태 + 시간 안 돼서 못 나오는 애들만 있다면
	return 2;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	vec.resize(n + 1);

	for (int i = 0; i < n; i++)
	{
		cin >> t >> w;
		q[(int)(w - 'A')].push({ t, i });
		vec[i] = -1;
	}

	// 하나씩 빼기
	long long int now_time = q[0].front().time;
	for (int i = 1; i < 4; i++)
	{
		if (q[i].empty()) continue;
		if (q[i].front().time < now_time) now_time = q[i].front().time;
	}

	// 되는 애들 전부 한번에 빼기 (동시에)
	int res;
	while (true)
	{
		res = chkCar(now_time);

		// deadlock이나 다 나갔음
		if (res == -1) break;

		// 시간 기다려야 함
		if (res == 2)
		{
			now_time = 9999999999;
			for (int i = 0; i < 4; i++)
			{
				if (q[i].empty()) continue;
				else if (q[i].front().time < now_time) now_time = q[i].front().time;
			}
			continue;
		}

		// 나갈 수 있는 애들 pop
		for (int i = 0; i < 4; i++)
		{
			if (flag[i] == 0)
			{
				vec[q[i].front().idx] = now_time;
				q[i].pop();
			}
		}
		now_time++;
	}

	// 결과 출력
	for (int i = 0; i < n; i++) cout << vec[i] << '\n';

	return 0;
}