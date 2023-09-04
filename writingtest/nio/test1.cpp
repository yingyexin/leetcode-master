#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

int getResult(vector<int>& nums){
    int n=nums.size();
    
    sort(nums.begin(), nums.end());
    long long res = 0;//numeric_limits<long long>::min();
    
    for (int mid = 1; mid < n / 2 + 1; mid++) {
        long long S = 0;
        for (int i = 0; mid - i-1 >= 0 && n - i -1>= mid; i++) {
            S += nums[n - i-1] + nums[mid - i-1] - 2 * nums[mid];
            res = max(res, S);
        }
    }

    return res;
}

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    long long res = getResult(nums);
    
    cout << res << endl;
    return 0;
}
// 64 位输出请用 printf("%lld")