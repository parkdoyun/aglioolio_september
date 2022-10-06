#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// swea 5658 - 보물상자 비밀번호
// brute-force
// 문제 주어진대로 풀면 됨

int arr[29];
vector<int> vec;

bool cmp(int a, int b)
{
	if (a > b) return true;
	return false;
}

int main()
{
	int T, n, k;
	cin >> T;
	
	char c;
	for (int tc = 0; tc < T; tc++)
	{
		vec.clear();

		cin >> n >> k;
		for (int i = 0; i < n; i++)
		{
			cin >> c;
			if (c >= 'A' && c <= 'F')
			{
				arr[i] = (int)(c - 'A') + 10;
			}
			else
			{
				arr[i] = (int)(c - '0');
			}
		}

		// 4번 숫자들 모두 넣기
		int tmp;
		for (int i = 0; i < n / 4; i++) // i회전
		{
			// n / 4 개만큼 집어넣기
			int idx = i;
			int cnt = 0;
			while (cnt < n)
			{
				tmp = 0;
				for (int j = 0; j < n / 4; j++) {
					tmp += pow(16, n / 4 - j - 1) * arr[idx];
					idx = (idx + 1) % n;
					cnt++;
				}
				vec.push_back(tmp);
			}

		}
		
		sort(vec.begin(), vec.end(), cmp);

		// 중복 없애기
		vector<int>::iterator it;
		vector<int>::iterator it_del;
		for (it = vec.begin() + 1; it != vec.end();)
		{
			if (*it == *(it - 1))
			{
				it_del = it;
				//it++;
				vec.erase(it_del);
			}
			else it++;
		}
		// 출력
		cout << '#' << tc + 1 << ' ' << vec[k - 1] << '\n';
	}

	return 0;
}