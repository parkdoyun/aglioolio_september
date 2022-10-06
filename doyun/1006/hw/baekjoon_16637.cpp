#include <iostream>

using namespace std;

// 백준 16637 - 괄호 추가하기
// 골드 4
// 완전탐색
// dfs, backtracking

// 가능한 괄호 전부 넣어보고 식 계산 -> 최댓값

// 예제 6 : 1-9-(1-9)-(1-9)-(1-9)-(1-9) = 24

int op[11]; // 연산자 + : 1, - : 2, * : 3
int num[11]; // 숫자
// backtracking은 연산자마다 한다
// 바로 붙은 연산자 두개에 괄호 칠 수 x
// 최대 괄호 갯수 => 연산자 홀수 : (연산자 갯수 / 2) + 1, 연산자 짝수 : 연산자 갯수 / 2
int path[11]; // backtracking 배열 (괄호)
int n;
int max1;
int op_idx = 0; // 연산자 갯수
int num_idx = 0; // 숫자 갯수

int cal() // 현재 수식 계산
{
	int res = num[0];
	int idx = 0;
	while (idx < op_idx)
	{
		if (idx + 1 < op_idx && path[idx + 1] == 1)
		{
			int tmp = 0;
			// 다음 것부터 계산
			if (op[idx + 1] == 1) // +
			{
				tmp = num[idx + 1] + num[idx + 2];
			}
			else if (op[idx + 1] == 2) // -
			{
				tmp = num[idx + 1] - num[idx + 2];
			}
			else // *
			{
				tmp = num[idx + 1] * num[idx + 2];
			}

			if (op[idx] == 1) // +
			{
				res = res + tmp;
			}
			else if (op[idx] == 2) // -
			{
				res = res - tmp;
			}
			else // *
			{
				res = res * tmp;
			}

			idx += 2;
			
		}
		else
		{
			if (op[idx] == 1) // +
			{
				res = res + num[idx + 1];
			}
			else if (op[idx] == 2) // -
			{
				res = res - num[idx + 1];
			}
			else // *
			{
				res = res * num[idx + 1];
			}
			idx++;
		}
	}

	return res;
}

void DFS(int lv, int h) // h : 개수
{
	int res = cal(); // 식 계산
	if (res > max1) max1 = res;

	if (lv == h)
	{
		return;
	}

	for (int i = 0; i < op_idx; i++)
	{
		// 괄호 띄어서 씌워야 함
		if (path[i] == 1) continue;
		else if (i - 1 > 0 && path[i - 1] == 1) continue;
		path[i] = 1;
		DFS(lv + 1, h);
		path[i] = 0;
	}
}

int main()
{
	cin >> n;
	char c;
	for (int i = 0; i < n; i++)
	{
		cin >> c;
		if (i % 2 == 0) // 정수
		{
			num[num_idx] = (int)(c - '0');
			num_idx++;
		}
		else // 기호
		{
			if (c == '+')
			{
				op[op_idx] = 1;
			}
			else if (c == '-')
			{
				op[op_idx] = 2;
			}
			else // *
			{
				op[op_idx] = 3;
			}
			op_idx++;
		}
	}

	// 괄호 없는 식을 기본값으로
	max1 = cal();
	
	for (int i = 0; i < op_idx; i++)
	{
		if (path[i] == 1) continue;
		else if (i - 1 > 0 && path[i - 1] == 1) continue;
		path[i] = 1;
		DFS(1, (op_idx / 2 + 1));
		path[i] = 0;
	}

	cout << max1;

	return 0;
}