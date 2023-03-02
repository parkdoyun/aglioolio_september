#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 백준 3151 - 합이 0
// two pointer
// 골드 4

// 한점 고정해놓고 나머지 투포인터
// 수 터지므로 long long int 해야 함

int n;
vector<long long int> score;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;

	int a, b, c;
	for (int i = 0; i < n; i++)
	{
		cin >> a;
		score.push_back(a);
	}

	sort(score.begin(), score.end());

	long long int cnt = 0;
	long long int tmp_res;
	for (int i = 0; i < n - 1; i++)
	{
		a = i;
		b = i + 1;
		c = n - 1;
		if (b >= c) continue;
		while (b < c)
		{
			tmp_res = (long long int)(score[a] + score[b] + score[c]);
			if (tmp_res > 0)
			{
				c--;
			}
			else if (tmp_res < 0)
			{
				b++;
			}
			else
			{
				if (score[b] == score[c]) // 시간 초과 처리
				{
					cnt += (long long int)((long long int)(c - b + 1) * (long long int)(c - b)) / 2;
					break;
				}
				else
				{
					int tmp1 = 0;
					int tmp2 = 0;
					int tmp_c = c;
					int tmp_b = b;
					
					while (score[tmp_c] == score[c]) // 시간 초과 처리
					{
						tmp1++;
						tmp_c--;
					}

					while (score[tmp_b] == score[b])
					{
						tmp2++;
						tmp_b++;
					}
					cnt += tmp1 * tmp2;
					c = tmp_c;
					b = tmp_b;
				}
				//break;
			}
		}
	}

	cout << cnt;

	return 0;
}