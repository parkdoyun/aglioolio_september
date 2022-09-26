#include <iostream>
#include <string>

using namespace std;

// 백준 16120 - PPAP
// string
// 골드 4

// PPAP -> PP와 A 만나면 상쇄
// 마지막 PPAP 남아야 함 -> P 하나 남고 바로 전에 A면 ok

int main()
{
	string s;
	cin >> s;

	int cnt = 0;

	// 예외 처리 (P 하나 입력 받았을 때)
	if (s == "P")
	{
		cout << "PPAP";
		return 0;
	}

	for (int i = 0; i < s.length() - 1; i++)
	{
		if (s[i] == 'P') {
			cnt++;
		}
		else // A
		{
			if (cnt >= 2) cnt -= 2;
			else
			{
				cout << "NP";
				return 0;
			}
		}
	}

	if (cnt == 0 && s[s.length() - 1] == 'P' && s[s.length() - 2] == 'A')
	{
		cout << "PPAP";
	}
	else cout << "NP";

	return 0;
}