#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;


/*
n块木板，宽1，高an, 拼成最大的正方形边长是？

[1,4,3,5,2]->3; [1,2,3,4]->2; [1,2,3,4,8,5,1]->3

*/

int maxSide(vector<int>& nums){
    sort(nums.begin(), nums.end());
    int n = nums.size();
    if(n==1) return 1;

    // int curWidth = 0;
    int i=1;
    for(; i<nums.size(); i++){
        // curWidth++;
        if(nums[n-i] >= i)
            continue;
        else break;
    }

    return i-1;
}

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for(int i=0; i<n; i++)
        cin >> nums[i];

    int res = maxSide(nums);
    cout << res << endl;

    return 0;
}