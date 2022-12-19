#include <iostream>
#include <algorithm>
using namespace std;

// 스위치를 누르는 순서는 상관 X -> 결과가 항상 같음
// --> 각각의 스위치를 누르냐, 안 누르냐 선택

// ***
// i번 전구 -> i-1, i, i+1번 스위치의 영향을 받음
// => i번 전구를 토글하려면, i번이 아닌 i+1번 스위치 누르기!

// 1) 0번째 스위치를 누르지 않고 시작
// 2) 0번째 스위치를 누르고 시작

int N;
string str;
string tar;
string temp;
int ans = -1;

void toggle(int idx) {
    if (temp[idx] == '0')
        temp[idx] = '1';
    else
        temp[idx] = '0';
}

void simul(int idx, int cnt) {
    if (idx == N) {
        // i번까지 왔다면, 0 ~ i-2까지는 이미 같다고 확인하고 넘어옴
        // -> i-1번째만 같은지 확인하면 됨!
        if (temp[idx - 1] == tar[idx - 1]) {
            ans = cnt;
        }
        return;
    }
    
    if (temp[idx - 1] == tar[idx - 1])
        simul(idx + 1, cnt);
    else {
        toggle(idx - 1);
        toggle(idx);
        if (idx != N - 1)
            toggle(idx + 1);
        simul(idx + 1, cnt + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    cin >> str >> tar;

    // 1) 누르지 않고 시작
    temp = str;
    simul(1, 0);

    // 2) 누르고 시작
    // -> 순서 상관 없으므로, 안 누르고 시작해서 가능하면 무조건 최소가 됨.
    if (ans == -1) {
        temp = str;
        toggle(0);
        toggle(1);
        simul(1, 1);
    }

    cout << ans;

    return 0;
}
