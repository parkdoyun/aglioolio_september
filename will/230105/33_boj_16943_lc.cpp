#include <iostream>
#include <string>
using namespace std;

string A, B, C;
int Ans;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(), cout.tie();

    freopen("../SampleInput/input.txt", "r", stdin);

    cin >> A >> B;
    Ans = -1;

    sort(A.begin(), A.end());
    do{
        if (A[0] != '0' and stoi(A) < stoi(B) and Ans < stoi(A)){
            Ans = stoi(A);
        }
    }while(next_permutation(A.begin(), A.end()));

    cout << Ans << '\n';

    return 0;
}

/*
1차 시도 : for 문으로 구현하려고 했지만,
         구현하다보니, A가 몇 자리의 정수라는 말이 없음
         4중 for 로 구현 못 할 가능성이 있음 -> dfs

2차 시도 : dfs 에서 test case 에러가 뜸
3차 시도 : 해설을 보았고, do-while + next_permutation 으로 맞춤
          -> 모든 순열은 sort + do-while + next_permutation 좋음
*/