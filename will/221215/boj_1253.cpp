#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> Values;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(), cout.tie();

    freopen("../SampleInput/input.txt", "r", stdin);

    int n;
    cin >> n;
    Values.resize(n, 0);
    for (int i = 0; i < n; i++){
        cin >> Values[i];
    }
    sort(Values.begin(), Values.end());

    int cnt = 0;
    for (int i = 0; i < n; i++){
        vector<int> checkV;
        for (int j = 0; j < n; j++){
            if (i != j) { checkV.push_back(Values[j]); }
        }

        int l = 0;
        int r = checkV.size() - 1;
        while( l < r ){
            if (checkV[l] + checkV[r] == Values[i]){
                cout << checkV[l] << " + " << checkV[r] << " = " << Values[i] <<'\n';
                cnt++;
                break;
            }

            else if (checkV[l] + checkV[r] < Values[i]){
                l++;
            }
            else {
                r--;
            }
        }

    }

    cout << cnt << '\n';
    Values.clear();
    return 0;
}
/*
첫 시도: brute force 로 접근
       - 2중 for 문을 돌면서 서로 다른 index 2개를 합쳐서 target 과 비교
       - N: 2000 이라, 괜찮다고 생각할 수 있지만, 주어진 수에 대해 2중 for 문
         -> 최종적으로 3 중 for 문을 돌게 된다
         -> O(N ** 3) -> 시간 초과

두번째 시도: two_pointer
       - 현재 value 를 제외한 value 를 새로운 vector 에 저장
       - 그리고, sort
       - left, right 를 활용해 부분 합 비교
*/