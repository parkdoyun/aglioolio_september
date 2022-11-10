#include <iostream>
#include <cmath>
using namespace std;

struct Point{
    int r;
    int c;
};


const int z[2][2] = {
    {0, 1},
    {2, 3}
};
/*
    quadrant
    1 2
    3 4
*/
int get_quad(int l, int r, int c){
    if(r < l / 2 && c < l / 2) return 0;
    if(r < l / 2 && c >= l / 2) return 1;
    if(r >= l / 2 && c < l / 2) return 2;
    return 3;
}

Point get_quad_start_point(int l, int quad){
    Point p;
    switch (quad)
    {
    case 0:
        p = {0, 0};
        break;
    case 1:
        p = {0, l / 2};
        break;
    case 2:
        p = {l / 2, 0};
        break;
    case 3:
        p = {l / 2, l / 2};
        break;
    default:
        break;
    }
    return p;
}

int get_order(int l, int r, int c){
    if(l == 2){
        return z[r][c];
    }

    int q = get_quad(l, r, c);
    Point i = get_quad_start_point(l, q);

    return q * pow((int)(l / 2), 2) + get_order(l / 2, r - i.r, c - i.c);
}

int main(){
    int n; cin >> n;
    int r; cin >> r;
    int c; cin >> c;
    
    int l = pow(2, n);
    int answer = get_order(l, r, c);
    cout << answer << '\n';
}