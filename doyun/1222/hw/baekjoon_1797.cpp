#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// 백준 1797 - 균형잡힌 줄서기
// prefix sum
// 골드 2

// 이분 탐색
// 만약 만들 수 있다 -> 더 크게
// 만들 수 없다 -> 더 작게
// 2 단위로 해야 함

// mid를 2 단위로 고치는 과정에서 탐색에 포함 안 되는 값이 생기는 듯

// 이분 탐색으로 구해지지 X
// 부분합 문제
// 남 = -1, 여 = 1로 부분합 구하면 뺐을 때 0인 부분이 남자와 여자 수 같은 구역
// 부분합 같은 부분끼리는 한 구역으로 묶을 수 있다
// 부분합 같은 부분끼리 묶어서 끝값 더 크게 갱신
// 부분합 같은 부분끼리 묶기 -> 속도 줄이기 위하여 map 사용

// ***예외 조건 : 맨 처음(vec[1].n으로 시작하는 것, 부분합 0)도 넣어줘야 함***

struct node
{
	int n;
	int sex;
};
bool cmp(node n1, node n2)
{
	if (n1.n < n2.n) return true;
	return false;
}
struct node2
{
	int start = 0;
	int end = -1;
};
vector<node> vec;
map<int, node2> map1;

int sumArr[1000001];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	int s, n1;
	vec.push_back({ -9999, 0 }); // 1번 idx부터 시작 위해
	for (int i = 0; i < n; i++)
	{
		cin >> s >> n1;
		if (s == 0) s = -1;
		vec.push_back({ n1, s });
	}

	sort(vec.begin(), vec.end(), cmp);

	// 예외 조건 : 맨 처음도 넣어줘야 함 (부분합 0으로)
	node2 tmp;
	tmp.start = vec[1].n;
	map1.insert({ 0, tmp });

	for (int i = 1; i <= n; i++)
	{
		sumArr[i] = sumArr[i - 1] + vec[i].sex;
		if (map1.find(sumArr[i]) == map1.end())
		{
			if (i == n) break;
			node2 tmp;
			tmp.start = vec[i + 1].n;
			map1.insert({ sumArr[i], tmp });
		}
		else
		{
			if (map1[sumArr[i]].end == -1)
			{
				map1[sumArr[i]].end = vec[i].n;
			}
			else if (map1[sumArr[i]].end < vec[i].n) map1[sumArr[i]].end = vec[i].n;
		}
	}
	
	int max1 = 0;
	for (auto e : map1)
	{
		if (e.second.start != -1 && e.second.end != -1)
		{
			if (max1 < e.second.end - e.second.start) max1 = e.second.end - e.second.start;
		}
	}
	cout << max1;

	return 0;
}