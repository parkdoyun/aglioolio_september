#include <iostream>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

// 백준 9328 - 열쇠
// BFS
// 골드 1

// 1. 우선 막히는 부분이 있다면 구역을 그룹핑 해놓는다(BFS) + 막히는 문 표시 (큐 삽입), 구역 다 확인했다면(전부 chk) 다음 턴
// 2. 구역 그룹핑 하면서 얻은 열쇠들로 구역 한번씩 돌면서 막히는 문 있으면 큐에서 꺼내서 연다 
// 2.2 다시 막히는 부분 있다면 배열 삽입, 구역 다 확인했다면 그냥 다음 턴
// 이렇게 해서 큐 비거나 아니면 더 이상 열 수 있는 구역 없을 때까지 계속 큐 돈다
// 큐에는 어떻게 넣어놓느냐? 구역 좌표 (정확히는 문 좌표) + 문 글자

int y_mov[] = { -1, 1, 0, 0 };
int x_mov[] = { 0, 0, -1, 1 };
int chk[101][101];
char board[101][101];
int key[26];
int h, w;
int files = 0;

struct node
{
	int y;
	int x;
	int flag;
	int key = 0;
};
bool operator<(node n1, node n2)
{
	if (n1.flag < n2.flag) return true;
	else if (n1.flag == -1 && n2.flag == -1 && key[n1.key] == 0 && key[n2.key] > 0) return true;
	return false;
}
bool cmp(node n1, node n2)
{
	if (key[n1.key] > 0 && key[n2.key] == 0) return true;
	return false;
}
vector<node> pq;
priority_queue<node> pq2;

// 처음 BFS
void BFS()
{
	int ty, tx;

	while (!pq2.empty())
	{
		node tmp = pq2.top();
		pq2.pop();

		if (chk[tmp.y][tmp.x] == 1 || chk[tmp.y][tmp.x] == 2) continue;
		chk[tmp.y][tmp.x] = 1;
		
		// 열쇠면 추가
		if (board[tmp.y][tmp.x] >= 'a' && board[tmp.y][tmp.x] <= 'z')
		{
			key[(int)(board[tmp.y][tmp.x] - 'a')]++;
		}
		// 문인데 못 열면 -> pq에 넣기
		else if (board[tmp.y][tmp.x] >= 'A' && board[tmp.y][tmp.x] <= 'Z')
		{
			if (key[(int)(board[tmp.y][tmp.x] - 'A')] == 0)
			{
				pq.push_back({ tmp.y, tmp.x, -1, (int)(board[tmp.y][tmp.x] - 'A') });
				chk[tmp.y][tmp.x] = 2;
				continue;
			}
		}
		// 문서면 files++;
		else if (board[tmp.y][tmp.x] == '$') files++;

		for (int i = 0; i < 4; i++)
		{
			ty = tmp.y + y_mov[i];
			tx = tmp.x + x_mov[i];

			if (ty >= 0 && ty < h && tx >= 0 && tx < w &&
				chk[ty][tx] == 0 && board[ty][tx] != '*')
			{
				if (board[ty][tx] == '.' || board[ty][tx] == '$') pq2.push({ ty, tx, 0 });
				else if (board[ty][tx] >= 'a' && board[ty][tx] <= 'z') pq2.push({ ty, tx, 1 });
				else  pq2.push({ ty, tx, -1, (int)(board[ty][tx] - 'A') });
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin >> T;
	string keys;
	for (int tc = 1; tc <= T; tc++)
	{
		// 입력
		while (!pq.empty()) pq.pop_back();

		files = 0;
		for (int i = 0; i < 26; i++) key[i] = 0;

		cin >> h >> w;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				cin >> board[i][j];
				chk[i][j] = 0;
			}
		}
		cin >> keys;
		if (keys != "0")
		{
			for (int i = 0; i < keys.length(); i++)
			{
				key[(int)(keys[i] - 'a')]++;
			}
		}

		// 가로
		for (int i = 0; i < w; i++)
		{
			if (board[0][i] == '*') ;
			else if (board[0][i] == '.' || board[0][i] == '$') pq2.push({ 0, i, 0 });
			else if (board[0][i] >= 'A' || board[0][i] <= 'Z') pq2.push({ 0, i, -1 });
			else pq2.push({ 0, i, 1 });

			if (board[h - 1][i] == '*') continue;
			else if (board[h - 1][i] == '.' || board[h - 1][i] == '$') pq2.push({ h - 1, i, 0 });
			else if (board[h - 1][i] >= 'A' || board[h - 1][i] <= 'Z') pq2.push({ h - 1, i, -1 });
			else pq2.push({ h - 1, i, 1 });
		}

		// 세로
		for (int i = 1; i < h - 1; i++)
		{
			if (board[i][0] == '*') ;
			else if (board[i][0] == '.' || board[i][0] == '$') pq2.push({ i, 0, 0 });
			else if (board[i][0] >= 'A' || board[i][0] <= 'Z') pq2.push({ i, 0, -1 });
			else pq2.push({ i, 0, 1 });

			if (board[i][w - 1] == '*') continue;
			else if (board[i][w - 1] == '.' || board[i][w - 1] == '$') pq2.push({ i, w - 1, 0 });
			else if (board[i][w - 1] >= 'A' || board[i][w - 1] <= 'Z') pq2.push({ i, w - 1, -1 });
			else pq2.push({ i, w - 1, 1 });
		}

		BFS();
		int pq_s = 0;
		while (!pq.empty())
		{
			// pq에 있던 애들에서 BFS -> pq2로
			// pq2에서 문 연 적 없다면 break
			pq_s = pq.size();
			sort(pq.begin(), pq.end(), cmp);

			// 문 열 수 없다면 다시 pq에 집어넣기
			// 문 열 수 있다면 BFS 진행
			for (int i = 0; i < pq.size();)
			{
				if (key[pq[i].key] == 0)
				{
					i++;
					continue;
				}
				chk[pq[i].y][pq[i].x] = 0;
				pq2.push({ pq[i].y, pq[i].x });
				BFS();
				// 삭제
				pq.erase(pq.begin() + i);
			}

			// 한번 다 검사한 후 크기 같으면 out (변한 것 없으므로)
			if (pq_s == pq.size()) break;
		}
		cout << files << '\n';

	}
	return 0;
}