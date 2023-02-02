#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// softeer 5차 기출 - 성적 평가
// simulation

int n;
long long int total_score[100001]; // 전체 점수 => **1000으로 잘못 봤음
long long int score[100001]; // 현재 점수
int order[100001]; // 등수

struct node
{
	long long int s; // score
	long long int n; // idx
};

bool cmp(node n1, node n2)
{
	if (n1.s > n2.s) return true;
	return false;
}

vector<node> vec;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long int now_order, now_score, same_cnt;
	cin >> n;
	vec.resize(n + 1);

	for (int tc = 0; tc < 3; tc++)
	{
		for (int i = 0; i < n; i++)
		{
			cin >> score[i];
			vec[i].s = score[i];
			vec[i].n = i;
			total_score[i] = (long long int)(total_score[i] + score[i]);
		}
		
		sort(vec.begin(), vec.begin() + n, cmp);

		now_order = 1; // 등수
		now_score = vec[0].s;
		same_cnt = 1; // 같은 사람 등수 처리
		order[vec[0].n] = now_order;

		for (int i = 1; i < n; i++)
		{
			if (vec[i].s != now_score)
			{
				now_score = vec[i].s;
				now_order += same_cnt;
				same_cnt = 1;
			}
			else same_cnt++;
			order[vec[i].n] = now_order;
		}

		// 결과 출력
		for (int i = 0; i < n; i++)
		{
			cout << order[i] << ' ';
		}
		cout << '\n';
	}

	// 전체 등수
	for (int i = 0; i < n; i++)
	{
		vec[i].s = total_score[i];
		vec[i].n = i;
	}
	sort(vec.begin(), vec.begin() + n, cmp);

	now_order = 1; // 등수
	now_score = vec[0].s;
	same_cnt = 1;
	order[vec[0].n] = now_order;

	for (int i = 1; i < n; i++)
	{
		if (vec[i].s != now_score)
		{
			now_score = vec[i].s;
			now_order += same_cnt;
			same_cnt = 1; // **빼먹지 말기
		}
		else same_cnt++;
		order[vec[i].n] = now_order;

	}

	for (int i = 0; i < n; i++)
	{
		cout << order[i] << ' ';
	}
	cout << '\n';

	return 0;
}