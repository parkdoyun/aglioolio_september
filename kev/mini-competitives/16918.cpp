#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int R, C, N;
vector<vector<char>> board;
vector<vector<int>> blow_time;

const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, -1, 0, 1};
void blow(int cur)
{
    for (int i = 0; i < R; ++i)
    {
        for (int j = 0; j < C; ++j)
        {
            if (board[i][j] == '.')
                continue;

            if (blow_time[i][j] != cur)
                continue;

            board[i][j] = '.';
            for (int k = 0; k < 4; ++k)
            {
                int ny = i + dy[k];
                int nx = j + dx[k];

                if (ny < 0 || nx < 0 || ny >= R || nx >= C)
                    continue;

                if(blow_time[ny][nx] == cur) continue;

                board[ny][nx] = '.';
            }
        }
    }
}

void sap(int cur)
{
    for (int i = 0; i < R; ++i)
    {
        for (int j = 0; j < C; ++j)
        {
            if (board[i][j] != '.')
                continue;

            board[i][j] = 'O';
            blow_time[i][j] = cur + 3;
        }
    }
}

void print_board()
{
    for (const auto &row : board)
    {
        for (const auto &cell : row)
        {
            cout << cell;
        }
        cout << "\n";
    }
}

void solve()
{
    cin >> R >> C >> N;

    board.resize(R);
    for (int i = 0; i < R; ++i)
        board[i].resize(C);

    blow_time.resize(R);
    for (int i = 0; i < R; ++i)
        blow_time[i].resize(C);

    for (int i = 0; i < R; ++i)
    {
        for (int j = 0; j < C; ++j)
        {
            char initial_state;
            cin >> initial_state;
            board[i][j] = initial_state;
            blow_time[i][j] = 3;
        }
    }

    int n = 2;
    while(n <= N)
    {
        if (n % 2 == 0)
            sap(n);
        else
            blow(n);
        n++;
    }

    print_board();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}