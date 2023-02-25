#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 백준 2110 - 공유기 설치
// binary search
// 골드 4

// binary search
// mid : 가장 인접한 공유기 사이 거리
// 만약 mid보다 큰 곳에 있다면 ok -> 최댓값 비교 및 start++
// mid보다 작은 곳에 인접 지역 있다면 -> end--
// 꼭 인접한 집들마다 공유기 설치 안 해도 됨

// 시간 초과
// 이분탐색 잘 확인하자

vector<long long int> vec;
int n, c;
long long int max1 = 0;

bool chkLen(long long int len)
{
	long long int prev = vec[0];
	int idx = 1;
	long long int now;
	int cnt = 0;
	
	while (idx < n)
	{
		now = vec[idx];
		if (vec[idx] - prev >= len) // 되는 경우 붙어있으면 계속 넘기기
		{
			prev = vec[idx];
			cnt++;
			idx++;
		}
		else // vec[idx] - prev < len => 만약 붙어있다면 뒤로 밀기
		{
			idx++;
		}
	}
	cnt++;

	if (cnt < c) return false;
	return true;
}

void binary_search()
{
	long long int start = 0;
	long long int end = vec.back();
	long long int mid;

	while (start <= end)
	{
		mid = (long long int)(start + end) / 2;

		if (chkLen(mid))
		{
			if (mid > max1) max1 = mid;
			start = mid + 1;
		}
		else
		{
			end = mid - 1;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> c;

	long long int a;
	for (int i = 0; i < n; i++)
	{
		cin >> a;
		vec.push_back(a);
	}

	sort(vec.begin(), vec.end());

	// binary search
	binary_search();

	cout << max1;

	return 0;
}
