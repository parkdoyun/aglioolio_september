#include <iostream>
#include <map>

using namespace std;

// 백준 10942 - 팰린드롬?
// DP
// 골드 4

// 처음에 각 인덱스와 인덱스 사이를 중심으로 하는 가장 긴 회문 찾아서
// 처음 인덱스와 마지막 인덱스를 배열에 각각 저장한다
// s, e 입력받으면 해당 값의 중심을 찾아 가장 긴 회문의 범위 안에 들어가는지 확인한다.

// 시간 초과
// map 쓰지말고 arr로 쓰자 => map 시간 오래 걸림 => 해결

int arr[2001];

struct node
{
	int start; // 범위
	int end;
};

node map1[5000]; // 인덱스 사이(2와 3사이)를 중심으로 하는 회문도 찾아야 함


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);


	int n, m, s ,e;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}

	// map1 만들기 (회문 조사)
	int start, end;
	for (int i = 2; i <= 2 * n; i++)
	{
		if (i % 2 == 0) // 하나부터 시작하는 회문
		{
			start = i / 2;
			end = i / 2;
		}
		else // .5의 회문 처리
		{
			start = i / 2;
			end = i / 2 + 1;
		}
		while (arr[start] == arr[end] && start >= 1 && end <= n)
		{
			start--;
			end++;

		}
		map1[i].start = start + 1;
		map1[i].end = end - 1;
		//map1.insert({ (d / 2), {start + 1, end - 1} });
	}

	cin >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> s >> e;
		if (s == e)
		{
			cout << 1 << '\n';
			continue;
		}
		
		if (s >= map1[s + e].start && e <= map1[s + e].end)
		{
			cout << 1 << '\n';
		}
		else cout << 0 << '\n';
	}

	return 0;
}