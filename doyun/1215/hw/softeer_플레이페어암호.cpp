#include <iostream>
#include <string>

using namespace std;

// softeer - 플레이페어 암호
// 구현
// 별3

// XX일 때 무조건 ZZ로 바꾸는 게 아니라 옆에 걸로 바꾼다 => 이것때문에 틀림

int alphabet[27];
char board[6][6];

string cipher(string tmp)
{
	int y1, x1, y2, x2;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (board[i][j] == tmp[0])
			{
				y1 = i;
				x1 = j;
			}
			else if (board[i][j] == tmp[1])
			{
				y2 = i;
				x2 = j;
			}
		}
	}

	// 변경
	if (tmp == "XX") // **이 때 주의!!! 무조건 ZZ로 바꾸는 게 아니라 옆에 걸로 바꾼다**
	{
		tmp[0] = board[y1][(x1 + 1) % 5];
		tmp[1] = board[y1][(x1 + 1) % 5];
		return tmp;
	}
	else if (y1 == y2) // 오른쪽으로 한칸 이동
	{
		tmp[0] = board[y1][(x1 + 1) % 5];
		tmp[1] = board[y1][(x2 + 1) % 5];
	}
	else if (x1 == x2) // 밑으로
	{
		tmp[0] = board[(y1 + 1) % 5][x1];
		tmp[1] = board[(y2 + 1) % 5][x1];
	}
	else // X자
	{
		tmp[0] = board[y1][x2];
		tmp[1] = board[y2][x1];
	}
	
	return tmp;
}

int main(int argv, char **argc)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	string msg, key;
	cin >> msg >> key;

	// J는 사용 안 함
	alphabet[(int)('J' - 'A')] = 1;

	// key 채우기
	int idx = 0;
	int alpha_idx = 0;
	int k_len = key.length();
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (idx < k_len)
			{
				board[i][j] = key[idx];
				alphabet[(int)(key[idx] - 'A')] = 1;
				idx++;
				while (idx < k_len)
				{
					if (alphabet[(int)(key[idx] - 'A')] == 0) break;
					idx++;
				}
			}
			else // 나머지 알파벳 순서대로 채우기
			{
				while (alpha_idx < 26)
				{
					if (alphabet[alpha_idx] == 0)
					{
						board[i][j] = (char)('A' + alpha_idx);
						alphabet[alpha_idx] = 1;
						alpha_idx++;
						break;
					}
					alpha_idx++;
				}
			}
		}	
	}

	// 두개씩 떨어뜨리기
	idx = 0;
	int msg_len = msg.length();
	string tmp_len;
	string res = "";
	while (idx < msg_len)
	{
		tmp_len = "";
		tmp_len += msg[idx];
		idx++;
		if (idx == msg_len) // 마지막 한글자였을 때
		{
			tmp_len += "X";
		}
		else if (msg[idx] == msg[idx - 1]) // 똑같을 때
		{
			if (tmp_len == "X") tmp_len += "Q";
			else tmp_len += "X";
		}
		else
		{
			tmp_len += msg[idx];
			idx++;
		}

		// 암호화
		tmp_len = cipher(tmp_len);

		res += tmp_len;
	}

	cout << res;

	return 0;
}