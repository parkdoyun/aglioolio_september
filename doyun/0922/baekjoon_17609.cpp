#include <iostream>
#include <string>

using namespace std;

// 백준 17609 - 회문
// 문자열
// 골드 5

// 건너뛰어야 하는 애들 카운트 & 건너뜀
// 0 개 : 회문
// 1 개 : 유사회문
// 그 이상 : 2 출력

// 처음 빼면 회문 되는 것도 체크
// 처음 빼면 회문 되거나, 맨 뒤 빼면 회문 되는 거 체크 위해
// 회문 체크 함수 두개 사용해서 값 적은 거 출력

int chkPal(string s)
{
	int start = 0;
	int end = s.length() - 1;

	int cnt = 0;
	while (start < end)
	{
		if (s[start] == s[end])
		{
			start++;
			end--;
		}
		else
		{
			cnt++;
			// 누가 같은지 확인
			if (s[start + 1] == s[end])
			{
				start++;
			}
			else if (s[start] == s[end - 1])
			{
				end--;
			}
			else start++;

		}
		if (cnt >= 2) return 2;
	}
	
	return cnt;
}

int chkPal2(string s)
{
	int start = 0;
	int end = s.length() - 1;

	int cnt = 0;
	while (start < end)
	{
		if (s[start] == s[end])
		{
			start++;
			end--;
		}
		else
		{
			cnt++;
			// 누가 같은지 확인
			if (s[start] == s[end - 1])
			{
				end--;
			}
			else if (s[start + 1] == s[end])
			{
				start++;
			}
			else start++;

		}
		if (cnt >= 2) return 2;
	}

	return cnt;
}


int main()
{
	string s;

	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> s;
		int res1 = chkPal(s);
		int res2 = chkPal2(s);
		if (res1 < res2) cout << res1 << '\n';
		else cout << res2 << '\n';
	}
	return 0;
}