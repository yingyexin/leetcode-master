#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm> // sort
using namespace std;

class ComSolution {
public:
    // 77M
    vector<vector<int>> combine(int n, int k) {
        vector<int> path;
        vector<vector<int>> res;
        backtracking77(n, k, 1, path, res);
        return res;
    };
    void backtracking77(int n, int k, int start, vector<int>& path, vector<vector<int>>& res){
        if(path.size()==k){
            res.push_back(path);
            return;
        }
        for(int i=start; i<=n-(k-path.size())+1; i++){
            path.push_back(i);
            backtracking77(n, k, i+1, path, res);
            path.pop_back();
        }
    }

    // 216M
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> path;
        vector<vector<int>> res;
        backtracking216(n, k, 1, path, res);
        return res;
    };
    void backtracking216(int n, int k, int start, vector<int>& path, vector<vector<int>>& res){
        if(path.size()==k){
            int sum = 0;
            for(int j=0; j<k; j++){
                sum += path[j];
            }
            if (sum==n)
                res.push_back(path);
            return;
        }
        for(int i=start; i<=9-(k-path.size())+1; i++){
            path.push_back(i);
            backtracking216(n, k, i+1, path, res);
            path.pop_back();
        }
    }

    // 17M
    vector<string> letterCombinations(string digits) {
        const string mapstr[10] = {
            "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
        }; // 0-9
        string path;
        vector<string> res;
        vector<string> d;
        for(int i=0; i<digits.size(); i++){
            if(digits[i]-'0' < 2 || digits[i]-'0' > 9){
                cout << "wrong digits input" << endl;
                return res;
            } else
                d.push_back(mapstr[digits[i]-'0']);
        }
        backtracking17(d, 0, path, res);
        return res;
    }
    void backtracking17(vector<string> d, int start, string& path, vector<string>& res){
        if(path.size()==d.size()){            
            res.push_back(path);
            return;
        }
        for(int i=0; i<d[start].size(); i++){
            path += d[start][i];
            backtracking17(d, start+1, path, res);
            path.pop_back();
        }
    }

    // 39M
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> path;
        vector<vector<int>> res;
        int sum = 0;
        sort(candidates.begin(), candidates.end());
        backtracking39(candidates, target, 0, sum, path, res);
        return res;
    }
    void backtracking39(vector<int> candidates, int target, int start, int& sum, vector<int>& path, vector<vector<int>>& res){
        if(sum==target){
            res.push_back(path);
            return;
        }
        for(int i=start; i<candidates.size() && sum+candidates[i]<=target; i++){
            sum += candidates[i];
            path.push_back(candidates[i]);
            // for(auto num:path)
            //     cout << num << " ";
            // cout << "------" << i << endl;
            backtracking39(candidates, target, i, sum, path, res);
            sum -= candidates[i];
            path.pop_back();
        }
    }

    // 40M
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> path;
        vector<bool> used(candidates.size(), false);
        vector<vector<int>> res;
        int sum = 0;
        sort(candidates.begin(), candidates.end());
        backtracking40(candidates, target, 0, sum, used, path, res);
        //backtracking40b(candidates, target, 0, sum, path, res);
        return res;
    }
    void backtracking40(vector<int> candidates, int target, int start, int& sum, vector<bool>& used, vector<int>& path, vector<vector<int>>& res){
        if(sum==target){
            res.push_back(path);
            return;
        }
        for(int i=start; i<candidates.size() && sum+candidates[i]<=target; i++){
            if(i>0 && candidates[i]==candidates[i-1] && !used[i-1])
                continue;
            sum += candidates[i];
            path.push_back(candidates[i]);
            used[i] = true;
            backtracking40(candidates, target, i+1, sum, used, path, res);
            used[i] = false;
            sum -= candidates[i];
            path.pop_back();
        }
    }
    void backtracking40b(vector<int> candidates, int target, int start, int& sum, vector<int>& path, vector<vector<int>>& res){
        if(sum==target){
            res.push_back(path);
            return;
        }
        for(int i=start; i<candidates.size() && sum+candidates[i]<=target; i++){
            if(i>start && candidates[i]==candidates[i-1])
                continue;
            sum += candidates[i];
            path.push_back(candidates[i]);
            backtracking40b(candidates, target, i+1, sum, path, res);
            sum -= candidates[i];
            path.pop_back();
        }
    }

};
class HardSolution{
public:
    // Problem 2305M
    int ans = INT_MAX;
    int distributeCookies(vector<int>& cookies, int k) {
        sort(cookies.begin(), cookies.end(), std::greater());
        vector<int> bucket(k, 0);
       
        backtrace(cookies, bucket, 0);
        return ans;
    }
    void backtrace(vector<int>& nums, vector<int>& bucket, int idx){

        if(idx==nums.size()){
            int unfair = INT_MIN;
            for(int num:bucket)
                unfair = max(unfair, num);
            ans = min(unfair, ans);
            return;
        }

        int zero=0;
        for(int num:bucket)
            if(num==0) zero++;
        if(zero>nums.size()-idx) return;

        for(int i=0; i<bucket.size(); i++){
            if(bucket[i]>ans) return;
            
            bucket[i] += nums[idx];
            backtrace(nums, bucket, idx+1);
            bucket[i] -= nums[idx];
        }
        return;
    }



}


void printVec(vector<vector<int>> res){
    cout << "[" << endl;
    for(int i=0; i<res.size(); i++){
        cout << "[";
        for(int j=0; j< res[0].size(); j++)
            cout << res[i][j] << " ";
        cout << "]" << endl;
    }
    cout << "]";
}

int main(){
    // int n,k;
    // cin >> n >> k;
    ComSolution sol;
    // printVec(sol.combine(n, k));
    vector<int> vec = {2,5,3};
    vector<vector<int>> res = sol.combinationSum(vec, 7);
    

    return 0;
}
