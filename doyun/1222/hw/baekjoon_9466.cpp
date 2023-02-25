#include <iostream>

using namespace std;

// 백준 9466 - 텀 프로젝트
// DFS
// 골드 3

// DFS로 cycle 확인
// 이미 cycle 확정된 애는 2로 표시, 검사중인 애는 1, cycle 안 된 애는 -1

int arr[100001];
int chk[100001]; // 이미 cycle 확정된 애는 2로 표시, 검사중인 애는 1, cycle 안 된 애는 -1

int findR(int a)
{
	if (arr[a] == a) // 얘만 팀이고 나머진 아웃
	{
		chk[a] = 2;
		return -1;
	}
	else if (chk[arr[a]] == 1) // 검사 중 -> 얘부터 나까지만 cycle 돈다
	{
		chk[a] = 2;
		chk[arr[a]] = 2;
		return 1;
	}
	else if (chk[arr[a]] == 2) // 나 포함되지 않는 다른 cycle
	{
		chk[a] = -1;
		return -1;
	}
	else if (chk[arr[a]] == -1)
	{
		chk[a] = -1;
		return -1;
	}

	chk[a] = 1;
	int answer = findR(arr[a]);
	if (answer == -1) // cycle X에 포함 X
	{
		chk[a] = -1;
		return -1;
	}
	else if (answer == 1 && chk[a] == 2) // 나까지만 cycle, 내 뒤부터 cycle X
	{
		return -1;
	}
	else if (answer == 1 && chk[a] == 1) // 나는 cycle에 포함
	{
		chk[a] = 2;
		return 1;
	}
	return 0;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int T, n;
	cin >> T;

	for (int tc = 1; tc <= T; tc++)
	{
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			cin >> arr[i];
			chk[i] = 0;
		}
		for (int i = 1; i <= n; i++)
		{
			if (chk[i] != 0) continue;
			findR(i);
		}
		int cnt = 0;
		for (int i = 1; i <= n; i++)
		{
			if (chk[i] == -1) cnt++;
		}
		cout << cnt << '\n';
	}

	return 0;

}