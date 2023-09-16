#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

long oper(long a, long b){
    return a^b;
}

struct hash_pair{
    
}

int func(vector<int>& nums, unordered_map<pair<int, int>, int>& umap){

    int sum = 0;

    for(int i=2; i<=nums.size(); i++){

    }

}

int main(){
    int n;
    cin >> n;
    vector<int> nums(n);
    for(int i=0; i<n; i++)
        cin >> nums[i];

    unordered_map<pair<int, int>, int> umap;
    for(int i=0; i<n-1; i++)
        umap[make_pair(i, i+1)] = oper(nums[i], nums[i+1]);
    
    cout << func(nums, umap) << endl;

    return 0;
}