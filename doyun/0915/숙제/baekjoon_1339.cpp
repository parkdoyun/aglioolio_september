#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 백준 1339 - 단어 수학
// greedy, backtracking
// 골드 4

// 모든 경우의 수 다 돌리기
// 9 ~ 경우의 수만큼
// backtracking 후 모든 경우의 수
// 시간 너무 많이 걸린다 -> 시간 단축 방법 찾기
// 시간 단축 방법 1. stoi(), to_string() 같은 string 연산 제거
//                2. DAT를 하나 더 추가하여(value[]) 알파벳 -> 숫자 변환 시 단축

int max1 = 0;
int DAT[10];
int value[26]; // 알파벳 dat -> 시간 단축 위해 (일일이 alpha_vec 찾지 않도록)
int total_size; // 알파벳 총 몇개인지

vector<string> words;
struct node
{
	char ch;
	int num;
};
vector<node> alpha_vec; // 알파벳 dat

void DFS(int lv)
{
	if (lv == total_size)
	{
		// 계산
		int sum = 0;
		int tmp;
		int tens;
		for (int i = 0; i < words.size(); i++)
		{
			//string s = "";
			tens = 0;
			for (int j = 0; j < words[i].size(); j++)
			{
				tmp = value[(int)(words[i][j] - 'A')];
				tens = (tens * 10) + tmp;
				
				//s += to_string(tmp); // string 연산 시간 많이 듬
			}
			//sum += stoi(s);
			sum += tens;
		}
		if (sum > max1) max1 = sum;
		
		return;
	}

	for (int i = 0; i < total_size; i++)
	{
		// backtracking
		if (DAT[i] == 1) continue;
		DAT[i] = 1;
		alpha_vec[lv].num = 9 - i;
		value[(int)(alpha_vec[lv].ch - 'A')] = 9 - i;
		DFS(lv + 1);
		DAT[i] = 0;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;
	string s;
	for (int i = 0; i < n; i++)
	{
		cin >> s;
		words.push_back(s);
		for (int j = 0; j < s.length(); j++)
		{
			value[(int)(s[j] - 'A')] = 1;
		}
	}

	// alphabet
	for (int i = 0; i < 26; i++)
	{
		if (value[i] == 1)
		{
			alpha_vec.push_back({ (char)('A' + i), -1 });
		}
	}

	total_size = alpha_vec.size();

	
	for (int i = 0; i < total_size; i++)
	{
		// backtracking
		if (DAT[i] == 1) continue;
		DAT[i] = 1;
		alpha_vec[0].num = 9 - i;
		value[(int)(alpha_vec[0].ch - 'A')] = 9 - i;
		DFS(1);
		DAT[i] = 0;
	}
	
	
	
	cout << max1;

	return 0;
}