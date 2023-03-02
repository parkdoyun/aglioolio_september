#include <iostream>
using namespace std;

int N, M;
int Root[500000];

int Find(int now){
	if (Root[now] == now){ return now; }
	return Find(Root[now]);
}

void Union(int a, int b){
	int rootA = Find(a);
	int rootB = Find(b);
	Root[rootB] = rootA;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(), cout.tie();

	freopen("../SampleInput/input.txt", "r", stdin);

	cin >> N >> M;

	for (int i = 0; i < N; i++){
		Root[i] = i;
	}
	
	for (int j = 1; j <= M; j++){
		int from, to;
		cin >> from >> to;
		
		if (Find(from) == Find(to)){
			cout << j << '\n';
			return 0;
		}
		else{ Union(from, to); }
	}
	cout << 0 << '\n';
	return 0;
}

/*
Union-Find 대표 예제
1차 시도: Union-Find 인지 몰랐음
2차 시도: Union-Find 임을 파악 => 복습 후 코드 작성
3차 시도: 2차에서 Union의 Root[pB] 를 Root[B] 로 작성
	  	-> 이렇게 되면 대표 노드가 교체가 안되고 자식 노드가 교체 되어버림
		-> 1-2-3, 4-5 에서 Union(3, 5)를 하면, Root[5] = 1 이 되고
		   Root[4] 는 1이 안되어서 그룹핑이 제대로 되지 않는다
*/