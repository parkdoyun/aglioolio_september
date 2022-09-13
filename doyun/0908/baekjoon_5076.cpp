#include <iostream>
#include <string>
#include <stack>

using namespace std;

// 백준 5076 - Web Pages
// 문자열
// 골드 4

stack<string> st;

int main()
{
	string s, tmp_s;
	while (true)
	{
		getline(cin, s);
		while (!st.empty()) st.pop();

		if (s == "#") break;

		int idx = 0;
		int chk = -1;
		while (idx < s.length())
		{			
			while (s[idx] != '<' && idx < s.length()) idx++;
			if (idx == s.length()) break;

			idx++;
			if (s[idx] == '/') // st에서 빼기
			{
				idx++;
				if (st.size() == 0) // 빼야 되는데 스택이 비었을 때
				{
					chk = 1;
					break;
				}
				tmp_s = "";
				while (s[idx] != '>' && idx < s.length())
				{
					tmp_s += s[idx];
					idx++;
					
				}
				if (st.top() == tmp_s) st.pop();
				else // 스택의 top이랑 괄호 안 문자열 다를 때
				{
					chk = 1;
					break;
				}
			}
			else // 문자열 등록, '/'로 끝나면 pass
			{
				tmp_s = "";
				while (s[idx] != '>' && s[idx] != ' ' && idx < s.length())
				{
					tmp_s += s[idx];
					idx++;
				}
				if (s[idx + 1] != '/') // st에 넣기
				{
					st.push(tmp_s);
					idx++;
				}
			}
			idx++;

		}
		if (chk == -1 && st.size() == 0) cout << "legal\n";
		else cout << "illegal\n";
	}
	return 0;
}