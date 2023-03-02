#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 백준 15811 - 복면산?!
// brute-force
// 골드 4

// 나온 문자별로 모든 조합 다 해보고 안 되면 out
// 맨 뒤부터 맞추고 시작하면 backtracking 가짓수 줄어드므로 맞추고 시작

// out of range (해결)
// 시간초과 -> string 연산 너무 오래 걸림 -> 배열로 바꾸자(해결)

string str1, str2, str3;
vector<char> alpha; // alphabet
int path[11];
int use[10]; // 해당 수 쓰는지 쓰지 않는지
int vec_s;
int total_flag = 0;
long long int s1[19];
long long int s2[19];
long long int s3[19];
int s1_len, s2_len, s3_len;

// cal() 여기서 out of range -> int 범위 넘어가기 때문
int cal()
{	
	for (int i = 0; i < s1_len; i++)
	{
		for (int j = 0; j < alpha.size(); j++)
		{
			if (alpha[j] == str1[i])
			{
				s1[i] = path[j];
				break;
			}
		}
	}

	long long int a = 0;
	long long int ten = 1;

	for (int i = s1_len - 1; i >= 0; i--)
	{
		a = (long long int)(a + (long long int)(ten * s1[i]));
		ten = (long long int)(ten * 10);
	}

	for (int i = 0; i < str2.length(); i++)
	{
		for (int j = 0; j < alpha.size(); j++)
		{
			if (alpha[j] == str2[i])
			{
				s2[i] = path[j];
				break;
			}
		}
	}

	long long int b = 0;
	ten = 1;
	for (int i = s2_len - 1; i >= 0; i--)
	{
		b = (long long int)(b + (long long int)(ten * s2[i]));
		ten = (long long int)(ten * 10);
	}

	for (int i = 0; i < str3.length(); i++)
	{
		for (int j = 0; j < alpha.size(); j++)
		{
			if (alpha[j] == str3[i])
			{
				s3[i] = path[j];
				break;
			}
		}
	}
	long long int c = 0;
	ten = 1;
	for (int i = s3_len - 1; i >= 0; i--)
	{
		c = (long long int)(c + (long long int)(ten * s3[i]));
		ten = (long long int)(ten * 10);
	}

	if ((long long int)(a + b) == c) return 1;
	return -1;
}

void backtracking(int lv)
{
	if (total_flag == 1) return;
	if (lv == vec_s)
	{
		// 계산 되는지 확인
		if (cal() == 1) total_flag = 1;
		return;
	}

	for (int i = 0; i <= 9; i++)
	{
		if (use[i] == 0)
		{
			use[i] = 1;
			path[lv] = i;
			backtracking(lv + 1);
			use[i] = 0;
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> str1 >> str2 >> str3;

	// 시간 줄이기 위해
	// string 시간 오래 걸림
	s1_len = str1.length();
	s2_len = str2.length();
	s3_len = str3.length();

	// 알파벳 배열에 넣기
	for (int i = 0; i < str1.length(); i++)
	{
		int flag = 0;
		for (int j = 0; j < alpha.size(); j++)
		{
			if (alpha[j] == str1[i])
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0) alpha.push_back(str1[i]);
	}
	for (int i = 0; i < str2.length(); i++)
	{
		int flag = 0;
		for (int j = 0; j < alpha.size(); j++)
		{
			if (alpha[j] == str2[i])
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0) alpha.push_back(str2[i]);
	}
	for (int i = 0; i < str3.length(); i++)
	{
		int flag = 0;
		for (int j = 0; j < alpha.size(); j++)
		{
			if (alpha[j] == str3[i])
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0) alpha.push_back(str3[i]);
	}
	vec_s = alpha.size();

	
	for (int i = 0; i <= 9; i++)
	{
		if (total_flag == 1) break;
		path[0] = i;
		use[i] = 1;
		backtracking(1);
		use[i] = 0;
	}
	

	if (total_flag == 1) cout << "YES";
	else cout << "NO";

	return 0;
}