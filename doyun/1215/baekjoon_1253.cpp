#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// 백준 1253 - 좋다
// map
// 골드 4

// 다른 수 두개의 합 => 나 + 0은 안 됨
// 맵에 벡터 넣자 (어떤 애들로 이루어진 건지 구성된 벡터)

struct node // a번째와 b번째가 더해서 만들어짐
{
	int a;
	int b;
};

map<long long int, vector<node>> m;
vector<long long int> vec;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	long long int a;
	for (int i = 0; i < n; i++)
	{
		vector<node> vec2;
		cin >> a;
		vec.push_back(a);
		if (m.find(a) == m.end())
		{
			m.insert({ a, vec2 });
		}
	}

	sort(vec.begin(), vec.end());

	// 두개 수 계산
	long long int tmp;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			tmp = (long long int)(vec[i] + vec[j]);
			if (m.find(tmp) != m.end())
			{
				m[tmp].push_back({ i, j });
			}
		}
	}

	int cnt = 0;

	for (int i = 0; i < n; i++)
	{
		if (m.find(vec[i]) != m.end() && m[vec[i]].size() != 0)
		{
			for (int j = 0; j < m[vec[i]].size(); j++)
			{
				// 만약 나로 이루어진 애들말고 있다면 cnt++
				if (m[vec[i]][j].a != i && m[vec[i]][j].b != i)
				{
					cnt++;
					break;
				}
			}

		}
	}

	cout << cnt;

	return 0;
}