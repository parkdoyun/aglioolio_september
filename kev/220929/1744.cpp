#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
using ll = long long;

int main(){
    priority_queue<int> positives; // 큰게 먼저
    priority_queue<int, vector<int>, greater<int>> negatives; // 작은게 먼저
    
    int N; cin >> N;
    for(int i = 0; i < N; i++){
        int n; cin >> n;
        if(n > 0) positives.push(n);
        else negatives.push(n);
    }
    
    ll sum = 0;
    while(positives.size() > 1){
        int first = positives.top(); positives.pop();
        int second = positives.top(); positives.pop();
        int g = first + second;
        if(g < first * second) g = first * second;
        sum += g;
    }
    if(!positives.empty()) sum += positives.top();
    
    while(negatives.size() > 1){
        int first = negatives.top(); negatives.pop();
        int second = negatives.top(); negatives.pop();
        sum += first * second;
    }
    if(!negatives.empty()) sum += negatives.top();

    cout << sum << '\n';

    return 0;
}