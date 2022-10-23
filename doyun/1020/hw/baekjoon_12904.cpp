#include <iostream>
#include <string>
using namespace std;

// 백준 12904 - A와 B
// greedy
// 골드 5

// t에서 s를 만들 수 있는지 보면 됨
// ABBA -> ABB -> BA -> B (된다)

int main()
{
	string s, t;
	cin >> s >> t;

	string tmp; // 뒤집기용
	while (s.size() < t.size())
	{
		if (t[t.size() - 1] == 'A')
		{
			t.pop_back();
		}
		else
		{
			t.pop_back();
			tmp = "";
			for (int i = t.size() - 1; i >= 0; i--)
			{
				tmp += t[i];
			}
			t = tmp;
		}
	}
	if (t == s) cout << 1;
	else cout << 0;

	return 0;
}