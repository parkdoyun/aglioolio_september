#include <iostream>

using namespace std;

// 백준 1068 - 트리
// DFS
// 골드 5

// 1. 리프 노드부터 재귀 돌면서 root[a]가 del_n라면 재귀 멈추고 그 밑까지 전부 지운다
// 2. 그 후에 전부 돌면서 자식 있는 애들 체크
// 3. root[i]가 -2 (삭제된 노드) 아니고 자식 없는 애들 (리프 노드) 출력

int n, del_n;

int root[51]; // -2이면 지운 노드
int hasChild[51]; // 자식 있으면 1 표시

int searchRoot(int a)
{
	if (root[a] == del_n) // 부모가 삭제됐다면
	{
		root[a] = -2; // 삭제
		return -1;
	}
	else if (root[a] == -2) // 이미 삭제됐다면
	{
		return -1;
	}
	else if (root[a] == a) // 무사하게 루트로 왔다면 다시 내려감
	{
		return 1;
	}

	int res = searchRoot(root[a]);
	if (res == -1)
	{
		root[a] = -2; // 나 삭제
		return -1;
	}
	else if (res == 1) return 1;
}

// 부모 노드 체크
void chkChild(int a) // -2이면 애초에 들어오지 못 하게
{
	if (hasChild[a] == 1) return; // 이미 체크됐다면 재귀 종료
	hasChild[a] = 1; // 자식 있다고 표시
	if (root[a] == a) return; // 루트라면 재귀 종료
	chkChild(root[a]); // 부모 확인
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;

	for (int i = 0; i < n; i++)
	{
		cin >> root[i];
		if (root[i] == -1) root[i] = i;
	}
	cin >> del_n;
	root[del_n] = -2; // 노드 삭제
	for (int i = 0; i < n; i++)
	{
		searchRoot(i); // 트리 탐색
	}

	// 부모 노드 체크
	for (int i = 0; i < n; i++)
	{
		if (root[i] == -2) continue;
		chkChild(root[i]);
	}

	int total_cnt = 0; // 루트만 남게 되었을 때 예외 처리
	int cnt = 0;
	for (int i = 0; i < n; i++)
	{
		if (root[i] != -2) total_cnt++;
		if (root[i] == -2 || hasChild[i] == 1) continue; // 부모 노드이거나 삭제된 노드라면 pass
		cnt++;
	}

	// 결과 출력
	if (total_cnt == 1) cout << 1;
	else cout << cnt;

	return 0;
}