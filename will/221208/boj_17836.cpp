#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int ROWMAX, COLMAX, T, gotSord;
int dR[4] = {-1, 1, 0, 0};
int dC[4] = {0, 0, -1, 1};
struct POS { int r, c; } Sord, Night, Queen;
vector<vector<int>> Map, Vst;

int bfs(int sord){
    Night = {0, 0};
    Queen = {ROWMAX - 1, COLMAX - 1};

    queue<POS> q;
    q.push(Night);
    Vst[Night.r][Night.c] = 0;

    while(!q.empty()){
        POS now = q.front();
        q.pop();

        if (Map[now.r][now.c] == 2 and sord){
            gotSord = 1;
        }

        if (sord == 1 && Map[now.r][now.c] == 2){
            return Vst[now.r][now.c];
        }

        for (int i = 0; i < 4; i++){
            POS next = {now.r + dR[i], now.c + dC[i]};
            if (next.r < 0 || next.r >= ROWMAX) continue;
            if (next.c < 0 || next.c >= COLMAX) continue;
            if (Vst[next.r][next.c] != -1) continue;
            if (Map[next.r][next.c] == 1) continue;

            Vst[next.r][next.c] = Vst[now.r][now.c] + 1;
            q.push(next);
        }
    }

    return Vst[Queen.r][Queen.c];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(), cout.tie();

    freopen("../SampleInput/input.txt", "r", stdin);

    cin >> ROWMAX >> COLMAX >> T;
    Map.resize(ROWMAX, vector<int>(COLMAX, 0));
    Vst.resize(ROWMAX, vector<int>(COLMAX, -1));
    for (int r = 0; r < ROWMAX; r++){
        for (int c = 0; c < COLMAX; c++){
            cin >> Map[r][c];
            if (Map[r][c] == 2){
                Sord = {r, c};
            }
        }
    }    

    // without sord
    int dist1 = bfs(0);
    for (int r = 0; r < ROWMAX; r++){
        for (int c = 0; c < COLMAX; c++){
            Vst[r][c] = -1;
        }
    }

    // with sord
    int dist2 = bfs(1);
    if (gotSord) {
        dist2 += abs(Queen.r - Sord.r) + abs(Queen.c - Sord.c);
    }
    
    int ans = 0;
    if (dist1 == - 1 and dist2 == -1){
        cout << "Fail\n";
        return 0;
    }
    else if (dist1 == -1 and dist2 != -1){
        ans = dist2;
    }
    else if (dist1 != -1 and dist2 == -1){
        ans = dist1;
    }
    else if (dist1 != -1 and dist2 != -1){
        ans = min(dist1, dist2);
    }

    if (ans <= T) cout << ans << '\n';
    else cout << "Fail\n";

    Map.clear(), Vst.clear();
    return 0;
}
/*
?????????: dist1, dist2 ??? ????????? ????????????,
sord??? ????????? ???'???' abs??? ???????????????????????? ????????? abs??? ????????????
?????? ?????? ???????????? abs??? ????????? minValue??? ????????? ???????????? ?????? ??????

??????: gotSord flag??? ?????? ?????? ????????? ??? true??? ???????????? 
flag??? true ?????? abs ??? ???????????? ????????? ??????
*/

