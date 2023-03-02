/* Category : DFS, BruteForce
 * solving time : > 5h   
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define INF 9999999999

using namespace std;


int N;
int boundary[5] = { 0, };
int arr[15][5] = { 0, };
string temp2 = "";
//bool flag;

vector<string> ansarr;
int answer = INF;

/*
void init() {
	memset(boundary, 0, sizeof(int));
	for (int i = 0; i < 15; i++) {
		memset(arr[i], 0, sizeof(int));
	}
	//flag = true;
	ansarr.clear();
	answer = INF;
}
*/
void input() {
	cin >> N;
	for (int i = 0; i < 4; i++) {
		cin >> boundary[i];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> arr[i][j];
		}
	}
}

int visited[15] = { 0, };
vector<int> path;

void calculate(vector<int> a) {
	int total[5] = { 0, };
	bool flag = true;
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < a.size(); i++) {
			total[j] += arr[a.at(i)][j];
		}
		if (total[j] < boundary[j]) {
			flag = false;
			break;
		}
	}

	if (!flag)
		return;

	if (total[4] <= answer) {
		if (total[4] == answer) {
			string temp1 = "";

			for (int i = 0; i < a.size(); i++)
				if (i == a.size() - 1)
					temp1 += to_string(a.at(i)+1);
				else
					temp1 += to_string(a.at(i)+1) + " ";
			

			if (temp1 < temp2) {
				temp2 = temp1;
				//ansarr.clear();
				ansarr.push_back(temp1);
				//copy(a.begin(), a.end(), back_inserter(ansarr));

			}
		}
		else {
			answer = total[4];
			string t = "";
			for (int i = 0; i < a.size(); i++) {
				if (i == a.size() - 1)
					t += to_string(a.at(i)+1);
				else
					t += to_string(a.at(i)+1)+" ";
			}
			
			temp2 = t;
			ansarr.clear();
			ansarr.push_back(t);
			//copy(a.begin(), a.end(), back_inserter(ansarr));
		}
	}





}
void dfs(int depth, int idx, int r) {
	if (depth >= r) {
		calculate(path);
		return;
	}

	for (int i = idx; i < N; i++) {
		if (visited[i] == 1)
			continue;

		visited[i] = 1;
		path.push_back(i);
		dfs(depth + 1, i + 1, r);
		path.pop_back();
		visited[i] = 0;
	}
}
int main() {
	//init();
	input();

	for (int i = 1; i <= N; i++) {
		dfs(0, 0, i);
	}

	if (answer == INF || ansarr.size() == 0) {
		cout << -1;
	}
	else {

		sort(ansarr.begin(), ansarr.end());
		cout << answer << '\n';
		cout << ansarr.at(0);
		//for (int i = 0; i < ansarr.size(); i++) {
		//	cout << ansarr.at(i) + 1 << " ";
		//}
	}
}
