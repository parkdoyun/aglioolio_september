#include <iostream>
#include<string>
#include <vector>
#include <algorithm>
#include<bitset>

using namespace std;

long long T;
int n, m;

long long A[1000];
long long B[1000];
long long sumA[1001];
long long sumB[1001];

/*
void init() {
	memset(A, 0, sizeof(int));
	memset(B, 0, sizeof(int));
	memset(sumA, 0, sizeof(int));
	memset(sumB, 0, sizeof(int));
}
*/
void input() {
	cin >>T>> n;
	for (int i = 0; i < n; i++) {
		cin >> A[i];
	}
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> B[i];
	}
}

void getPsum() {
	for (int i = 1; i <= n; i++) {
		sumA[i] = sumA[i - 1] + A[i - 1];
	}
	for (int i = 1; i <= m; i++) {
		sumB[i] = sumB[i - 1] + B[i - 1];
	}
}

vector<long long> pscombinations(int n, int r, long long arr[]) {
	vector <long long> ret;

	int vec[1001] = { 0, };
	for (int i = 0; i < r; i++) {
		vec[i] = 1;
	}
	do {
		long long a, b;
		bool f = false;
		for (int i = 0; i <= n; i++) {
			if (vec[i] == 1) {
				if (!f) {
					a = arr[i];
					f = true;
				}
				else if (f) {
					b = arr[i];
				}
			}
		}
		//cout << abs(a - b) << " ";
		ret.push_back(b - a);
	} while (prev_permutation(vec, vec + n + 1));

	return ret;
}

void solution() {

	vector<long long> combPartSumA = pscombinations(n, 2, sumA);
	//cout << endl;
	vector<long long> combPartSumB = pscombinations(m, 2, sumB);
	//여기까지 O(10^7+4000)
	
	//n, m 둘 중 값이 작은 부분합 배열을 기준으로 한다.(A,B중 길이가 작은것이 기준)
	//예를 들어 m < n이라면, 
	//B부분합의 모든 경우를 담은 배열 combPartSumB의 각 원소를 하나하나씩 
	//combPartSumA의 원소 중에서 합이 T를 만족하는 경우를 이진탐색 하면서 더한다.
	//combPartSumA 원소 중에서 합이 T를 만족하는 동일한 원소가 A에 여러개 존재할 수 도 있으므로
	// lower bound , upper bound 사용

	long long answer = 0;
	if (n < m) {
		sort(combPartSumB.begin(), combPartSumB.end());
		//여기까지 O(2*10^7+4000)

		for (int i = 0; i < combPartSumA.size(); i++) {
		
			long long lb = lower_bound(combPartSumB.begin(), combPartSumB.end(), T - combPartSumA.at(i))-combPartSumB.begin();
			long long ub = upper_bound(combPartSumB.begin(), combPartSumB.end(), T - combPartSumA.at(i))-combPartSumB.begin();
			answer += (ub - lb);

		}
		cout << answer;
	}
	else {
		sort(combPartSumA.begin(), combPartSumA.end());
		//여기까지 O(2*10^7+4000)

		for (int i = 0; i < combPartSumB.size(); i++) {

			long long lb = lower_bound(combPartSumA.begin(), combPartSumA.end(), T - combPartSumB.at(i)) - combPartSumA.begin();
			long long ub = upper_bound(combPartSumA.begin(), combPartSumA.end(), T - combPartSumB.at(i)) - combPartSumA.begin();
			answer += (ub - lb);

		}
		cout << answer;
	}
	
	//O(10^7log(10^7))= O(7*10^7)
	//O(9*10^7)

}



int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
		input();
		getPsum();
		solution();

}
