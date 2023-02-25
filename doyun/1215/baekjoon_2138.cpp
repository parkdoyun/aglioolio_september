#include <iostream>

using namespace std;

// 백준 2138 - 전구와 스위치
// greedy
// 골드 5

// 전구 한번만 끌지 켤지 해보면 답 나옴
// 어차피 끌지 켤지 한번에 결정되므로

// 두번만 해보면 된다
// 1. 처음 무조건 켤 때
// 2. 처음 무조건 켜지 않을 때

int light[100001];
int tmp[100001];
int goal[100001];
int n;
int flag = 0; // 만들면 1
int total_cnt = 1000000;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;

	char c;
	for (int i = 0; i < n; i++)
	{
		cin >> c;
		light[i] = (int)(c - '0');
	}
	for (int i = 0; i < n; i++)
	{
		cin >> c;
		goal[i] = (int)(c - '0');
	}

	// 처음 무조건 켜지 않을 때
	tmp[0] = light[0];
	tmp[1] = light[1];
	int cnt = 0;

	for (int i = 1; i < n - 1; i++)
	{
		if (tmp[i - 1] != goal[i - 1]) // 바꾼다
		{
			cnt++;
			if (tmp[i - 1] == 0) tmp[i - 1] = 1;
			else tmp[i - 1] = 0;
			if (tmp[i] == 0) tmp[i] = 1;
			else tmp[i] = 0;
			if (light[i + 1] == 0) tmp[i + 1] = 1;
			else tmp[i + 1] = 0;
		}
		else // 그냥 둔다
		{
			tmp[i + 1] = light[i + 1];
		}
	}

	// n - 1번째
	if (tmp[n - 2] != goal[n - 2]) // 바꾼다
	{
		cnt++;
		if (tmp[n - 2] == 0) tmp[n - 2] = 1;
		else tmp[n - 2] = 0;
		if (tmp[n - 1] == 0) tmp[n - 1] = 1;
		else tmp[n - 1] = 0;
	}

	// 같은지 체크
	int flag = 0;
	for (int i = 0; i < n; i++)
	{
		if (tmp[i] != goal[i])
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		if (total_cnt > cnt) total_cnt = cnt;
	}

	for (int i = 0; i < n; i++)
	{
		tmp[i] = 0;
	}

	// 처음 무조건 켤 때
	cnt = 1;
	if (light[0] == 0) tmp[0] = 1;
	else tmp[0] = 0;
	if (light[1] == 0) tmp[1] = 1;
	else tmp[1] = 0;

	for (int i = 1; i < n - 1; i++)
	{
		if (tmp[i - 1] != goal[i - 1]) // 바꾼다
		{
			cnt++;
			if (tmp[i - 1] == 0) tmp[i - 1] = 1;
			else tmp[i - 1] = 0;
			if (tmp[i] == 0) tmp[i] = 1;
			else tmp[i] = 0;
			if (light[i + 1] == 0) tmp[i + 1] = 1;
			else tmp[i + 1] = 0;
		}
		else // 그냥 둔다
		{
			tmp[i + 1] = light[i + 1];
		}
	}
	// n번째
	if (tmp[n - 2] != goal[n - 2]) // 바꾼다
	{
		cnt++;
		if (tmp[n - 2] == 0) tmp[n - 2] = 1;
		else tmp[n - 2] = 0;
		if (tmp[n - 1] == 0) tmp[n - 1] = 1;
		else tmp[n - 1] = 0;
	}

	// 같은지 체크
	flag = 0;
	for (int i = 0; i < n; i++)
	{
		if (tmp[i] != goal[i])
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		if (total_cnt > cnt) total_cnt = cnt;
	}

	if (total_cnt == 1000000) cout << -1;
	else cout << total_cnt;


	return 0;
}