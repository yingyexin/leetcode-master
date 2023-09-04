#include <iostream>
#include <vector>
#include <algorithm>
#include "string.h"
using namespace std;

int ans = 0;

bool isValid(vector<int>& path){
    if(path.size()<2) return true;
    
    if(path.size()==2){
        // if(path[1] % path[0] == 0) cout << path[0] << " " << path[1] << endl;
        return path[1] % path[0] == 0;
    }

    double factor = path[1]*1.0 / (path[0]*1.0);
    for(int i=1; i<path.size()-1; i++)
        if( path[i+1]*1.0 / (path[i]*1.0) != factor) 
            return false;
    
    // cout << path[0] << " " << path[1] <<" " << path[2] << endl;
    return true;
}

void backtrack(vector<int>& a, vector<int>& path, int startid, int m){
    if(path.size()==m){
        if(isValid(path)) ans++;
        return;
    }
    for(int i=startid; i<=a.size()-(m-path.size()); i++){
        path.push_back(a[i]);
        backtrack(a, path, i+1, m);
        path.pop_back();
    }
    return;
}
/*
n个数，删除k个，剩余元素两两互为倍数，有几种方案
6 4
1 4 2 3 6 7 -> 8
6 3 
1 4 2 3 6 7 -> 1
*/

int dp(vector<long>& nums, int n, int k){
    sort(nums.begin(), nums.end(), [](long a, long b) {return a < b; });
    long len = n - k;
    vector<vector<long>> dp(n, vector<long>(len + 1, 0));//横坐标数字，纵坐标子串长度
    for (long i = 0; i < n; i++) {
        dp[i][1] = 1;
        for (long j = 0; j < i; j++) {//找因数
            if (nums[i] % nums[j] == 0) {
                for (long k = 2; k <= len; k++) {
                    dp[i][k] += dp[j][k - 1];
                }
            }
        }
    }
    long sum = 0;
    for (long i = 0; i < n; i++) {
        sum += dp[i][len];
    }
    return sum;
}

int main(){
    int n, k;
    cin >> n >> k;

    vector<long> a(n);
    for(int i=0; i<n; i++)
        cin >> a[i];

    // ans = 0;
    // vector<int> path;
    // sort(a.begin(), a.end());
    // backtrack(a, path, 0, n - k);
    // cout << ans << endl;
    cout << dp(a, n, k) << endl;

    return 0;
}