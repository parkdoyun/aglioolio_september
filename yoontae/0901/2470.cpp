#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

int N;
int liquid[100001];

void input() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> liquid[i];
}

void solution() {

	sort(liquid, liquid + N);

	int neutral = 2134567890;
	int acid = 0;
	int base = 0;

	int a = 0;
	int b = N - 1;

	while (a < b) {

		int mixed = liquid[a] + liquid[b];

		if (mixed > 0) {
			if (abs(mixed) < abs(neutral)) {
				neutral = mixed;
				acid = liquid[a];
				base = liquid[b];
			}

			b--;
		}

		else if (mixed <= 0) {
			if (abs(mixed) < abs(neutral)) {
				neutral = mixed;
				acid = liquid[a];
				base = liquid[b];
			}

			a++;
		}

		else {
			neutral = mixed;
			acid = liquid[a];
			base = liquid[b];
			break;
		}
	}

	cout << acid << " " << base;
}

int main() {
	input();
	solution();

	return 0;
}