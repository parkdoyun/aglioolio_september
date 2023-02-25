#include <iostream>
#include <queue>

using namespace std;

// 백준 17837 - 새로운 게임 2
// simulation
// 골드 2

int n, k;
int color[13][13];
int board[13][13][11];
int y_mov[] = { 0, 0, -1, 1 };
int x_mov[] = { 1, -1, 0, 0 };
int res = 100000;
int tmp_path[11];

struct node
{
    int y;
    int x;
    int dir;
};
vector<node> vec;

int chk()
{
    int cnt;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cnt = 0;
            for (int r = 0; r < 11; r++)
            {
                if (board[i][j][r] != 0) cnt++;
                else break;
            }
            if (cnt >= 4) return 1;
        }
    }
    return -1;
}

void mov()
{
    int now_time = 0;
    int ty, tx;

    while (now_time <= 1000)
    {
        // 확인
        for (int i = 1; i <= k; i++)
        {
            ty = vec[i].y + y_mov[vec[i].dir];
            tx = vec[i].x + x_mov[vec[i].dir];
            if (ty >= n || ty < 0 || tx >= n || tx < 0 ||
                color[ty][tx] == 2) // 파란색
            {
                if (vec[i].dir == 1 || vec[i].dir == 3) vec[i].dir--;
                else vec[i].dir++;

                ty = vec[i].y + y_mov[vec[i].dir];
                tx = vec[i].x + x_mov[vec[i].dir];

                if (ty >= n || ty < 0 || tx >= n || tx < 0 ||
                    color[ty][tx] == 2) // 이동하려는 칸 파란색인 경우 이동 X
                {
                    ;
                }
                else // 이동
                {
                    int red_idx = 0;
                    for (int j = 0; j < 11; j++)
                    {
                        if (board[vec[i].y][vec[i].x][j] == i) // 이 뒤로 전부 옮기기
                        {
                            int idx = j;
                            for (int k = 0; k < 11; k++)
                            {
                                if (board[vec[i].y][vec[i].x][idx] != 0)
                                {
                                    tmp_path[k] = board[vec[i].y][vec[i].x][idx];
                                }
                                else
                                {
                                    tmp_path[k] = -1;
                                    break;
                                }
                                board[vec[i].y][vec[i].x][idx] = 0;
                                idx++;
                                red_idx = k;
                            }
                            break;
                        }
                    }

                    // 붙이기 -> 빨간색일 경우 반대로 붙이기
                    if (color[ty][tx] == 1)
                    {
                        for (int j = 0; j < 11; j++)
                        {
                            if (board[ty][tx][j] == 0)
                            {
                                int idx = j;
                                for (int k = red_idx; k >= 0; k--)
                                {
                                    board[ty][tx][idx] = tmp_path[k];
                                    vec[tmp_path[k]].y = ty;
                                    vec[tmp_path[k]].x = tx;
                                    idx++;
                                }
                                break;
                            }
                        }
                    }
                    else // 흰색
                    {
                        for (int j = 0; j < 11; j++)
                        {
                            if (board[ty][tx][j] == 0)
                            {
                                int idx = j;
                                for (int k = 0; k < 11; k++)
                                {
                                    if (tmp_path[k] == -1) break;
                                    board[ty][tx][idx] = tmp_path[k];
                                    vec[tmp_path[k]].y = ty;
                                    vec[tmp_path[k]].x = tx;
                                    idx++;
                                }
                                break;
                            }
                        }
                    }
               
                }
            }
            else if (color[ty][tx] == 0) // 흰색
            {
                for (int j = 0; j < 11; j++)
                {
                    if (board[vec[i].y][vec[i].x][j] == i) // 이 뒤로 전부 옮기기
                    {
                        int idx = j;
                        for (int k = 0; k < 11; k++)
                        {
                            if (board[vec[i].y][vec[i].x][idx] != 0)
                            {
                                tmp_path[k] = board[vec[i].y][vec[i].x][idx];
                            }
                            else
                            {
                                tmp_path[k] = -1;
                                break;
                            }
                            board[vec[i].y][vec[i].x][idx] = 0;
                            idx++;
                        }
                        break;
                    }
                }

                // 붙이기
                for (int j = 0; j < 11; j++)
                {
                    if (board[ty][tx][j] == 0)
                    {
                        int idx = j;
                        for (int k = 0; k < 11; k++)
                        {
                            if (tmp_path[k] == -1) break;
                            board[ty][tx][idx] = tmp_path[k];
                            vec[tmp_path[k]].y = ty;
                            vec[tmp_path[k]].x = tx;
                            idx++;
                        }
                        break;
                    }
                }
            }
            else // 1, 빨간색
            {
                int red_idx = 0;
                for (int j = 0; j < 11; j++)
                {
                    if (board[vec[i].y][vec[i].x][j] == i) // 이 뒤로 전부 옮기기
                    {
                        int idx = j;
                        for (int k = 0; k < 11; k++)
                        {
                            if (board[vec[i].y][vec[i].x][idx] != 0)
                            {
                                tmp_path[k] = board[vec[i].y][vec[i].x][idx];
                                red_idx = k;
                                board[vec[i].y][vec[i].x][idx] = 0;
                            }
                            else break;
                            idx++;
                        }
                        break;
                    }
                }

                // 붙이기
                for (int j = 0; j < 11; j++)
                {
                    if (board[ty][tx][j] == 0)
                    {
                        int idx = j;
                        for (int k = red_idx; k >= 0; k--)
                        {
                            board[ty][tx][idx] = tmp_path[k];
                            vec[tmp_path[k]].y = ty;
                            vec[tmp_path[k]].x = tx;
                            idx++;
                        }
                        break;
                    }
                }
            }
            if (chk() == 1) // 확인
            {
                res = now_time + 1;
                return;
            }
        }
        now_time++;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    vec.resize(k + 1);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) cin >> color[i][j];
    }

    for (int i = 1; i <= k; i++)
    {
        cin >> vec[i].y >> vec[i].x >> vec[i].dir;
        vec[i].y--;
        vec[i].x--;
        vec[i].dir--;
        for (int j = 0; j < 11; j++)
        {
            if (board[vec[i].y][vec[i].x][j] == 0)
            {
                board[vec[i].y][vec[i].x][j] = i;
                break;
            }
        }
    }

    mov();

    if (res == 100000) cout << -1;
    else cout << res;

    return 0;
}