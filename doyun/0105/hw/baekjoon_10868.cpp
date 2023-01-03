#include <iostream>
#include <algorithm>

using namespace std;

// 백준 10868 - 최솟값
// segment tree
// 골드 1

// 최솟값

int n, m;
long long int arr[100001];
long long int tree[400001];

long long int treeInit(int start, int end, int idx)
{
	// leaf
	if (start == end)
	{
		tree[idx] = arr[start];
		return tree[idx];
	}

	int mid = (start + end) / 2;
	tree[idx] = min(treeInit(start, mid, idx * 2), treeInit(mid + 1, end, idx * 2 + 1));
	return tree[idx];
}

// 구간 최솟값 구하기
long long int traversal(int start, int end, int idx, int left, int right)
{
	// 범위 밖
	if (left > end || right < start) return 1000000001;
	
	// 범위 안
	if (left <= start && right >= end)
	{
		return tree[idx];
	}

	int mid = (start + end) / 2;
	return min(traversal(start, mid, idx * 2, left, right), traversal(mid + 1, end, idx * 2 + 1, left, right));
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);


	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> arr[i];

	treeInit(1, n, 1);

	int a, b;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b;
		cout << traversal(1, n, 1, a, b) << '\n';
	}


	return 0;
}
