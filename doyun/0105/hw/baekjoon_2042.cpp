#include <iostream>

using namespace std;

// 백준 2042 - 구간 합 구하기
// segment-tree
// 골드 1

int n, m, k;
long long int arr[1000001];
long long int tree[4000001];

long long int treeInit(int start, int end, int idx)
{
	// leaf면 배열 값 트리에 넣기
	if (start == end)
	{
		tree[idx] = arr[start];
		return tree[idx];
	}

	// 트리 재귀
	int mid = (start + end) / 2;
	tree[idx] = (long long int)(treeInit(start, mid, idx * 2) + treeInit(mid + 1, end, idx * 2 + 1));
	return tree[idx];
}

long long int traversal(int start, int end, int idx, int left, int right)
{
	// 구간 밖인 경우 (더하면 안 되므로 0 return)
	if (left > end || right < start) return 0;

	// 구간 안인 경우
	if (left <= start && right >= end)
	{
		return tree[idx];
	}
	// 그렇지 않은 경우 합 구하기
	int mid = (start + end) / 2;

	return (long long int)(traversal(start, mid, idx * 2, left, right) + traversal(mid + 1, end, idx * 2 + 1, left, right));
}

void Update(int start, int end, int idx, int mod_val, long long int val) // val : 모든 구간합들이 변경되어야 하는 값
{
	// 수정하려는 수가 구간 밖인 경우
	if (mod_val < start || mod_val > end) return;

	// 범위 안에 있으면 재귀로 들어가면서 다른 원소 갱신
	tree[idx] = (long long int)(tree[idx] + val);
	if (start == end) // **leaf일 경우 arr[start]도 변경해야 함!!!!***
	{
		arr[start] = (long long int)(arr[start] + val);
		return;
	}
	
	int mid = (start + end) / 2;
	Update(start, mid, idx * 2, mod_val, val);
	Update(mid + 1, end, idx * 2 + 1, mod_val, val);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}

	treeInit(1, n, 1);

	int a, b;
	long long int c;

	for (int i = 0; i < k + m; i++)
	{
		cin >> a >> b >> c;
		if (a == 1) // b번째 수를 c로 변경
		{
			Update(1, n, 1, b, (long long int)(c - arr[b]));
		}
		else // b부터 c까지 구간합 구하기
		{
			cout << (long long int)traversal(1, n, 1, b, c) << '\n';
		}
	}


	return 0;
}