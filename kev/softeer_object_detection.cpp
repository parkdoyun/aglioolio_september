#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>

using namespace std;

int N, K;

struct Coord{
	int y;
	int x;
};

struct Bounds{
	Coord min;
	Coord max;
};

vector<vector<Coord>> color_points;

Bounds get_bounds(const vector<Coord>& points){
	Bounds bounds = {points[0], points[0]};
	
	Coord& min = bounds.min;
	Coord& max = bounds.max;

	for(int i = 1; i < points.size(); ++i){
		const Coord& pos = points[i];
		
		if(pos.y < min.y) min.y = pos.y;
		if(pos.x < min.x) min.x = pos.x;
		if(pos.y > max.y) max.y = pos.y;
		if(pos.x > max.x) max.x = pos.x;
	}
	return bounds;
}

int get_area(const Bounds& bounds){
	return (bounds.max.y - bounds.min.y) * (bounds.max.x - bounds.min.x);
}

int min_area = INT_MAX;
void dfs(int color, vector<Coord>& points){
	if(color == K + 1){
		Bounds bounds = get_bounds(points);
		int area = get_area(bounds);
		min_area = min(area, min_area);
		return;
	}

	if(!points.empty()){
		Bounds cur_bounds = get_bounds(points);
		int cur_area = get_area(cur_bounds);
		if(cur_area >= min_area) return;
	}

	for(int i = 0; i < color_points[color].size(); ++i){
		points.push_back(color_points[color][i]);
		dfs(color + 1, points);
		points.pop_back();
	}
}

void solve(){
	cin >> N >> K;

	color_points.resize(K + 1);

	for(int i = 0; i < N; ++i){
		Coord pos; 
		cin >> pos.x >> pos.y;

		int color;
		cin >> color;

		color_points[color].push_back(pos);
	}

	vector<Coord> points;
	dfs(1, points);

	cout << min_area << '\n';
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	solve();

	return 0;
}