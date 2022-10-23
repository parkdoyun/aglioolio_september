#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 백준 1041 - 주사위
// greedy
// 골드 5

// 모서리만 계산
// 나머지는 전부 최소값으로
// 위에 네 귀퉁이는 3개 => 짝지어서 해야됨
// (A, F), (B, E), (C, D) 짝
// 최소 3개와 최소 2개 구하기
// 밑에 네 귀퉁이는 2개
// 나머지 모서리도 2개
// 나머지 최소 평면만 나옴

bool cmp(int a, int b)
{
	if (a < b) return true;
	return false;
}

int dice[7];
vector<int> min_dice;


int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < 6; i++)
	{
		cin >> dice[i]; 
	}
	
	min_dice.push_back(min(dice[0], dice[5]));
	min_dice.push_back(min(dice[1], dice[4]));
	min_dice.push_back(min(dice[2], dice[3]));
	
	sort(min_dice.begin(), min_dice.end(), cmp);

	unsigned long long res = 0;
	
	int three = 0;
	for (int i = 0; i < 3; i++) three += min_dice[i];

	int two = three - min_dice[2];

	// 위 네 귀퉁이
	res += (unsigned long long)(three * 4);
	
	// 아래 네 귀퉁이
	res += (unsigned long long)(two * 4);

	// 모서리들 : 길이 n-2, 4개
	res += (unsigned long long)((n - 2) * two * 8);

	// 맨 밑 모서리들 : 4개, 길이 n-2
	res += (unsigned long long)((n - 2) * min_dice[0] * 4);

	// 나머지
	unsigned long long a = (unsigned long long)((unsigned long long)(n - 2) * (unsigned long long)(n - 2));
	a = (unsigned long long)(a * min_dice[0]);
	a = (unsigned long long)(a * 5);

	res += a;

	// 주사위 크기 1일 때 예외 처리
	if (n == 1)
	{
		int max = dice[0];
		res = 0;
		for (int i = 0; i < 6; i++)
		{
			res += dice[i];
			if (dice[i] > max) max = dice[i];
		}
		res -= max;
	}
	cout << res;

	return 0;
}