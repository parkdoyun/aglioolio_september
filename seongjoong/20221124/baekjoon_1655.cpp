#include <iostream>
#include <queue>
using namespace std;

int N;
priority_queue<int, vector<int>, greater<int>> pq1; // MINHEAP (큰 수들)
priority_queue<int> pq2; // MAXHEAP (작은 수들)

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++) {
        int n;
        cin >> n;
        
        if (pq1.size() == pq2.size())
            pq2.push(n);
        else
            pq1.push(n);

        if (!pq1.empty() && !pq2.empty() && pq1.top() < pq2.top()) {
            int temp1 = pq1.top();
            pq1.pop();
            int temp2 = pq2.top();
            pq2.pop();

            pq1.push(temp2);
            pq2.push(temp1);
        }

        cout << pq2.top() << '\n';
    }

    return 0;
}
