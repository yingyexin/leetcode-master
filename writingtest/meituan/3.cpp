#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

/*
可对任意元素*2，或/2，问将第一个元素变为所有元素的最大值最少需要多少操作数
1 2 3 4 -> 2
2 3 8 -> 2
4 2 10 8 ->2[4*2, 10/2]
*/

int minOper(vector<int>& a){
    int first = a[0];
    a.erase(a.begin());
    sort(a.begin(), a.end());

    int maxi = a[a.size()-1];
    // cout << maxi << " " << first << endl;
    int res = ceil(log2((maxi*1.0)/(first*1.0)));

    return res;
}

int main(){
    int n;
    cin >> n;

    vector<int> a(n);
    for(int i=0; i<n; i++)
        cin >> a[i];
    
    cout << minOper(a) << endl;

    return 0;
}