#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;

int func(vector<int>& nums, int sum_all){

    int max_ = 0;
    int sum = nums[0];
    for(int i=1; i<nums.size(); i++){
        if(sum>=nums[i] && max_<nums[i]) 
            max_ = nums[i];
        sum += nums[i];
    }
    // cout << sum << " " << max_ << endl;
    return max_==0? -1:sum-2*max_;
}



int main() {
    int n;
    cin >> n;
    vector<int> nums(n);    
    int sum_all = 0;
    for(int i=0; i<n; i++){
        cin >> nums[i];
        sum_all += nums[i];
    }

    cout << func(nums, sum_all) << endl;

    return 0;
}