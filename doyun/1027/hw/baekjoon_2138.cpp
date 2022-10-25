#include <iostream>
#include <string>

using namespace std;

// 백준 2138 - 전구와 스위치
// greedy
// 골드 5

// 전구를 첫번째부터 켤건지 아닌지
// 두개 다 해보고 둘다 되면 최소값 비교
// 다 안 되면 -1
// 경우의 수 1) 첫번째부터 켜기 -> 무조건 켜기 / 다를 때만 켜기
//           2) 두번째부터 켜기 -> 무조건 켜기 / 다를 때만 켜기 => 총 4가지 비교

// 현재 내가 다르면 바꾸자

int main()
{
	string input, output, tmp;
	int n;
	cin >> n >> output >> input;
	int min = 999999999;

	// 첫번째부터 켜는 것 비교
	int cnt = 0;
	tmp = output;
	
	if (tmp[0] != input[0]) // 확인하고 켜기
	{
		cnt++;
		tmp[0] = (tmp[0] == '0' ? '1' : '0');
		tmp[1] = (tmp[1] == '0' ? '1' : '0');
	}

	for (int i = 1; i < n - 1; i++)
	{
		if (tmp[i - 1] != input[i - 1])
		{
			cnt++;
			tmp[i-1] = (tmp[i-1] == '0' ? '1' : '0');
			tmp[i] = (tmp[i] == '0' ? '1' : '0');
			tmp[i + 1] = (tmp[i + 1] == '0' ? '1' : '0');
		}
	}
	if (tmp[n - 2] != input[n - 2])
	{
		cnt++;
		tmp[n - 2] = (tmp[n - 2] == '0' ? '1' : '0');
		tmp[n - 1] = (tmp[n - 1] == '0' ? '1' : '0');
	}
	if (tmp == input)
	{
		if (cnt < min) min = cnt;
	}

	// 무조건 켜기
	cnt = 0;
	tmp = output;

	
	cnt++;
	tmp[0] = (tmp[0] == '0' ? '1' : '0');
	tmp[1] = (tmp[1] == '0' ? '1' : '0');
	

	for (int i = 1; i < n - 1; i++)
	{
		if (tmp[i - 1] != input[i - 1])
		{
			cnt++;
			tmp[i - 1] = (tmp[i - 1] == '0' ? '1' : '0');
			tmp[i] = (tmp[i] == '0' ? '1' : '0');
			tmp[i + 1] = (tmp[i + 1] == '0' ? '1' : '0');
		}
	}
	if (tmp[n - 2] != input[n - 2])
	{
		cnt++;
		tmp[n - 2] = (tmp[n - 2] == '0' ? '1' : '0');
		tmp[n - 1] = (tmp[n - 1] == '0' ? '1' : '0');
	}
	if (tmp == input)
	{
		if (cnt < min) min = cnt;
	}


	// 두번째부터 켜는 것 비교
	cnt = 0;
	tmp = output;
	if (tmp[0] != input[0]) // 확인 후 켜기
	{
		cnt++;
		tmp[0] = (tmp[0] == '0' ? '1' : '0');
		tmp[1] = (tmp[1] == '0' ? '1' : '0');
		tmp[2] = (tmp[2] == '0' ? '1' : '0');
	}

	for (int i = 2; i < n - 1; i++)
	{
		if (tmp[i - 1] != input[i - 1])
		{
			cnt++;
			tmp[i - 1] = (tmp[i - 1] == '0' ? '1' : '0');
			tmp[i] = (tmp[i] == '0' ? '1' : '0');
			tmp[i + 1] = (tmp[i + 1] == '0' ? '1' : '0');
		}
	}
	if (tmp[n - 2] != input[n - 2])
	{
		cnt++;
		tmp[n - 2] = (tmp[n - 2] == '0' ? '1' : '0');
		tmp[n - 1] = (tmp[n - 1] == '0' ? '1' : '0');
	}
	if (tmp == input)
	{
		if (cnt < min) min = cnt;
	}

	// 두번째부터 켜기
	// 무조건 켜기
	cnt = 0;
	tmp = output;
	
	cnt++;
	tmp[0] = (tmp[0] == '0' ? '1' : '0');
	tmp[1] = (tmp[1] == '0' ? '1' : '0');
	tmp[2] = (tmp[2] == '0' ? '1' : '0');
	

	for (int i = 2; i < n - 1; i++)
	{
		if (tmp[i - 1] != input[i - 1])
		{
			cnt++;
			tmp[i - 1] = (tmp[i - 1] == '0' ? '1' : '0');
			tmp[i] = (tmp[i] == '0' ? '1' : '0');
			tmp[i + 1] = (tmp[i + 1] == '0' ? '1' : '0');
		}
	}
	if (tmp[n - 2] != input[n - 2])
	{
		cnt++;
		tmp[n - 2] = (tmp[n - 2] == '0' ? '1' : '0');
		tmp[n - 1] = (tmp[n - 1] == '0' ? '1' : '0');
	}
	if (tmp == input)
	{
		if (cnt < min) min = cnt;
	}

	if (input == output) cout << 0;
	else if (min == 999999999) cout << -1;
	else cout << min;

	return 0;
}