#include <iostream>
#include <string>
using namespace std;

int LCS[4001][4001]; // LCS는 i==0 or j==0일때 0으로 padding 주기
int main() {

	string str1;
	string str2;

	cin >> str1;
	cin >> str2;

	int maxLen = 0;
	for (int i = 1; i <= str1.length(); i++) {
		for (int j = 1; j <= str2.length(); j++) {
			if (str1[i-1] == str2[j-1]) {
				LCS[i][j] = LCS[i - 1][j - 1] + 1;
				if (maxLen < LCS[i][j]) maxLen = LCS[i][j];
			}
		}
	}

	cout << maxLen;

	return 0;
}

