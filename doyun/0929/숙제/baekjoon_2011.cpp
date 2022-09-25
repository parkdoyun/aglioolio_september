#include <iostream>
#include <string>

using namespace std;

// 백준 2011 - 암호코드
// DP
// 골드 5

// 251 => 2511
// 11은 가능한 수
// 2511 가짓수 = 251의 기존 가짓수 + (251 가짓수 중 마지막 1 혼자 있는 가짓수)
// 101, 201처럼 중간에 0 있는 애들 처리해야 함 

// 1301 => 이런 애들 13 01 이렇게 취급 안 하는지 확인 => 05, 06 이런 거 취급 X


long long DP[5001];

// 맨 끝에 혼자인 애들 갯수 => 얘네만 기존 DP 값에서 더해줘야 함
long long arr[5001];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// 입력 없을 때
	if (cin.eof())
	{
		cout << 0;
		return 0;
	}

	string pw;
	cin >> pw;

	// 기저 조건
	DP[0] = 1;
	arr[0] = 1;
	
	// 잘못된 암호
	if (pw[0] == '0')
	{
		cout << 0;
		return 0;
	}

	string tmp;
	for (int i = 1; i < pw.size(); i++)
	{
		tmp = pw.substr(i - 1, 2);
		if (tmp == "00") // 잘못된 암호 (00)
		{
			cout << 0;
			return 0;
		}

		if (pw[i] == '0')
		{
			if (tmp < "30")
			{
				if (i == pw.size() - 1) // 붙일 수 있는 애들만 붙임
				{
					DP[i] = arr[i - 1];
					arr[i] = 0;
				}
				else
				{
					DP[i] = arr[i - 1];
					arr[i] = DP[i - 1];
				}
			}
			else if(i == pw.size()-1) // 마지막이 연결 X (130) => 잘못된 암호
			{
				cout << 0;
				return 0;
			}
			else // 다 띄어서 보냄
			{
				/*
				DP[i] = DP[i - 1];
				arr[i] = DP[i - 1];
				*/
				cout << 0;
				return 0;
			}
			continue;
		}
		else if (pw[i - 1] == '0')
		{
			DP[i] = DP[i - 1];
			arr[i] = DP[i - 1];
			continue;
		}
		
		if (tmp < "27" && tmp >= "01") // 값이 27보다 작으면 => stoi() 느리기 때문에 빠르게 하는 법 찾기
		{
			DP[i] = (DP[i - 1] + arr[i - 1]) % 1000000;
			// 또 혼자인 애들 체크 => 얘도 나머지 연산

			// arr[i-1]이 더 커버릴 수도 있다
			// arr[i] = (DP[i] - arr[i - 1]) % 1000000; // 이렇게 쓰면 DP[i]가 먼저 나머지 연산을 한 후라 arr[i-1]보다 작아지게 되어 음수가 나올 수 있다 => 오답
			arr[i] = (DP[i - 1] + arr[i-1] - arr[i - 1]) % 1000000; // 수정
		}
		else // tmp >= "27" && tmp <= "99"
		{
			DP[i] = DP[i - 1];
			arr[i] = DP[i - 1]; // 전부 하나씩 남음
		}
		//cout << DP[i] << ' ' << arr[i] <<  endl;
	}

	cout << DP[pw.size() - 1] % 1000000;


	return 0;
}