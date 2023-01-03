#include<iostream>
#include<algorithm>
using namespace std;

int N, M;
long long arr[100001];
long long mintree[100000 * 4 + 1];
long long maxtree[100000 * 4 + 1];

long long min_init(int node, int start, int end) {
	if (start == end)
		return mintree[node] = arr[start];
	int mid = (start + end) / 2;
	return mintree[node] = min(min_init(2 * node, start, mid), min_init(2 * node + 1, mid + 1, end));
}
long long max_init(int node, int start, int end) {
	if (start == end)
		return maxtree[node] = arr[start];
	int mid = (start + end) / 2;
	return maxtree[node] = max(max_init(2 * node, start, mid), max_init(2 * node + 1, mid + 1, end));
}
long long getMin(int node, int start, int end, int left, int right) {
	if (end < left || right < start)
		return 1e9;
	if (left <= start && end <= right)
		return mintree[node];
	int mid = (start + end) / 2;
	return min(getMin(2 * node, start, mid, left, right), getMin(2 * node + 1, mid + 1, end, left, right));
}

long long getMax(int node, int start, int end, int left, int right) {
	if (end < left || right < start)
		return -1e9;
	if (left <= start && end <= right)
		return maxtree[node];
	int mid = (start + end) / 2;
	return max(getMax(2 * node, start, mid, left, right), getMax(2 * node + 1, mid + 1, end, left, right));
}

void input() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	min_init(1, 0, N - 1);
	max_init(1, 0, N - 1);

	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		cout << getMin(1, 0, N - 1, a-1, b-1) << " " << getMax(1, 0, N - 1, a-1, b-1) << '\n';
	}
}
int main() {
	input();
}
