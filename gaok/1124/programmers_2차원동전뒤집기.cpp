#include <string>
#include <vector>
using namespace std;

int h, w;
int minCnt=2134567890;
void dfsCol(int level, vector<vector<int>> &beginning, vector<vector<int>> &target, int cnt){
    
    if(level==w){
        
        // target check
        int flag=0;
        for(int i=0; i<h; i++){
            for(int j=0; j<w; j++){
                if(beginning[i][j]!=target[i][j]) {
                    flag=1;
                    break;
                }
            }
        }
        if(flag==0){
            if(cnt < minCnt) minCnt=cnt;
        }
        return;
    }
    
    for(int i=0; i<h; i++){
        if(beginning[i][level]==0) beginning[i][level]=1;
        else if(beginning[i][level]==1) beginning[i][level]=0;
    }
    dfsCol(level+1, beginning, target, cnt+1);
    for(int i=0; i<h; i++){
        if(beginning[i][level]==0) beginning[i][level]=1;
        else if(beginning[i][level]==1) beginning[i][level]=0;
    }
    
    dfsCol(level+1, beginning, target, cnt);
}


void dfsRow(int level, vector<vector<int>> &beginning, vector<vector<int>> &target, int cnt){
    
    if(level==h){
        
        // target check
        int flag=0;
        for(int i=0; i<h; i++){
            for(int j=0; j<w; j++){
                if(beginning[i][j]!=target[i][j]) {
                    flag=1;
                    break;
                }
            }
        }
        
        if(flag==1){
           dfsCol(0, beginning, target, cnt);
        }
        else{
            if(cnt < minCnt) minCnt=cnt;
        }
        
        return;
    }
    
    for(int i=0; i<w; i++){
        if(beginning[level][i]==0) beginning[level][i]=1;
        else if(beginning[level][i]==1) beginning[level][i]=0;
    }
    dfsRow(level+1, beginning, target, cnt+1);
    for(int i=0; i<w; i++){
        if(beginning[level][i]==0) beginning[level][i]=1;
        else if(beginning[level][i]==1) beginning[level][i]=0;
    }
    
    dfsRow(level+1, beginning, target, cnt);
}

int solution(vector<vector<int>> beginning, vector<vector<int>> target) {
    int answer = 0;
    
    h=beginning.size();
    w=beginning[0].size();
    
    dfsRow(0, beginning, target, 0);
    
    if(minCnt==2134567890) answer=-1;
    else answer=minCnt;
    
    return answer;
}
