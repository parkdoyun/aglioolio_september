#include iostream
#include string
#include stack

using namespace std;

string str;

void solution()
{
	int a = 0;
	int b = 0;
	int c = 0;

	stackstring s;

	while (true)
	{
		a = str.find(, c);
		b = str.find(, c);

		if (a == -1  b == -1)
			break;

		string tag = str.substr(a + 1, b - a - 1);

		int d = 0;

		d = tag.find(, 0);

		string attributes;

		if (d != -1)
		{
			attributes = tag.substr(d + 1, (int)(tag.size()) - (d + 1));
			tag = tag.substr(0, d);
		}


		if (attributes == )
		{
			int de = 1;
		}
		else if (tag[0] != '')
		{
			s.push(tag);
		}
		else
		{
			if (s.empty())
			{
				cout  illegal  n;
				return;
			}

			tag.erase(0, 1);
			if (tag == s.top())
			{
				s.pop();
			}
			else
			{
				cout  illegal  n;
				return;
			};
		}

		c = b + 1;
	}

	if (s.empty())
		cout  legal  n;
	else
		cout  illegal  n;
}

int main()
{
	while (true)
	{
		getline(cin, str);

		if (str == #)
			break;

		solution();
	}

	return 0;
}