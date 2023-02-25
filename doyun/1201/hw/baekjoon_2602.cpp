#include <iostream>
#include <string>

using namespace std;

// 백준 2602 - 돌다리 건너기
// DP
// 골드 4

// 첫글자 먼저 체크
// 두번째 글자 -> 인접한 다리에서 나보다 전의 첫번째 애들 다 더하기
// 마지막 글자 때 가짓수 다 더해서 출력
// 3차원 배열

int bridge[21][2][101]; // bridge[][0] : 악마 다리, bridge[][1] : 천사 다리

int main()
{
	string magic, devil, angel;

	cin >> magic >> devil >> angel;

	// 첫 글자
	for (int j = 0; j < devil.length(); j++)
	{
		if (magic[0] == devil[j])
		{
			bridge[0][0][j]++;
		}
		if (magic[0] == angel[j])
		{
			bridge[0][1][j]++;
		}
	}

	for (int i = 1; i < magic.length(); i++)
	{
		for (int j = 0; j < devil.length(); j++)
		{
			if (magic[i] == devil[j]) // 같으면 나 전에 이전 것들 더하자
			{
				for (int k = 0; k < j; k++)
				{
					if (bridge[i - 1][1][k] > 0) bridge[i][0][j] += bridge[i - 1][1][k];
				}
			}
			if (magic[i] == angel[j]) // 같으면 나 전에 이전 것들 더하자
			{
				for (int k = 0; k < j; k++)
				{
					if (bridge[i - 1][0][k] > 0) bridge[i][1][j] += bridge[i - 1][0][k];
				}
			}
		}
	}

	// 결과 출력
	int total_cnt = 0;
	int t_len = magic.length() - 1;
	for (int i = 0; i < angel.length(); i++)
	{
		total_cnt += bridge[t_len][0][i];
		total_cnt += bridge[t_len][1][i];
	}

	cout << total_cnt;

	return 0;
}