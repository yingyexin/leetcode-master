#include <iostream>
#include <vector>
#include <algorithm> //sort
using namespace std;

class EasySolution {
public:
    //455E
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int index = 0;//g
        int res = 0;
        for(int j=0; j<s.size(); j++){
            if(index<g.size() && g[index]<=s[j]){
                res++;
                index++;
            }
        }
        return res;
    }
    //1005E
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        while(k>0){
            sort(nums.begin(), nums.end());
            nums[0] *= -1;
            k--;
        }
        int sum=0;
        for(auto num:nums)
            sum += num;
        return sum;
    }
    int largestSumAfterKNegationsb(vector<int>& A, int K) {
        sort(A.begin(), A.end(), [](int a, int b){return abs(a)>abs(b);});       // 第一步
        for (int i = 0; i < A.size(); i++) { // 第二步
            if (A[i] < 0 && K > 0) {
                A[i] *= -1;
                K--;
            }
        }
        if (K % 2 == 1) A[A.size() - 1] *= -1; // 第三步
        int result = 0;
        for (int a : A) result += a;        // 第四步
        return result;
    }

    //860E
    bool lemonadeChange(vector<int>& bills) {
        vector<int> nums;
        for(auto mon:bills){
            if(mon == 5) nums[0]++;
            if(mon == 10){
                if(nums[0]==0) return false;
                nums[0]--;
                nums[1]++;
            }
            if(mon == 20){
                if(nums[1] == 0){
                    if(nums[0] < 3) return false;
                    nums[0] -= 3;
                    nums[2]++;
                } else if(nums[0]==0)
                    return false;
                else{
                    nums[1]--;
                    nums[0]--;
                    nums[2]++;
                }
            }
        return true;
    }
};

class MediumSolution {
public:
    // 376M
    int wiggleMaxLength(vector<int>& nums) {
        if(nums.size()<=1) return 1;
        int preDiff = 0;
        int curDiff = 0;
        int res = 1;
        for(int i=1; i<nums.size(); i++){
            curDiff = nums[i]-nums[i-1];
            if((curDiff>0 && preDiff<=0) || (curDiff<0 && preDiff>=0)){
                res++;
                preDiff = curDiff;
            }
        }
    }
};

int main(){


    return 0;
}