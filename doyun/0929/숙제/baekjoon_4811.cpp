#include <iostream>

using namespace std;

// 백준 4811 - 알약
// DP
// 골드 4

// 조건 1 : 같은 개수의 W는 무조건 H보다 앞에 있어야 한다.
// 조건 2 : W와 H는 각각 N개 있어야 한다.
// 조건 3 : 맨 처음은 W, 맨 마지막은 H

// 점화식 DP[w][h] = DP[w-1][h] + DP[w][h-1]
// w개의 W, h개의 H로 이루어진 문자열 = w-1개의 W, h개의 H로 이루어진 문자열 + 'W' 
// w개의 W, h개의 H로 이루어진 문자열 = w개의 W, h-1개의 H로 이루어진 문자열 + 'H'
// h > w인 상황은 없으므로 continue (H 개수의 최댓값은 W 개수)

long long DP[31][31];

int main()
{
	// DP 먼저 채우기
	// 기저 조건
	DP[0][0] = 0;
	DP[1][0] = 1;

	for (int w = 1; w <= 30; w++)
	{
		// W로만 이루어진 문자열 1
		DP[w][0] = 1;
		for (int h = 1; h <= 30; h++)
		{
			if (h > w) break;
			DP[w][h] = DP[w - 1][h] + DP[w][h - 1];
		}
	}

	int t;
	while (true)
	{
		cin >> t;
		if (t == 0) break;

		cout << DP[t][t] << '\n';

	}

	return 0;
}