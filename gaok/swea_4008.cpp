#include <iostream>
#include<vector>
using namespace std;
 
int n;
int opp[4];
int number[13];
 
int len = 0;
 
int minRes = 2134567890;
int maxRes = -2134567890;
int calc(int a, int b, int op) {
 
    if (op == 0) return a + b;
    if (op == 1) return a - b;
    if (op == 2) return a * b;
    if (op == 3) return a / b;
 
}
 
void dfs(int level, int res) {
 
    if (level == n) {
        if (maxRes < res) maxRes = res;
        if (minRes > res) minRes = res;
        return;
    }
 
    for (int i = 0; i < 4; i++) {
        if (opp[i] == 0) continue;
        opp[i] -= 1;
        dfs(level + 1, calc(res, number[level], i));
        opp[i] += 1;
    }
}
 
void init() {
    minRes = 2134567890;
    maxRes = -2134567890;
    len = 0;
}
 
int main() {
 
    int t;
    cin >> t;
 
    for (int testcase = 0; testcase < t; testcase++) {
         
        cin >> n;
 
        for (int i = 0; i < 4; i++) {
            cin >> opp[i];
            len += opp[i];
        }
 
        for (int i = 0; i < n; i++) {
            cin >> number[i];
        }
 
        dfs(1,number[0]);
        cout << "#"<<testcase+1<<" " <<abs(maxRes - minRes) << "\n";
 
        init();
    }
 
    return 0;
}
