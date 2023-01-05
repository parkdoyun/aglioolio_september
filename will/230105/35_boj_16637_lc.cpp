#include <iostream>
#include <vector>
using namespace std;

struct Var{ int num; char op; };

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(), cout.tie();

    freopen("../SampleInput/input.txt", "r", stdin);

    int n, maxAns;
    string s;
    cin >> n >> s;

    vector<Var> variables;    
    for (int i = 0; i < n; i++){
        if ((i % 2)){
            variables.push_back({0, s[i]});
        }
        else{
            variables.push_back({s[i] - '0', '0'});
        }
    }

    // m : 연산자 수
    // 연산자 수를 기준으로 비트마스크 진행
    maxAns = -2134567890;
    int m = (n - 1) / 2;
    for (int i = 0; i < (1 << m); i++){
        bool ok = true;
        for (int j = 0; j < m - 1; j++){
            // 연속된 연산자 2개를 선택하는 경우 -> 제외
            if ((i & (1 << j)) && (i & (1 << (j + 1)))){ ok = false; }
        }
        if (!ok){ continue; }

        // 연산자 기준으로 계산 -> temp 갱신
        vector<Var> temp(variables);
        for (int j = 0; j < m; j++){
            if ((i & (1 << j))){
                int k = 2 * j + 1;
                if (variables[k].op == '+'){
                    temp[k - 1].num += temp[k + 1].num;
                }
                else if(variables[k].op == '-'){
                    temp[k - 1].num -= temp[k + 1].num;
                }
                else if(variables[k].op == '*'){
                    temp[k - 1].num *= temp[k + 1].num;
                }
                temp[k].op = '+';
                temp[k + 1].num = 0;
            }
        }
        
        int res = temp[0].num;
        for (int l = 0; l < m; l++){
            int k = 2 * l + 1;
            if (temp[k].op == '+'){
                res += temp[k + 1].num;
            }
            else if (temp[k].op == '-'){
                res -= temp[k + 1].num;
            }
            else if (temp[k].op == '*'){
                res *= temp[k + 1].num;
            }
        }

        if (maxAns < res){ maxAns = res; }
    }

    cout << maxAns << '\n';

    return 0;
}
/*
1차 시도 : 또 무지성 dfs 로 접근 시도
         -> 그러다 안되겠다 싶어서 강의 들음
2차 시도 : 강의를 듣고 1차 비트마스크 파악
3차 시도 : 왜맞틀 시전 -> 알고보니 maxAns 초기값을 -2e9 로 설정안함
         -> 수의 범위가 -2e9 ~ 2e9 이므로, 이를 고려한 최솟값이어야함
*/