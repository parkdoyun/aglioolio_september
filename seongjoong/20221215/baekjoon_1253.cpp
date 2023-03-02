#include <iostream>
#include <algorithm>
using namespace std;

int N;
int arr[2000];
int ans;

void search(int tar, int idx) {
    int left = 0;
    int right = N - 1;

    // 자신을 더하는 경우 제외
    if (left == idx)
        left++;
    if (right == idx)
        right--;

    while (left < right) {
        int temp = arr[left] + arr[right];
        if (temp == tar) {
            ans++;
            return;
        }
        else if (temp < tar) {
            left++;
            if (left == idx)
                left++;
        }
        else {
            right--;
            if (right == idx)
                right--;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    sort(arr, arr + N);

    for (int i = 0; i < N; i++)
        search(arr[i], i);

    cout << ans;

    return 0;
}
