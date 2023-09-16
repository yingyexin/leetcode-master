#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> func(int n, int m){
    vector<int> res;
    int start = 1;
    for(int i= 1; i<=n; i++){
        // cout << start << " ";
        if(start <= m) res.push_back(start);
        else res.push_back(m);
        
        start += i;
    }
    return res;
}

int main() {
    int n, m;
    cin >> n >> m;

    auto v = func(n, m);

    for(int i=0; i<n; i++)
        cout << v[i] << " ";

    return 0;
}