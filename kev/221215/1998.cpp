#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <vector>
#include <array>
#include <unordered_set>
using namespace std;

#define DEBUG

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define size(v) (int)((v).size())

#define WHITE '0'
#define BLACK '1'

#define ROOT 0

struct Coord{
    int y, x;
};

enum NodeType{
    EMPTY = 1,
    CONNECTOR,
    LEAF
};

struct Node{
    NodeType type;
    string pattern;
    bool linked = false; // 패턴 연결되어 있는 노드인지
};

int N, M;
char quad[128][128];
unordered_set<string> subtree_patterns;

int get_zero_padded_width(int width){
    int padding;
    for(padding = 2; padding < width; padding *= 2);
    return padding;
}

const int dy[4] = {0, 0, 1, 1};
const int dx[4] = {0, 1, 0, 1};

void make_quadtree(vector<Node>& quadtree, int idx, Coord pivot, int width){
    Node& cur_node = quadtree[idx];
    
    if(width == 1){ // base: 현재 노드가 쿼드트리의 리프 노드이다
        cur_node.type = NodeType::LEAF;
        
        const char& color = quad[pivot.y][pivot.x];
        cur_node.pattern.push_back(color);
        
        return;
    }

    array<Coord, 4> subtree_pivots;
    for(int k = 0; k < 4; ++k){
        subtree_pivots[k] = {
            pivot.y + dy[k] * (width / 2), 
            pivot.x + dx[k] * (width / 2)
            };
    }
    
    // 서브트리로 재귀
    for(int k = 0; k < 4; ++k)
        make_quadtree(quadtree, 4 * idx + (k + 1), subtree_pivots[k], width / 2);

    // 서브트리 완성 이후
    Node& sub1 = quadtree[4 * idx + 1];
    Node& sub2 = quadtree[4 * idx + 2];
    Node& sub3 = quadtree[4 * idx + 3];
    Node& sub4 = quadtree[4 * idx + 4];

    bool is_all_leaf = sub1.type == NodeType::LEAF 
                    && sub2.type == NodeType::LEAF 
                    && sub3.type == NodeType::LEAF 
                    && sub4.type == NodeType::LEAF;
    
    bool is_all_leaf_same = is_all_leaf 
                    && sub1.pattern == sub2.pattern 
                    && sub2.pattern == sub3.pattern 
                    && sub3.pattern == sub4.pattern;
    
    if(is_all_leaf_same){
        cur_node.type = NodeType::LEAF;
        cur_node.pattern = sub1.pattern;
        sub1.type = sub2.type = sub3.type = sub4.type = NodeType::EMPTY;
        return;
    }
    
    // 서브트리 패턴 등록
    if(idx != ROOT && cur_node.type == NodeType::CONNECTOR){
        // 현재 노드를 포함하지 않는 하위 서브트리 패턴
        string pattern = sub1.pattern + sub2.pattern + sub3.pattern + sub4.pattern;

        if(subtree_patterns.find(pattern) == subtree_patterns.end())
            subtree_patterns.insert(pattern);
        else
            cur_node.linked = true;
        
        /* ex)
        서브트리 상태가 아래와 같을 때
        
        .
        b w b w
         
        하위 서브트리 패턴 = bwbw
        커넥터 노드를 포함하는 패턴 = (bwbw)
        */
        cur_node.pattern = "(" + pattern + ")";
    }
}

void print_quadtree(const vector<Node>& quadtree, int quad_width){
    int start_idx = 0;
    for(int level = 0; level < (int)log2(quad_width) + 1; ++level){
        int num_vertices = pow(pow(2, level), 2);
        rep(i, num_vertices){
            const Node& node = quadtree[start_idx + i];
            const NodeType& type = node.type;
            switch (type)
            {
            case NodeType::EMPTY:
                cout << "_" << " ";
                break;
            case NodeType::CONNECTOR:
                cout << "." << " ";
                break;
            case NodeType::LEAF:
                cout << (node.pattern == "0" ? "w": "b") << " ";
                break;
            default:
                break;
            }
        }
        cout << '\n';
        start_idx += num_vertices;
    }
}

int get_quadtree_length(int quad_width){
    int num_vertices = 0;
    for(int level = 0; level < (int)log2(quad_width) + 1; ++level){
        num_vertices += pow(pow(2, level), 2);
    }
    return num_vertices;
}

int count_quadtree_nodes(const vector<Node>& quadtree, int root_idx){
    if(quadtree[root_idx].type == NodeType::LEAF) return 1;
    
    int counter = 1;
    for(int k = 1; k <= 4; ++k){
        int subtree_root_idx = 4 * root_idx + k;
        counter += count_quadtree_nodes(quadtree, subtree_root_idx);
    }

    return counter;
}

int count_compressed_quadtree_nodes(const vector<Node>& quadtree, int root_idx){
    if(quadtree[root_idx].linked) return 0;
    if(quadtree[root_idx].type == NodeType::LEAF) return 1;
    
    int counter = 1;
    for(int k = 1; k <= 4; ++k){
        int subtree_root_idx = 4 * root_idx + k;
        counter += count_compressed_quadtree_nodes(quadtree, subtree_root_idx);
    }

    return counter;
}

void solve(){
    memset(quad, WHITE, sizeof(quad));
    
    // 1
    // 2 3
    // 4 5 6 7

    // 0
    // 1 2 3 4
    // 5 6 7 8 / 9 10 11 12 / 13 14 15 16 / 17 18 19 20

    // 서브트리 패턴을 문자열로 식별하기

    cin >> N >> M;
    rep(i, N) rep(j, M) cin >> quad[i][j];
    
    int quad_width = get_zero_padded_width(max(N, M));
    int quadtree_len = get_quadtree_length(quad_width);
    
    vector<Node> quadtree(quadtree_len, {CONNECTOR, "", false});
    
    make_quadtree(quadtree, ROOT, {0, 0}, quad_width);
    
#ifdef DEBUG
    print_quadtree(quadtree, quad_width);
#endif

    // answer
    cout << count_quadtree_nodes(quadtree, ROOT) << " " 
        << count_compressed_quadtree_nodes(quadtree, ROOT) << '\n';
}

int main(){
    solve();
    return 0;
}