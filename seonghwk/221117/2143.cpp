#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int T, n, m;
vector<int> A;
vector<int> B;

void input() {
  cin >> T;
  cin >> n;
  A = vector<int>(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
  }
  cin >> m;
  B = vector<int>(m + 1, 0);
  for (int i = 1; i <= m; i++) {
    cin >> B[i];
  }
}

vector<int> getPsum(vector<int> src) {
  vector<int> ret(src.size(), 0);
  for (int i = 1; i < src.size(); i++) {
    ret[i] = ret[i - 1] + src[i];
  }
  return ret;
}

vector<int> getComb(vector<int> psum) {
  vector<int> ret(psum.size() * (psum.size() - 1) / 2, 0);
  int idx = 0;
  for (int i = 0; i < psum.size(); i++) {
    for (int j = i + 1; j < psum.size(); j++) {
      ret[idx++] = psum[j] - psum[i];
    }
  }
  return ret;
}

void solution() {
  vector<int> pA = getPsum(A);
  vector<int> pB = getPsum(B);

  vector<int> combA = getComb(pA);
  vector<int> combB = getComb(pB);

  sort(combA.begin(), combA.end(), less<int>());
  sort(combB.begin(), combB.end(), greater<int>());

  ll cnt = 0;
  int ptrA = 0;
  int ptrB = 0;
  int sum, startA, startB;
  while (true) {
    if (ptrA == combA.size() || ptrB == combB.size()) break;

    sum = combA[ptrA] + combB[ptrB];
    if (sum < T) {
      ptrA++;
      continue;
    }
    if (sum > T) {
      ptrB++;
      continue;
    }
    startA = ptrA;
    startB = ptrB;
    while (ptrA != combA.size() && combA[startA] == combA[ptrA]) ptrA++;
    while (ptrB != combB.size() && combB[startB] == combB[ptrB]) ptrB++;
    cnt += (ll)(ptrA - startA) * (ll)(ptrB - startB);
  }
  cout << cnt << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  input();
  solution();

  return 0;
}