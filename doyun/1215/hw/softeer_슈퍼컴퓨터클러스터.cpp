#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// softeer - 슈퍼 컴퓨터 클러스터
// binary-search
// 별 3

// 가장 낮은 애들 올리는 것 전부 해보기
// 만약 넘으면 break
// pq로 낮은 애들끼리

// 이진 탐색 쓰자
// start = 컴퓨터 성능 최소, end = 컴퓨터 성능 최대

// 변수 계속 터짐
// 터지기 전에 함수 잘라야 함
// 변수 범위 지정해줘야 함 (아님 너무 커서 터지는 듯)

int n;
unsigned long long int a, b;
unsigned long long int max1 = 0;

vector<unsigned long long int> vec;
bool cmp(unsigned long long int l1, unsigned long long int l2)
{
	if (l1 < l2) return true;
	return false;
}

bool cal(unsigned long long int goal)
{
	unsigned long long int tmp_budget = 0;

	for (int i = 0; i < n; i++)
	{
		if (vec[i] >= goal) break;

		// 곱하는 부분에서 터질 수도 있음
		if ((unsigned long long int)(goal - vec[i]) >= 4294967296 || (unsigned long long int)(goal - vec[i]) > b) return false;
		else if ((unsigned long long int)((unsigned long long int)(goal - vec[i]) * (unsigned long long int)(goal - vec[i])) > (unsigned long long int)(b - tmp_budget)) return false;

		tmp_budget = (unsigned long long int)(tmp_budget + (unsigned long long int)((unsigned long long int)(goal - vec[i]) * (unsigned long long int)(goal - vec[i])));

		// 변수 터지기 전에 함수 자르기
		if (tmp_budget > b) return false;

	}

	if (tmp_budget <= b) return true;
	return false;
}

void binary_search(unsigned long long int max, unsigned long long int min)
{
	unsigned long long int start = min;
	unsigned long long int end = max;
	unsigned long long int mid;

	while (start <= end)
	{
		mid = (unsigned long long int)((unsigned long long int)(start + end) / 2);

		// mid가 가능한지 확인
		bool res = cal(mid); // 가능한지 확인(mid 값이 최소로 되는지)
		if (res == true) // 가능하다면
		{
			if (mid > max1) max1 = mid;
			start = (unsigned long long int)(mid + (unsigned long long int)1);
		}
		else // 불가능하다면
		{
			end = (unsigned long long int)(mid - (unsigned long long int)1);
		}
	}
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> b;
	
	for (int i = 0; i < n; i++)
	{
		cin >> a;
		vec.push_back(a);
	}
	sort(vec.begin(), vec.end(), cmp);

	max1 = 0;
	binary_search(2000000000, 0); // 이렇게 해줘야지 최대 b로 하면 오답 처리됨

	cout << max1;

	return 0;
}