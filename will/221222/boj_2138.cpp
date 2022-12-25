#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

bool check(string a, string b){
	for (int i = 0; i < a.size(); i++){
		if (a[i] != b[i]){ return false; }
    }
	return true;
}
int main(void){
    ios_base::sync_with_stdio(false);

    freopen("../SampleInput/input.txt", "r", stdin);

	int n;
	cin >> n;
	string a, b;

	cin >> a >> b;
	string c = a;
	a[0] = (a[0] == '1') ? '0' : '1';
	a[1] = (a[1] == '1') ? '0' : '1';
	int cnt1 = 0, cnt2 = 0;
	cnt1++;

	for (int i = 1; i < n; i++){
		if (a[i - 1] != b[i - 1]){
			
            a[i - 1] = (a[i - 1] == '1') ? '0' : '1';
			a[i]     = (a[i]     == '1') ? '0' : '1';

			if (i + 1 < n){ 
                a[i + 1] = a[i+1] == '1' ? '0' : '1'; 
            }
			cnt1++;
		}
	}
	
	for (int i = 1; i < n; i++){
		if (c[i - 1] != b[i - 1]){
            
            c[i - 1] = (c[i - 1] == '1') ? '0' : '1';
			c[i]     = (c[i]     == '1') ? '0' : '1';

			if (i + 1 < n){ 
                c[i + 1] = c[i + 1] == '1' ? '0' : '1'; 
            }
			cnt2++;
		}
	}
	
	int ans = 2e9;
	if (check(a, b)){ ans = min(cnt1, ans); }
	if (check(c, b)){ ans = min(cnt2, ans); }

	if (ans == 2e9){ cout << -1; }
	else{ cout << ans; }

    return 0;
}