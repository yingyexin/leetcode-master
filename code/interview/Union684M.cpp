#include <iostream>
#include <vector>
using namespace std;

class Solution {
private:
    int n = 1005; // 节点数量3 到 1000
    vector<int> father = vector<int> (n, 0); // C++里的一种数组结构

    // 并查集初始化
    void init() {
        for (int i = 0; i < n; ++i) {
            father[i] = i;
        }
    }
    // 并查集里寻根的过程
    int find(int u) {
        return u == father[u] ? u : father[u] = find(father[u]);
    }
    // 判断 u 和 v是否找到同一个根
    bool isSame(int u, int v) {
        u = find(u);
        v = find(v);
        return u == v;
    }
    // 将v->u 这条边加入并查集
    void join(int u, int v) {
        u = find(u); // 寻找u的根
        v = find(v); // 寻找v的根
        if (u == v) return ; // 如果发现根相同，则说明在一个集合，不用两个节点相连直接返回
        father[v] = u;
}
public:
    vector<int> getConnect(vector<vector<int>>& edges) {
        init();
        for (int i = 0; i < edges.size(); i++) {
            if (isSame(edges[i][0], edges[i][1])) return edges[i];
            else join(edges[i][0], edges[i][1]);
        }
        return {};
    }
};

int main(){
    int m,n;
    cin >> m >> n; 
    vector<vector<char>> grid(m, vector<char>(n));
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];
    cout << getConnect(grid);
}