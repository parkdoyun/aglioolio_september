#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int samples[100000];

typedef struct __compound{
    int a;
    int b;
    int balance;
    int abs_sum;

    bool better_than(const struct __compound& other){
        if(abs(balance) < abs(other.balance)) return true;
        if(abs(balance) > abs(other.balance)) return false;
        return abs_sum > other.abs_sum;
    }
}Compound;

Compound next_compound(int i, int j){
    Compound ret = {
        samples[i], 
        samples[j], 
        samples[i] + samples[j],
        abs(samples[i]) + abs(samples[j])
    };
    
    return ret;
}

int main(){
    int N; cin >> N;
    for(int i = 0; i < N; i++) cin >> samples[i];

    sort(samples, samples + N);

    // for(int i = 0; i < N; i++){
    //     cout << samples[i] << " ";
    // }
    // cout << '\n';
    
    int i = 0, j = N - 1;
    Compound best_compound = {
        samples[i],
        samples[j],
        samples[i] + samples[j],
        abs(samples[i]) + abs(samples[j])
    };

    Compound compound(best_compound);
    while(i < j - 1){
        if(compound.balance < 0){
            compound = next_compound(++i, j);
        }
        else if(compound.balance > 0){
            compound = next_compound(i, --j);
        }
        else{
            i++;
            j--;
        }

        if(compound.better_than(best_compound))
            best_compound = compound;
    }
    cout << best_compound.a << " " << best_compound.b << '\n';

    return 0;
}