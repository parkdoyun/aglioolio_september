#include <iostream>
#include <vector>
using namespace std;

#define MAX_SIZE 100000

int inorder_value_index_mapper[MAX_SIZE + 1];
int postorder_value_index_mapper[MAX_SIZE + 1];
int inorder_traverse[MAX_SIZE];
int postorder_traverse[MAX_SIZE];

struct Bound
{
    int left;
    int right;
};

// 7
// 6 4 2 1 3 5 7
// 6 4 2 7 5 3 1

void get_preorder_traverse(const Bound &inorder_bound, const Bound &postorder_bound)
{
    int i = inorder_bound.left;
    int j = inorder_bound.right;

    if (i > j) return;

    int x = postorder_bound.left;
    int y = postorder_bound.right;

    int cur_root_value = postorder_traverse[y];
    cout << cur_root_value << " ";

    int inorder_root_idx = inorder_value_index_mapper[cur_root_value];
    int left_subtree_size = inorder_root_idx - i;

    get_preorder_traverse({i, inorder_root_idx - 1}, {x, x + left_subtree_size - 1});
    get_preorder_traverse({inorder_root_idx + 1, j}, {x + left_subtree_size, y - 1});
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int N; cin >> N;

    for (int i = 0; i < N; ++i)
    {
        int e;
        cin >> e;
        inorder_traverse[i] = e;
        inorder_value_index_mapper[e] = i;
    }

    for (int i = 0; i < N; ++i)
    {
        int e;
        cin >> e;
        postorder_traverse[i] = e;
        postorder_value_index_mapper[e] = i;
    }

    get_preorder_traverse({0, N - 1}, {0, N - 1});
}