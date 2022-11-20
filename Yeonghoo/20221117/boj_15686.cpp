#include <iostream>
#include <vector>
#include <algorithm>

#define INF 2123456789;
using namespace std;

struct Coord {
	int y, x;
};

int N, M;
int MAP[50][50] = { 0, };
int answer = INF;

vector<Coord> chichouse;
vector<Coord> house;
void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 1)
				house.push_back({ i, j });
			else if (MAP[i][j] == 2)
				chichouse.push_back({ i, j });
		}
}

int findDist(vector<Coord> h, vector<Coord> c) {
	int chicDist = 0;
	for (auto i : h) {
		int minDist = INF;
		for (auto j : c) {
			int dist = abs(i.y - j.y) + abs(i.x - j.x);
			if (dist < minDist)
				minDist = dist;
		}
		chicDist += minDist;
	}
	return chicDist;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
	input();

	vector<int> vec;
	for (int i = 0; i < chichouse.size(); i++) {
		vec.push_back(0);
	}

	for (int i = 0; i < M; i++) {
		vec.at(i) = 1;
	}
    
	do {
			vector<Coord> select;
			for (int ch = 0; ch < chichouse.size(); ch++) {
				if (vec.at(ch) == 1) {
					select.push_back(chichouse.at(ch));
				}
			}
			int chickendist = findDist(house, select);
			if (chickendist < answer)
				answer = chickendist;
		} while (prev_permutation(vec.begin(), vec.end()));
	cout << answer;
}
